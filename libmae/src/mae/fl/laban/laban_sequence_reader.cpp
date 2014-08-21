/*
 * laban_sequence_reader.cpp
 *
 *  Created on: 26.07.2014
 *      Author: keks
 */

#include "laban_sequence_reader.hpp"


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			laban_sequence_reader::laban_sequence_reader()
			{
			}

			laban_sequence_reader::~laban_sequence_reader()
			{
			}

			std::shared_ptr<laban_sequence> laban_sequence_reader::read_sequence_file(std::string file_name)
			{
				std::ifstream in_file(file_name);
				std::stringstream sstr;

				if (in_file.is_open())
				{
					std::string line;
					while (std::getline(in_file, line))
					{
						sstr << line << std::endl;
					}
					in_file.close();
					return read_sequence_str(sstr.str());
				}

				return nullptr;
			}

			std::shared_ptr<laban_sequence> laban_sequence_reader::read_sequence_str(std::string xml_string)
			{
				std::shared_ptr<laban_sequence> result;

				std::stringstream sstr;
				sstr << xml_string;

				xmlpp::DomParser parser;
				parser.parse_stream(sstr);

				xmlpp::Document* doc = parser.get_document();
				xmlpp::Node* root_node = doc->get_root_node();

				//setup namespace prefix
				std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map = std::shared_ptr<xmlpp::Node::PrefixNsMap>(new xmlpp::Node::PrefixNsMap());
				if (root_node->get_namespace_prefix().size() > 0)
				{
					namespace_map->insert(std::make_pair(root_node->get_namespace_prefix(), root_node->get_namespace_uri()));
				}

				std::string nsp = root_node->get_namespace_prefix();

				//---------------
				// main elements
				//---------------

				std::string title = get_node_content(root_node, namespace_map, "title", nsp, "unknown");

				std::vector<std::string> authors = get_node_contents(root_node, namespace_map, "author", nsp, "anonymous");

				//staff elements
				unsigned int measures = static_cast<unsigned int>(std::stoul(get_node_content(root_node, namespace_map, "staff/measures", nsp, "0")));

				e_time_unit time_unit = e_time_unit_c::parse(get_node_content(root_node, namespace_map, "staff/timing/timeUnit", nsp, "NONE"));

				unsigned int beat_duration = static_cast<unsigned int>(std::stoul(get_node_content(root_node, namespace_map, "staff/timing/measure/beatDuration", nsp, "0")));

				unsigned int beats = static_cast<unsigned int>(std::stoul(get_node_content(root_node, namespace_map, "staff/timing/measure/beats", nsp, "0")));

				//create the sequence and add additional information as well as columns and movements
				result = std::shared_ptr<laban_sequence>(
						new laban_sequence(title, authors.at(0), measures, time_unit, beat_duration, beats));

				//additional elements

				//other authors
				for (unsigned int i = 1; i < authors.size(); i++)
				{
					result->add_author(authors.at(i));
				}

				//decription
				std::string description = get_node_content(root_node, namespace_map, "description", nsp, "");

				if (description.size() > 0)
				{
					result->set_description(description);
				}

				//column definitions
				//TODO continue from here
				xmlpp::NodeSet coldefs_node_set = root_node->find("/score/columns/columnDefinition");

				for (unsigned int i = 0; i < coldefs_node_set.size(); i++)
				{
					result->add_column_definition(read_column_definition(coldefs_node_set.at(i)));
				}

				//movements
				xmlpp::NodeSet movs_node_set = root_node->find("/score/movements/movement");

				for (unsigned int i = 0; i < coldefs_node_set.size(); i++)
				{
					result->add_column_definition(read_column_definition(coldefs_node_set.at(i)));
				}

				//done
				return result;
			}

			std::string laban_sequence_reader::get_xpath(std::string element, std::string nsp)
			{
				std::stringstream sstr;

				std::vector<std::string> split = mstr::split(element, '/');

				for (unsigned int i = 0; i < split.size() ; i++)
				{
					if (i > 0)
					{
						sstr << "/";
					}

					if (nsp.size() > 0)
					{
						sstr << nsp << ":";
					}

					sstr << split.at(i);
				}

				std::cout << sstr.str() << std::endl;

				return sstr.str();
			}

			std::string laban_sequence_reader::get_node_content(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return)
			{
				xmlpp::NodeSet node_set = parent_node->find(get_xpath(element, nsp), *namespace_map);

				std::string result = default_return;

				if (node_set.size() > 0)
				{
					xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(node_set.at(0));

					if (node->has_child_text())
					{
						result = node->get_child_text()->get_content();
					}
					else
					{
						result = "";
					}
				}

				return result;
			}

			std::vector<std::string> laban_sequence_reader::get_node_contents(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return)
			{
				xmlpp::NodeSet node_set = parent_node->find(get_xpath(element, nsp), *namespace_map);

				std::vector<std::string> result;

				if (node_set.size() > 0)
				{
					for (unsigned int i = 0; i < node_set.size(); i++)
					{
						xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(node_set.at(i));

						if (node->has_child_text())
						{
							result.push_back(node->get_child_text()->get_content());
						}
						else
						{
							result.push_back("");
						}
					}
				}
				else
				{
					result.push_back(default_return);
				}

				return result;
			}

			std::shared_ptr<column_definition> laban_sequence_reader::read_column_definition(xmlpp::Node* node)
			{
				std::shared_ptr<column_definition> result = nullptr;

				//staff elements
				xmlpp::NodeSet index_node_set = node->find("/index");
				unsigned int index = 0;

				if (index_node_set.size() > 0)
				{
					index = static_cast<unsigned int>(std::stoi(
							dynamic_cast<xmlpp::ContentNode*>(index_node_set.at(0))->get_content()));
				}

				std::shared_ptr<ps::i_pre_sign> pre_sign = laban_sequence_reader::read_pre_sign(node);

				result = std::shared_ptr<column_definition>(new column_definition(index, pre_sign));

				return result;
			}

			std::shared_ptr<ps::i_pre_sign> laban_sequence_reader::read_pre_sign(xmlpp::Node* node)
			{
				std::shared_ptr<ps::i_pre_sign> result = nullptr;

				xmlpp::NodeSet body_part_node_set = node->find("/preSign/bodyPart");
				if (body_part_node_set.size() > 0)
				{
					//side
					xmlpp::NodeSet side_node_set = node->find("/preSign/bodyPart/side");
					ps::e_side side = ps::e_side::NONE;

					if (side_node_set.size() > 0)
					{
						side = ps::e_side_c::parse(
								dynamic_cast<xmlpp::ContentNode*>(side_node_set.at(0))->get_content());
					}

					std::shared_ptr<ps::i_endpoint> endpoint = laban_sequence_reader::read_end_point(
							body_part_node_set.at(0));

					if (endpoint != nullptr)
					{
						result = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, endpoint));
					}
					else
					{
						std::shared_ptr<ps::i_limb> limb = laban_sequence_reader::read_limb(body_part_node_set.at(0));

						if (limb != nullptr)
						{
							result = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, limb));
						}
						else
						{
							std::shared_ptr<ps::surface_part> surface = laban_sequence_reader::read_surface(
									body_part_node_set.at(0));

							if (surface != nullptr)
							{
								result = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, surface));
							}
							else
							{
								throw std::invalid_argument(
										"Column definition is invalid. Expected a body part, namely an endpoint a limb or a surface.");
							}
						}
					}
				}
				else
				{
					xmlpp::NodeSet prop_node_set = node->find("/preSign/prop");

					if (prop_node_set.size() > 0)
					{
						//side
						xmlpp::NodeSet name_node_set = node->find("/preSign/prop/name");
						std::string name = "";

						if (name_node_set.size() > 0)
						{
							name = dynamic_cast<xmlpp::ContentNode*>(name_node_set.at(0))->get_content();
						}

						//description (optional)
						xmlpp::NodeSet description_node_set = node->find("/preSign/prop/description");
						std::string description = "";

						if (description_node_set.size() > 0)
						{
							description = dynamic_cast<xmlpp::ContentNode*>(description_node_set.at(0))->get_content();
						}

						result = std::shared_ptr<ps::i_pre_sign>(new ps::prop(name, description));
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_endpoint> laban_sequence_reader::read_end_point(xmlpp::Node* node)
			{
				std::shared_ptr<ps::i_endpoint> result = nullptr;

				//area pre-sign
				xmlpp::NodeSet area_node_set = node->find("/part");

				if (area_node_set.size() > 0)
				{
					ps::e_area area = ps::e_area_c::parse(
							dynamic_cast<xmlpp::ContentNode*>(area_node_set.at(0))->get_content());

					result = std::shared_ptr<ps::i_endpoint>(new ps::area_part(area));
				}
				else
				{
					//joint pre-sign
					xmlpp::NodeSet joint_node_set = node->find("/joint/joint");

					if (joint_node_set.size() > 0)
					{
						ps::e_joint joint = ps::e_joint_c::parse(
								dynamic_cast<xmlpp::ContentNode*>(joint_node_set.at(0))->get_content());

						result = std::shared_ptr<ps::i_endpoint>(new ps::joint_part(joint));
					}
					else
					{
						//digit pre-sign
						xmlpp::NodeSet digit_node_set = node->find("/digit/digit");

						if (digit_node_set.size() > 0)
						{
							ps::e_digit digit = ps::e_digit_c::parse(
									dynamic_cast<xmlpp::ContentNode*>(digit_node_set.at(0))->get_content());

							xmlpp::NodeSet digit_joint_node_set = node->find("/digit/joint");
							unsigned int knuckle = 0;
							if (digit_joint_node_set.size() > 0)
							{
								knuckle = static_cast<unsigned int>(std::stoi(
										dynamic_cast<xmlpp::ContentNode*>(digit_joint_node_set.at(0))->get_content()));
							}

							result = std::shared_ptr<ps::i_endpoint>(new ps::digit_part(digit, knuckle));
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_limb> laban_sequence_reader::read_limb(xmlpp::Node* node)
			{
				std::shared_ptr<ps::i_limb> result = nullptr;

				//default limb pre-sign
				xmlpp::NodeSet default_limb_node_set = node->find("/limb/default/limb");

				if (default_limb_node_set.size() > 0)
				{
					ps::e_limb limb = ps::e_limb_c::parse(
							dynamic_cast<xmlpp::ContentNode*>(default_limb_node_set.at(0))->get_content());

					result = std::shared_ptr<ps::i_limb>(new ps::default_limb(limb));
				}
				else
				{
					xmlpp::NodeSet custom_limb_node_set = node->find("/limb/custom");

					if (custom_limb_node_set.size() > 0)
					{
						xmlpp::NodeSet fixed_end_node_set = node->find("/limb/custom/fixedEnd");

						if (fixed_end_node_set.size() > 0)
						{

							std::shared_ptr<ps::i_endpoint> fixed_end = laban_sequence_reader::read_end_point(
									fixed_end_node_set.at(0));

							if (fixed_end != nullptr)
							{

								xmlpp::NodeSet extremity_end_node_set = node->find("/limb/custom/extremity");

								std::shared_ptr<ps::i_endpoint> extremity_end = nullptr;

								if (extremity_end_node_set.size() > 0)
								{
									extremity_end = laban_sequence_reader::read_end_point(extremity_end_node_set.at(0));
								}

								result = std::shared_ptr<ps::i_limb>(new ps::custom_limb(fixed_end, extremity_end));
							}
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::surface_part> laban_sequence_reader::read_surface(xmlpp::Node* node)
			{
				std::shared_ptr<ps::surface_part> result = nullptr;

				xmlpp::NodeSet surface_node_set = node->find("/surface");

				if (surface_node_set.size() > 0)
				{
					std::shared_ptr<ps::i_limb> limb = laban_sequence_reader::read_limb(surface_node_set.at(0));

					xmlpp::NodeSet limb_side_node_set = node->find("/surface/side");

					if (limb != nullptr && limb_side_node_set.size() > 0)
					{
						ps::e_limb_side limb_side = ps::e_limb_side_c::parse(
								dynamic_cast<xmlpp::ContentNode*>(limb_side_node_set.at(0))->get_content());

						result = std::shared_ptr<ps::surface_part>(new ps::surface_part(limb_side, limb));
					}
				}

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_movement(xmlpp::Node* node)
			{
				std::shared_ptr<i_movement> result = nullptr;

				xmlpp::NodeSet column_node_set = node->find("/column");

				if (column_node_set.size() > 0)
				{
					int column = std::stoi(dynamic_cast<xmlpp::ContentNode*>(column_node_set.at(0))->get_content());

					xmlpp::NodeSet measure_node_set = node->find("/measure");

					if (measure_node_set.size() > 0)
					{
						unsigned int measure = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(measure_node_set.at(0))->get_content()));

						xmlpp::NodeSet beat_node_set = node->find("/beat");

						if (beat_node_set.size() > 0)
						{
							double beat = std::stod(dynamic_cast<xmlpp::ContentNode*>(beat_node_set.at(0))->get_content());

							xmlpp::NodeSet duration_node_set = node->find("/duration");

							if (duration_node_set.size() > 0)
							{
								double duration = std::stod(dynamic_cast<xmlpp::ContentNode*>(duration_node_set.at(0))->get_content());

								xmlpp::NodeSet pre_sign_node_set = node->find("/preSign");
								std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr;

								if (pre_sign_node_set.size() > 0)
								{
									pre_sign = laban_sequence_reader::read_pre_sign(node);
								}

								xmlpp::NodeSet hold_node_set = node->find("/hold");
								bool hold = false;

								if (hold_node_set.size() > 0)
								{
									hold = mbool::parse(dynamic_cast<xmlpp::ContentNode*>(hold_node_set.at(0))->get_content());
								}

								xmlpp::NodeSet direction_node_set = node->find("/direction");

								if (direction_node_set.size() > 0)
								{
									std::shared_ptr<mv::direction_symbol> direction = laban_sequence_reader::read_direction(direction_node_set.at(0));

									if (direction != nullptr)
									{
										result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, direction, hold, pre_sign));
									}
								}
								else
								{
									xmlpp::NodeSet space_node_set = node->find("/space");

									if (space_node_set.size() > 0)
									{
										std::shared_ptr<mv::space_symbol> space = laban_sequence_reader::read_space(space_node_set.at(0));

										if (space != nullptr)
										{
											result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, space, hold, pre_sign));
										}
									}
									else
									{
										xmlpp::NodeSet turn_node_set = node->find("/turn");

										if (turn_node_set.size() > 0)
										{
											std::shared_ptr<mv::turn_symbol> turn = laban_sequence_reader::read_turn(turn_node_set.at(0));

											if (turn != nullptr)
											{
												result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, turn, hold, pre_sign));
											}
										}
										else
										{
											xmlpp::NodeSet vibration_node_set = node->find("/vibration");

											if (vibration_node_set.size() > 0)
											{
												std::shared_ptr<mv::vibration_symbol> vibration = laban_sequence_reader::read_vibration(vibration_node_set.at(0));

												if (vibration != nullptr)
												{
													result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, vibration, hold, pre_sign));
												}
											}
											else
											{
												xmlpp::NodeSet cancel_node_set = node->find("/cancel");

												if (cancel_node_set.size() > 0)
												{
													std::shared_ptr<mv::cancellation_symbol> cancel = laban_sequence_reader::read_cancellation(cancel_node_set.at(0));

													if (cancel != nullptr)
													{
														result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, cancel, hold, pre_sign));
													}
												}
												else
												{
													throw std::invalid_argument("Movement symbol unknown.");
												}
											}
										}
									}
								}
							}
						}
					}
				}


				return result;
			}

			std::shared_ptr<mv::pin> laban_sequence_reader::read_pin(xmlpp::Node* node)
			{
				std::shared_ptr<mv::pin> result = nullptr;

				xmlpp::NodeSet vertical_node_set = node->find("/vertical");

				if (vertical_node_set.size() > 0)
				{
					mv::e_level vertical = mv::e_level_c::parse(
							dynamic_cast<xmlpp::ContentNode*>(vertical_node_set.at(0))->get_content());

					xmlpp::NodeSet horizontal_node_set = node->find("/horizontal");

					if (horizontal_node_set.size() > 0)
					{
						int horizontal = std::stoi(dynamic_cast<xmlpp::ContentNode*>(horizontal_node_set.at(0))->get_content());

						result = std::shared_ptr<mv::pin>(new mv::pin(vertical, horizontal));
					}
				}

				return result;
			}

			std::shared_ptr<mv::space_measurement> laban_sequence_reader::read_space_measurement(xmlpp::Node* node)
			{
				std::shared_ptr<mv::space_measurement> result = nullptr;

				xmlpp::NodeSet type_node_set = node->find("/spaceMeasurement/type");

				if (type_node_set.size() > 0)
				{
					mv::e_space vertical = mv::e_space_c::parse(
							dynamic_cast<xmlpp::ContentNode*>(type_node_set.at(0))->get_content());

					xmlpp::NodeSet degree_node_set = node->find("/spaceMeasurement/degree");

					if (degree_node_set.size() > 0)
					{
						unsigned int degree = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(degree_node_set.at(0))->get_content()));

						xmlpp::NodeSet direction_node_set = node->find("/spaceMeasurement/direction");
						mv::e_space_direction direction = mv::e_space_direction::NONE;

						if (direction_node_set.size() > 0)
						{
							direction = mv::e_space_direction_c::parse(
									dynamic_cast<xmlpp::ContentNode*>(direction_node_set.at(0))->get_content());
						}

						result = std::shared_ptr<mv::space_measurement>(new mv::space_measurement(vertical, degree, direction));
					}
				}

				return result;

			}

			std::shared_ptr<mv::i_dynamics_sign> laban_sequence_reader::read_dynamics(xmlpp::Node* node)
			{
				std::shared_ptr<mv::i_dynamics_sign> result = nullptr;

				xmlpp::NodeSet accent_node_set = node->find("/dynamics/accent");

				if (accent_node_set.size() > 0)
				{
					unsigned int accent = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(accent_node_set.at(0))->get_content()));

					result = std::shared_ptr<mv::i_dynamics_sign>(new mv::accent_sign(accent));
				}
				else
				{
					xmlpp::NodeSet dynamic_node_set = node->find("/dynamics/dynamic");

					if (dynamic_node_set.size() > 0)
					{
						mv::e_dynamic dynamic = mv::e_dynamic_c::parse(dynamic_cast<xmlpp::ContentNode*>(dynamic_node_set.at(0))->get_content());

						result = std::shared_ptr<mv::i_dynamics_sign>(new mv::dynamic_sign(dynamic));
					}
				}

				return result;
			}

			std::shared_ptr<mv::direction_symbol> laban_sequence_reader::read_direction(xmlpp::Node* node)
			{
				std::shared_ptr<mv::direction_symbol> result = nullptr;

				xmlpp::NodeSet vertical_node_set = node->find("/vertical");

				if (vertical_node_set.size() > 0)
				{
					mv::e_level vertical = mv::e_level_c::parse(dynamic_cast<xmlpp::ContentNode*>(vertical_node_set.at(0))->get_content());


					xmlpp::NodeSet horizontal_node_set = node->find("/horizontal");

					if (horizontal_node_set.size() > 0)
					{
						mv::e_direction horizontal = mv::e_direction_c::parse(dynamic_cast<xmlpp::ContentNode*>(horizontal_node_set.at(0))->get_content());

						//modification pin
						xmlpp::NodeSet modification_pin_node_set = node->find("/modificationPin");
						std::shared_ptr<mv::pin> modification_pin = nullptr;

						if (modification_pin_node_set.size() > 0)
						{
							modification_pin = laban_sequence_reader::read_pin(modification_pin_node_set.at(0));
						}

						//modification pin
						xmlpp::NodeSet relationship_pin_node_set = node->find("/relationshipPin");
						std::shared_ptr<mv::pin> relationship_pin = nullptr;

						if (relationship_pin_node_set.size() > 0)
						{
							relationship_pin = laban_sequence_reader::read_pin(relationship_pin_node_set.at(0));
						}


						//spaceMeasurement
						xmlpp::NodeSet space_measurement_node_set = node->find("/spaceMeasurement");
						std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

						if (space_measurement_node_set.size() > 0)
						{
							space_measurement = laban_sequence_reader::read_space_measurement(node);
						}

						//dynamics
						xmlpp::NodeSet dynamics_node_set = node->find("/dynamics");
						std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

						if (dynamics_node_set.size() > 0)
						{
							dynamics = laban_sequence_reader::read_dynamics(node);
						}

						//dynamics
						xmlpp::NodeSet contact_hook_node_set = node->find("/contactHook");
						mv::e_contact_hook contact_hook = mv::e_contact_hook::NONE;

						if (contact_hook_node_set.size() > 0)
						{
							contact_hook = mv::e_contact_hook_c::parse(dynamic_cast<xmlpp::ContentNode*>(contact_hook_node_set.at(0))->get_content());
						}


						result = std::shared_ptr<mv::direction_symbol>(new mv::direction_symbol(vertical, horizontal, modification_pin, relationship_pin, dynamics, space_measurement, contact_hook));
					}
				}


				return result;
			}

			std::shared_ptr<mv::space_symbol> laban_sequence_reader::read_space(xmlpp::Node* node)
			{
				std::shared_ptr<mv::space_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet space_measurement_node_set = node->find("/spaceMeasurement");
				std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

				if (space_measurement_node_set.size() > 0)
				{
					space_measurement = laban_sequence_reader::read_space_measurement(node);

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find("/dynamics");
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = laban_sequence_reader::read_dynamics(node);
					}

					result = std::shared_ptr<mv::space_symbol>(new mv::space_symbol(space_measurement, dynamics));
				}

				return result;
			}

			std::shared_ptr<mv::turn_symbol> laban_sequence_reader::read_turn(xmlpp::Node* node)
			{
				std::shared_ptr<mv::turn_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet direction_node_set = node->find("/direction");

				if (direction_node_set.size() > 0)
				{
					mv::e_turn_direction direction = mv::e_turn_direction_c::parse(dynamic_cast<xmlpp::ContentNode*>(direction_node_set.at(0))->get_content());

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find("/dynamics");
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = laban_sequence_reader::read_dynamics(node);
					}

					//degree
					xmlpp::NodeSet degree_node_set = node->find("/degree");
					std::shared_ptr<mv::i_degree_sign> degree = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						degree = laban_sequence_reader::read_space_measurement(degree_node_set.at(0));

						if (degree == nullptr)
						{
							degree = laban_sequence_reader::read_pin(degree_node_set.at(0));
						}
					}

					result = std::shared_ptr<mv::turn_symbol>(new mv::turn_symbol(direction, dynamics, degree));
				}

				return result;
			}

			std::shared_ptr<mv::vibration_symbol> laban_sequence_reader::read_vibration(xmlpp::Node* node)
			{
				std::shared_ptr<mv::vibration_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet displacement_node_set = node->find("/displacement");

				if (displacement_node_set.size() > 1)
				{
					std::shared_ptr<mv::pin> displacement1 = laban_sequence_reader::read_pin(displacement_node_set.at(0));
					std::shared_ptr<mv::pin> displacement2 = laban_sequence_reader::read_pin(displacement_node_set.at(1));

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find("/dynamics");
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = laban_sequence_reader::read_dynamics(node);
					}

					result = std::shared_ptr<mv::vibration_symbol>(new mv::vibration_symbol(displacement1, displacement2, dynamics));
				}

				return result;
			}

			std::shared_ptr<mv::cancellation_symbol> laban_sequence_reader::read_cancellation(xmlpp::Node* node)
			{
				std::shared_ptr<mv::cancellation_symbol> result = nullptr;

				//cancel
				xmlpp::NodeSet cancel_node_set = node->find("/cancel");

				if (cancel_node_set.size() > 0)
				{
					mv::e_cancel cancel = mv::e_cancel_c::parse(dynamic_cast<xmlpp::ContentNode*>(cancel_node_set.at(0))->get_content());

					result = std::shared_ptr<mv::cancellation_symbol>(new mv::cancellation_symbol(cancel));
				}

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
