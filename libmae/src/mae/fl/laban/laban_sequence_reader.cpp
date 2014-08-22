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
				xmlpp::NodeSet coldefs_node_set = root_node->find(get_xpath("staff/columns/columnDefinition", nsp), *namespace_map);

				for (unsigned int i = 0; i < coldefs_node_set.size(); i++)
				{
					result->add_column_definition(read_column_definition(coldefs_node_set.at(i), namespace_map, nsp));
				}

				//movements
				xmlpp::NodeSet movs_node_set = root_node->find(get_xpath("staff/movements/movement", nsp), *namespace_map);

				for (unsigned int i = 0; i < movs_node_set.size(); i++)
				{
					result->add_movement(read_movement(movs_node_set.at(i), namespace_map, nsp));
				}

				//TODO other i_movements like path, bow, or room dir

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

			std::shared_ptr<column_definition> laban_sequence_reader::read_column_definition(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<column_definition> result = nullptr;

				//staff elements
				unsigned int index = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "index", nsp, "0")));

				std::shared_ptr<ps::i_pre_sign> pre_sign = laban_sequence_reader::read_pre_sign(node, namespace_map, nsp);

				result = std::shared_ptr<column_definition>(new column_definition(index, pre_sign));

				return result;
			}

			std::shared_ptr<ps::i_pre_sign> laban_sequence_reader::read_pre_sign(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_pre_sign> result = nullptr;

				xmlpp::NodeSet body_part_node_set = node->find(get_xpath("preSign/bodyPart", nsp), *namespace_map);
				if (body_part_node_set.size() > 0)
				{
					//side
					ps::e_side side = ps::e_side_c::parse(get_node_content(node, namespace_map, "preSign/bodyPart/side", nsp, "NONE"));

					std::shared_ptr<ps::i_endpoint> endpoint = read_end_point(body_part_node_set.at(0), namespace_map, nsp);

					if (endpoint != nullptr)
					{
						result = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, endpoint));
					}
					else
					{
						std::shared_ptr<ps::i_limb> limb = laban_sequence_reader::read_limb(body_part_node_set.at(0), namespace_map, nsp);

						if (limb != nullptr)
						{
							result = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, limb));
						}
						else
						{
							std::shared_ptr<ps::surface_part> surface = laban_sequence_reader::read_surface(
									body_part_node_set.at(0), namespace_map, nsp);

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
					xmlpp::NodeSet prop_node_set = node->find(get_xpath("preSign/prop", nsp), *namespace_map);

					if (prop_node_set.size() > 0)
					{
						//side
						std::string name = get_node_content(node, namespace_map, "preSign/prop/name", nsp, "");

						//description (optional)
						std::string description = get_node_content(node, namespace_map, "preSign/prop/description", nsp, "");;

						result = std::shared_ptr<ps::i_pre_sign>(new ps::prop(name, description));
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_endpoint> laban_sequence_reader::read_end_point(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_endpoint> result = nullptr;

				//area pre-sign
				xmlpp::NodeSet area_node_set = node->find(get_xpath("part", nsp), *namespace_map);

				if (area_node_set.size() > 0)
				{
					ps::e_area area = ps::e_area_c::parse(get_node_content(node, namespace_map, "part", nsp, "NONE"));

					result = std::shared_ptr<ps::i_endpoint>(new ps::area_part(area));
				}
				else
				{
					//joint pre-sign
					xmlpp::NodeSet joint_node_set = node->find(get_xpath("joint/joint", nsp), *namespace_map);

					if (joint_node_set.size() > 0)
					{
						ps::e_joint joint = ps::e_joint_c::parse(get_node_content(node, namespace_map, "joint/joint", nsp, "NONE"));

						result = std::shared_ptr<ps::i_endpoint>(new ps::joint_part(joint));
					}
					else
					{
						//digit pre-sign
						xmlpp::NodeSet digit_node_set = node->find(get_xpath("digit/digit", nsp), *namespace_map);

						if (digit_node_set.size() > 0)
						{
							ps::e_digit digit = ps::e_digit_c::parse(get_node_content(node, namespace_map, "digit/digit", nsp, "NONE"));

							unsigned int knuckle = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "digit/joint", nsp, "0")));

							result = std::shared_ptr<ps::i_endpoint>(new ps::digit_part(digit, knuckle));
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_limb> laban_sequence_reader::read_limb(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_limb> result = nullptr;

				//default limb pre-sign
				xmlpp::NodeSet default_limb_node_set = node->find(get_xpath("limb/default/limb", nsp), *namespace_map);

				if (default_limb_node_set.size() > 0)
				{
					ps::e_limb limb = ps::e_limb_c::parse(get_node_content(node, namespace_map, "limb/default/limb", nsp, "NONE"));

					result = std::shared_ptr<ps::i_limb>(new ps::default_limb(limb));
				}
				else
				{
					xmlpp::NodeSet custom_limb_node_set = node->find(get_xpath("limb/custom", nsp), *namespace_map);

					if (custom_limb_node_set.size() > 0)
					{
						xmlpp::NodeSet fixed_end_node_set = node->find(get_xpath("limb/custom/fixedEnd", nsp), *namespace_map);

						if (fixed_end_node_set.size() > 0)
						{

							std::shared_ptr<ps::i_endpoint> fixed_end = laban_sequence_reader::read_end_point(
									fixed_end_node_set.at(0), namespace_map, nsp);

							if (fixed_end != nullptr)
							{

								xmlpp::NodeSet extremity_end_node_set = node->find(get_xpath("limb/custom/extremity", nsp), *namespace_map);

								std::shared_ptr<ps::i_endpoint> extremity_end = nullptr;

								if (extremity_end_node_set.size() > 0)
								{
									extremity_end = laban_sequence_reader::read_end_point(extremity_end_node_set.at(0), namespace_map, nsp);
								}

								result = std::shared_ptr<ps::i_limb>(new ps::custom_limb(fixed_end, extremity_end));
							}
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::surface_part> laban_sequence_reader::read_surface(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::surface_part> result = nullptr;

				xmlpp::NodeSet surface_node_set = node->find(get_xpath("surface", nsp), *namespace_map);

				if (surface_node_set.size() > 0)
				{
					std::shared_ptr<ps::i_limb> limb = laban_sequence_reader::read_limb(surface_node_set.at(0), namespace_map, nsp);

					xmlpp::NodeSet limb_side_node_set = node->find(get_xpath("surface/side", nsp), *namespace_map);

					if (limb != nullptr && limb_side_node_set.size() > 0)
					{
						ps::e_limb_side limb_side = ps::e_limb_side_c::parse(get_node_content(node, namespace_map, "surface/side", nsp, "NONE"));

						result = std::shared_ptr<ps::surface_part>(new ps::surface_part(limb_side, limb));
					}
				}

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_movement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<i_movement> result = nullptr;

				int column = std::stoi(get_node_content(node, namespace_map, "column", nsp, "0"));

				unsigned int measure = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "measure", nsp, "0")));

				double beat = std::stod(get_node_content(node, namespace_map, "beat", nsp, "0"));

				double duration = std::stod(get_node_content(node, namespace_map, "duration", nsp, "0"));


				xmlpp::NodeSet pre_sign_node_set = node->find(get_xpath("preSign", nsp), *namespace_map);
				std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr;

				if (pre_sign_node_set.size() > 0)
				{
					pre_sign = laban_sequence_reader::read_pre_sign(node, namespace_map, nsp);
				}

				bool hold = mbool::parse(get_node_content(node, namespace_map, "hold", nsp, "false"));


				xmlpp::NodeSet direction_node_set = node->find(get_xpath("direction", nsp), *namespace_map);

				if (direction_node_set.size() > 0)
				{
					std::shared_ptr<mv::direction_symbol> direction = laban_sequence_reader::read_direction(direction_node_set.at(0), namespace_map, nsp);

					if (direction != nullptr)
					{
						result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, direction, hold, pre_sign));
					}
				}
				else
				{
					xmlpp::NodeSet space_node_set = node->find(get_xpath("space", nsp), *namespace_map);

					if (space_node_set.size() > 0)
					{
						std::shared_ptr<mv::space_symbol> space = laban_sequence_reader::read_space(space_node_set.at(0), namespace_map, nsp);

						if (space != nullptr)
						{
							result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, space, hold, pre_sign));
						}
					}
					else
					{
						xmlpp::NodeSet turn_node_set = node->find(get_xpath("turn", nsp), *namespace_map);

						if (turn_node_set.size() > 0)
						{
							std::shared_ptr<mv::turn_symbol> turn = laban_sequence_reader::read_turn(turn_node_set.at(0), namespace_map, nsp);

							if (turn != nullptr)
							{
								result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, turn, hold, pre_sign));
							}
						}
						else
						{
							xmlpp::NodeSet vibration_node_set = node->find(get_xpath("vibration", nsp), *namespace_map);

							if (vibration_node_set.size() > 0)
							{
								std::shared_ptr<mv::vibration_symbol> vibration = laban_sequence_reader::read_vibration(vibration_node_set.at(0), namespace_map, nsp);

								if (vibration != nullptr)
								{
									result = std::shared_ptr<i_movement>(new movement(column, measure, beat, duration, vibration, hold, pre_sign));
								}
							}
							else
							{
								xmlpp::NodeSet cancel_node_set = node->find(get_xpath("cancel", nsp), *namespace_map);

								if (cancel_node_set.size() > 0)
								{
									std::shared_ptr<mv::cancellation_symbol> cancel = laban_sequence_reader::read_cancellation(cancel_node_set.at(0), namespace_map, nsp);

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

				return result;
			}

			std::shared_ptr<mv::pin> laban_sequence_reader::read_pin(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::pin> result = nullptr;

				mv::e_level vertical = mv::e_level_c::parse(get_node_content(node, namespace_map, "vertical", nsp, "NONE"));

				int horizontal = std::stoi(get_node_content(node, namespace_map, "horizontal", nsp, "0"));

				result = std::shared_ptr<mv::pin>(new mv::pin(vertical, horizontal));

				return result;
			}

			std::shared_ptr<mv::space_measurement> laban_sequence_reader::read_space_measurement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::space_measurement> result = nullptr;

				mv::e_space vertical = mv::e_space_c::parse(get_node_content(node, namespace_map, "spaceMeasurement/type", nsp, "NONE"));

				unsigned int degree = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "spaceMeasurement/degree", nsp, "0")));

				mv::e_space_direction direction = mv::e_space_direction_c::parse(get_node_content(node, namespace_map, "spaceMeasurement/direction", nsp, "NONE"));

				result = std::shared_ptr<mv::space_measurement>(new mv::space_measurement(vertical, degree, direction));

				return result;

			}

			std::shared_ptr<mv::i_dynamics_sign> laban_sequence_reader::read_dynamics(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::i_dynamics_sign> result = nullptr;

				xmlpp::NodeSet accent_node_set = node->find(get_xpath("dynamics/accent", nsp), *namespace_map);

				if (accent_node_set.size() > 0)
				{
					unsigned int accent = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "dynamics/accent", nsp, "0")));
					result = std::shared_ptr<mv::i_dynamics_sign>(new mv::accent_sign(accent));
				}
				else
				{
					xmlpp::NodeSet dynamic_node_set = node->find(get_xpath("dynamics/dynamic", nsp), *namespace_map);

					if (dynamic_node_set.size() > 0)
					{
						mv::e_dynamic dynamic = mv::e_dynamic_c::parse(get_node_content(node, namespace_map, "dynamics/dynamic", nsp, "NONE"));

						result = std::shared_ptr<mv::i_dynamics_sign>(new mv::dynamic_sign(dynamic));
					}
				}

				return result;
			}

			std::shared_ptr<mv::direction_symbol> laban_sequence_reader::read_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::direction_symbol> result = nullptr;

				mv::e_level vertical = mv::e_level_c::parse(get_node_content(node, namespace_map, "vertical", nsp, "NONE"));

				mv::e_direction horizontal = mv::e_direction_c::parse(get_node_content(node, namespace_map, "horizontal", nsp, "NONE"));

				//modification pin
				xmlpp::NodeSet modification_pin_node_set = node->find(get_xpath("modificationPin", nsp), *namespace_map);
				std::shared_ptr<mv::pin> modification_pin = nullptr;

				if (modification_pin_node_set.size() > 0)
				{
					modification_pin = laban_sequence_reader::read_pin(modification_pin_node_set.at(0), namespace_map, nsp);
				}

				//modification pin
				xmlpp::NodeSet relationship_pin_node_set = node->find(get_xpath("relationshipPin", nsp), *namespace_map);
				std::shared_ptr<mv::pin> relationship_pin = nullptr;

				if (relationship_pin_node_set.size() > 0)
				{
					relationship_pin = laban_sequence_reader::read_pin(relationship_pin_node_set.at(0), namespace_map, nsp);
				}


				//spaceMeasurement
				xmlpp::NodeSet space_measurement_node_set = node->find(get_xpath("spaceMeasurement", nsp), *namespace_map);
				std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

				if (space_measurement_node_set.size() > 0)
				{
					space_measurement = laban_sequence_reader::read_space_measurement(node, namespace_map, nsp);
				}

				//dynamics
				xmlpp::NodeSet dynamics_node_set = node->find(get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

				if (dynamics_node_set.size() > 0)
				{
					dynamics = laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
				}

				//dynamics
				mv::e_contact_hook contact_hook = mv::e_contact_hook_c::parse(get_node_content(node, namespace_map, "contactHook", nsp, "NONE"));

				result = std::shared_ptr<mv::direction_symbol>(new mv::direction_symbol(vertical, horizontal, modification_pin, relationship_pin, dynamics, space_measurement, contact_hook));

				return result;
			}

			std::shared_ptr<mv::space_symbol> laban_sequence_reader::read_space(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::space_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet space_measurement_node_set = node->find(get_xpath("spaceMeasurement", nsp), *namespace_map);
				std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

				if (space_measurement_node_set.size() > 0)
				{
					space_measurement = laban_sequence_reader::read_space_measurement(node, namespace_map, nsp);

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find(get_xpath("dynamics", nsp), *namespace_map);
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
					}

					result = std::shared_ptr<mv::space_symbol>(new mv::space_symbol(space_measurement, dynamics));
				}

				return result;
			}

			std::shared_ptr<mv::turn_symbol> laban_sequence_reader::read_turn(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::turn_symbol> result = nullptr;

				//dynamics
				mv::e_turn_direction direction = mv::e_turn_direction_c::parse(get_node_content(node, namespace_map, "direction", nsp, "NONE"));

				//dynamics
				xmlpp::NodeSet dynamics_node_set = node->find(get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

				if (dynamics_node_set.size() > 0)
				{
					dynamics = laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
				}

				//degree
				xmlpp::NodeSet degree_node_set = node->find(get_xpath("degree", nsp), *namespace_map);
				std::shared_ptr<mv::i_degree_sign> degree = nullptr;

				if (dynamics_node_set.size() > 0)
				{
					xmlpp::NodeSet space_degree_node_set = node->find(get_xpath("spaceMeasurement", nsp), *namespace_map);

					if (space_degree_node_set.size() > 0)
					{
						degree = laban_sequence_reader::read_space_measurement(degree_node_set.at(0), namespace_map, nsp);
					}
					else
					{
						degree = laban_sequence_reader::read_pin(degree_node_set.at(0), namespace_map, nsp);
					}
				}

				result = std::shared_ptr<mv::turn_symbol>(new mv::turn_symbol(direction, dynamics, degree));

				return result;
			}

			std::shared_ptr<mv::vibration_symbol> laban_sequence_reader::read_vibration(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::vibration_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet displacement_node_set = node->find(get_xpath("displacement", nsp), *namespace_map);

				if (displacement_node_set.size() > 1)
				{
					std::shared_ptr<mv::pin> displacement1 = laban_sequence_reader::read_pin(displacement_node_set.at(0), namespace_map, nsp);
					std::shared_ptr<mv::pin> displacement2 = laban_sequence_reader::read_pin(displacement_node_set.at(1), namespace_map, nsp);

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find(get_xpath("dynamics", nsp), *namespace_map);
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
					}

					result = std::shared_ptr<mv::vibration_symbol>(new mv::vibration_symbol(displacement1, displacement2, dynamics));
				}

				return result;
			}

			std::shared_ptr<mv::cancellation_symbol> laban_sequence_reader::read_cancellation(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::cancellation_symbol> result = nullptr;

				//cancel
				mv::e_cancel cancel = mv::e_cancel_c::parse(get_node_content(node, namespace_map, "cancel", nsp, "NONE"));

				result = std::shared_ptr<mv::cancellation_symbol>(new mv::cancellation_symbol(cancel));

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_path(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				e_path_type type = e_path_type_c::parse(get_node_content(node, namespace_map, "type", nsp, "NONE"));;

				unsigned int measure = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "measure", nsp, "0")));

				double beat = std::stod(get_node_content(node, namespace_map, "beat", nsp, "0"));

				double duration = std::stod(get_node_content(node, namespace_map, "duration", nsp, "0"));

				std::shared_ptr<i_movement> result = std::shared_ptr<i_movement>(new path(type, measure, beat, duration));

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_room_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{

				unsigned int measure = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "measure", nsp, "0")));

				double beat = std::stod(get_node_content(node, namespace_map, "beat", nsp, "0"));

				xmlpp::NodeSet direction_node_set = node->find(get_xpath("direction", nsp), *namespace_map);
				std::shared_ptr<mv::pin> direction;

				if (direction_node_set.size() > 1)
				{
					direction = read_pin(direction_node_set.at(0), namespace_map, nsp);
				}

				std::shared_ptr<i_movement> result = std::shared_ptr<i_movement>(new room_direction(measure, beat, direction));

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_relationship_bow(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				e_relationship_type type = e_relationship_type_c::parse(get_node_content(node, namespace_map, "type", nsp, "NONE"));

				bool grasping = mbool::parse(get_node_content(node, namespace_map, "grasping", nsp, "false"));

				bool passing = mbool::parse(get_node_content(node, namespace_map, "passing", nsp, "false"));

				bool hold = mbool::parse(get_node_content(node, namespace_map, "hold", nsp, "false"));

				unsigned int measure = static_cast<unsigned int>(std::stoul(get_node_content(node, namespace_map, "measure", nsp, "0")));

				double beat = std::stod(get_node_content(node, namespace_map, "beat", nsp, "0"));

				xmlpp::NodeSet left_relationship_endpoint_node_set = node->find(get_xpath("endPoints/left", nsp), *namespace_map);
				std::shared_ptr<mv::relationship_endpoint> left;

				if (left_relationship_endpoint_node_set.size() > 1)
				{
					left = read_relationship_endpoint(left_relationship_endpoint_node_set.at(0), namespace_map, nsp );
				}

				xmlpp::NodeSet right_relationship_endpoint_node_set = node->find(get_xpath("endPoints/right", nsp), *namespace_map);
				std::shared_ptr<mv::relationship_endpoint> right;

				if (right_relationship_endpoint_node_set.size() > 1)
				{
					right = read_relationship_endpoint(right_relationship_endpoint_node_set.at(0), namespace_map, nsp );
				}

				std::shared_ptr<i_movement> result = std::shared_ptr<i_movement>(new relationship_bow(type, grasping, passing, hold, measure, beat, left, right));

				return result;
			}

			std::shared_ptr<mv::relationship_endpoint> laban_sequence_reader::read_relationship_endpoint(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{

				int column = std::stoi(get_node_content(node, namespace_map, "column", nsp, "0"));

				xmlpp::NodeSet pre_sign_node_set = node->find(get_xpath("preSign", nsp), *namespace_map);
				std::shared_ptr<ps::i_pre_sign> pre_sign;

				if (pre_sign_node_set.size() > 1)
				{
					pre_sign = read_pre_sign(node, namespace_map, nsp);
				}

				xmlpp::NodeSet dynamics_node_set = node->find(get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics;

				if (dynamics_node_set.size() > 1)
				{
					dynamics = read_dynamics(node, namespace_map, nsp);
				}

				bool active = mbool::parse(get_node_content(node, namespace_map, "active", nsp, "false"));

				std::shared_ptr<mv::relationship_endpoint> result = std::shared_ptr<mv::relationship_endpoint>(new mv::relationship_endpoint(column, active, pre_sign, dynamics));

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
