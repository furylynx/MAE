#include "internal_laban_sequence_reader.hh"

//internal includes
#include "../../internal_mxml.hh"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			internal_laban_sequence_reader::internal_laban_sequence_reader()
			{
			}

			internal_laban_sequence_reader::~internal_laban_sequence_reader()
			{
			}

			std::shared_ptr<laban_sequence> internal_laban_sequence_reader::read_sequence_file(std::string file_name)
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

			std::shared_ptr<laban_sequence> internal_laban_sequence_reader::read_sequence_str(std::string xml_string)
			{
				std::shared_ptr<laban_sequence> result;

				std::stringstream sstr;
				sstr << xml_string;

				xmlpp::DomParser parser;
				parser.parse_stream(sstr);

				xmlpp::Document* doc = parser.get_document();
				xmlpp::Node* root_node = doc->get_root_node();

				//setup namespace prefix
				std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map = std::make_shared<xmlpp::Node::PrefixNsMap>();
				if (root_node->get_namespace_prefix().size() > 0)
				{
					namespace_map->insert(std::make_pair(root_node->get_namespace_prefix(), root_node->get_namespace_uri()));
				}

				std::string nsp = root_node->get_namespace_prefix();

				//---------------
				// main elements
				//---------------

				std::string title = internal_mxml::get_node_content(root_node, namespace_map, "title", nsp, "unknown");

				std::vector<std::string> authors = internal_mxml::get_node_contents(root_node, namespace_map, "author", nsp, "anonymous");

				//staff elements
				std::string measures_string = internal_mxml::get_node_content(root_node, namespace_map, "staff/measures", nsp, "0");
				unsigned int measures = static_cast<unsigned int>(std::atoi(measures_string.c_str()));

				e_time_unit time_unit = e_time_unit_c::parse(internal_mxml::get_node_content(root_node, namespace_map, "staff/timing/timeUnit", nsp, "NONE"));

				std::string beat_duration_string = internal_mxml::get_node_content(root_node, namespace_map, "staff/timing/measure/beatDuration", nsp, "0");
				unsigned int beat_duration = static_cast<unsigned int>(std::atoi(beat_duration_string.c_str()));

				std::string beats_string = internal_mxml::get_node_content(root_node, namespace_map, "staff/timing/measure/beats", nsp, "0");
				unsigned int beats = static_cast<unsigned int>(std::atoi(beats_string.c_str()));

				//create the sequence and add additional information as well as columns and movements
				result = std::make_shared<laban_sequence>(title, authors.at(0), measures, time_unit, beat_duration, beats);

				//additional elements

				//other authors
				for (unsigned int i = 1; i < authors.size(); i++)
				{
					result->add_author(authors.at(i));
				}

				//decription
				std::string description = internal_mxml::get_node_content(root_node, namespace_map, "description", nsp, "");

				if (description.size() > 0)
				{
					result->set_description(description);
				}

				//column definitions
				xmlpp::NodeSet coldefs_node_set = root_node->find(internal_mxml::get_xpath("staff/columns/columnDefinition", nsp), *namespace_map);

				for (unsigned int i = 0; i < coldefs_node_set.size(); i++)
				{
					result->add_column_definition(read_column_definition(coldefs_node_set.at(i), namespace_map, nsp));
				}

				//movements
				xmlpp::NodeSet movs_node_set = root_node->find(internal_mxml::get_xpath("staff/movements/movement", nsp), *namespace_map);

				for (unsigned int i = 0; i < movs_node_set.size(); i++)
				{
					result->add_movement(read_movement(movs_node_set.at(i), namespace_map, nsp));
				}

				//paths
				xmlpp::NodeSet paths_node_set = root_node->find(internal_mxml::get_xpath("staff/movements/path", nsp), *namespace_map);

				for (unsigned int i = 0; i < paths_node_set.size(); i++)
				{
					result->add_movement(read_path(paths_node_set.at(i), namespace_map, nsp));
				}

				//relationship
				xmlpp::NodeSet relationship_node_set = root_node->find(internal_mxml::get_xpath("staff/movements/relationship", nsp), *namespace_map);

				for (unsigned int i = 0; i < relationship_node_set.size(); i++)
				{
					result->add_movement(read_relationship_bow(relationship_node_set.at(i), namespace_map, nsp));
				}

				//roomDirections
				xmlpp::NodeSet roomdir_node_set = root_node->find(internal_mxml::get_xpath("staff/movements/roomDirection", nsp), *namespace_map);

				for (unsigned int i = 0; i < roomdir_node_set.size(); i++)
				{
					result->add_movement(read_room_direction(roomdir_node_set.at(i), namespace_map, nsp));
				}

				//done
				return result;
			}

			std::shared_ptr<column_definition> internal_laban_sequence_reader::read_column_definition(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<column_definition> result = nullptr;

				//staff elements
				std::string index_string = internal_mxml::get_node_content(node, namespace_map, "index", nsp, "0");
				unsigned int index = static_cast<unsigned int>(std::atoi(index_string.c_str()));

				std::shared_ptr<ps::i_pre_sign> pre_sign = internal_laban_sequence_reader::read_pre_sign(node, namespace_map, nsp);

				result = std::make_shared<column_definition>(index, pre_sign);

				return result;
			}

			std::shared_ptr<ps::i_pre_sign> internal_laban_sequence_reader::read_pre_sign(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_pre_sign> result = nullptr;

				xmlpp::NodeSet body_part_node_set = node->find(internal_mxml::get_xpath("preSign/bodyPart", nsp), *namespace_map);
				if (body_part_node_set.size() > 0)
				{
					//side
					ps::e_side side = ps::e_side_c::parse(internal_mxml::get_node_content(node, namespace_map, "preSign/bodyPart/side", nsp, "NONE"));

					std::shared_ptr<ps::i_endpoint> endpoint = read_end_point(body_part_node_set.at(0), namespace_map, nsp);

					if (endpoint != nullptr)
					{
						result = std::make_shared<ps::body_part>(side, endpoint);
					}
					else
					{
						std::shared_ptr<ps::i_limb> limb = internal_laban_sequence_reader::read_limb(body_part_node_set.at(0), namespace_map, nsp);

						if (limb != nullptr)
						{
							result = std::make_shared<ps::body_part>(side, limb);
						}
						else
						{
							std::shared_ptr<ps::surface_part> surface = internal_laban_sequence_reader::read_surface(
									body_part_node_set.at(0), namespace_map, nsp);

							if (surface != nullptr)
							{
								result = std::make_shared<ps::body_part>(side, surface);
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
					xmlpp::NodeSet prop_node_set = node->find(internal_mxml::get_xpath("preSign/prop", nsp), *namespace_map);

					if (prop_node_set.size() > 0)
					{
						//side
						std::string name = internal_mxml::get_node_content(node, namespace_map, "preSign/prop/name", nsp, "");

						//description (optional)
						std::string description = internal_mxml::get_node_content(node, namespace_map, "preSign/prop/description", nsp, "");;

						result = std::make_shared<ps::prop>(name, description);
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_endpoint> internal_laban_sequence_reader::read_end_point(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_endpoint> result = nullptr;

				//area pre-sign
				xmlpp::NodeSet area_node_set = node->find(internal_mxml::get_xpath("part", nsp), *namespace_map);

				if (area_node_set.size() > 0)
				{
					ps::e_area area = ps::e_area_c::parse(internal_mxml::get_node_content(node, namespace_map, "part", nsp, "NONE"));

					result = std::make_shared<ps::area_part>(area);
				}
				else
				{
					//joint pre-sign
					xmlpp::NodeSet joint_node_set = node->find(internal_mxml::get_xpath("joint/joint", nsp), *namespace_map);

					if (joint_node_set.size() > 0)
					{
						ps::e_joint joint = ps::e_joint_c::parse(internal_mxml::get_node_content(node, namespace_map, "joint/joint", nsp, "NONE"));

						result = std::make_shared<ps::joint_part>(joint);
					}
					else
					{
						//digit pre-sign
						xmlpp::NodeSet digit_node_set = node->find(internal_mxml::get_xpath("digit/digit", nsp), *namespace_map);

						if (digit_node_set.size() > 0)
						{
							ps::e_digit digit = ps::e_digit_c::parse(internal_mxml::get_node_content(node, namespace_map, "digit/digit", nsp, "NONE"));

							std::string knuckle_string = internal_mxml::get_node_content(node, namespace_map, "digit/joint", nsp, "0");
							unsigned int knuckle = static_cast<unsigned int>(std::atoi(knuckle_string.c_str()));

							result = std::make_shared<ps::digit_part>(digit, knuckle);
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::i_limb> internal_laban_sequence_reader::read_limb(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::i_limb> result = nullptr;

				//default limb pre-sign
				xmlpp::NodeSet default_limb_node_set = node->find(internal_mxml::get_xpath("limb/default/limb", nsp), *namespace_map);

				if (default_limb_node_set.size() > 0)
				{
					ps::e_limb limb = ps::e_limb_c::parse(internal_mxml::get_node_content(node, namespace_map, "limb/default/limb", nsp, "NONE"));

					result = std::make_shared<ps::default_limb>(limb);
				}
				else
				{
					xmlpp::NodeSet custom_limb_node_set = node->find(internal_mxml::get_xpath("limb/custom", nsp), *namespace_map);

					if (custom_limb_node_set.size() > 0)
					{
						xmlpp::NodeSet extremity_end_node_set = node->find(internal_mxml::get_xpath("limb/custom/extremity", nsp), *namespace_map);

						if (extremity_end_node_set.size() > 0)
						{

							std::shared_ptr<ps::i_endpoint> extremity_end = internal_laban_sequence_reader::read_end_point(
									extremity_end_node_set.at(0), namespace_map, nsp);

							if (extremity_end != nullptr)
							{

								xmlpp::NodeSet fixed_end_node_set  = node->find(internal_mxml::get_xpath("limb/custom/fixedEnd", nsp), *namespace_map);

								std::shared_ptr<ps::i_endpoint> fixed_end = nullptr;

								if (fixed_end_node_set.size() > 0)
								{
									fixed_end = internal_laban_sequence_reader::read_end_point(fixed_end_node_set.at(0), namespace_map, nsp);
								}

								result = std::make_shared<ps::custom_limb>(extremity_end, fixed_end);
							}
						}
					}
				}

				return result;
			}

			std::shared_ptr<ps::surface_part> internal_laban_sequence_reader::read_surface(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<ps::surface_part> result = nullptr;

				xmlpp::NodeSet surface_node_set = node->find(internal_mxml::get_xpath("surface", nsp), *namespace_map);

				if (surface_node_set.size() > 0)
				{
					std::shared_ptr<ps::i_limb> limb = internal_laban_sequence_reader::read_limb(surface_node_set.at(0), namespace_map, nsp);

					xmlpp::NodeSet limb_side_node_set = node->find(internal_mxml::get_xpath("surface/side", nsp), *namespace_map);

					if (limb != nullptr && limb_side_node_set.size() > 0)
					{
						ps::e_limb_side limb_side = ps::e_limb_side_c::parse(internal_mxml::get_node_content(node, namespace_map, "surface/side", nsp, "NONE"));

						result = std::make_shared<ps::surface_part>(limb_side, limb);
					}
				}

				return result;
			}

			std::shared_ptr<i_movement> internal_laban_sequence_reader::read_movement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<i_movement> result = nullptr;

				std::string column_string = internal_mxml::get_node_content(node, namespace_map, "column", nsp, "0");
				int column = std::atoi(column_string.c_str());

				std::string measure_string = internal_mxml::get_node_content(node, namespace_map, "measure", nsp, "0");
				unsigned int measure = static_cast<unsigned int>(std::atoi(measure_string.c_str()));

				std::string beat_string = internal_mxml::get_node_content(node, namespace_map, "beat", nsp, "0");
				double beat = std::atof(beat_string.c_str());

				std::string duration_string = internal_mxml::get_node_content(node, namespace_map, "duration", nsp, "0");
				double duration = std::atof(duration_string.c_str());


				xmlpp::NodeSet pre_sign_node_set = node->find(internal_mxml::get_xpath("preSign", nsp), *namespace_map);
				std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr;

				if (pre_sign_node_set.size() > 0)
				{
					pre_sign = internal_laban_sequence_reader::read_pre_sign(node, namespace_map, nsp);
				}

				bool hold = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "hold", nsp, "false"));


				xmlpp::NodeSet direction_node_set = node->find(internal_mxml::get_xpath("direction", nsp), *namespace_map);

				if (direction_node_set.size() > 0)
				{
					std::shared_ptr<mv::direction_symbol> direction = internal_laban_sequence_reader::read_direction(direction_node_set.at(0), namespace_map, nsp);

					if (direction != nullptr)
					{
						result = std::make_shared<movement>(column, measure, beat, duration, direction, hold, pre_sign);
					}
				}
				else
				{
					xmlpp::NodeSet space_node_set = node->find(internal_mxml::get_xpath("space", nsp), *namespace_map);

					if (space_node_set.size() > 0)
					{
						std::shared_ptr<mv::space_symbol> space = internal_laban_sequence_reader::read_space(space_node_set.at(0), namespace_map, nsp);

						if (space != nullptr)
						{
							result = std::make_shared<movement>(column, measure, beat, duration, space, hold, pre_sign);
						}
					}
					else
					{
						xmlpp::NodeSet turn_node_set = node->find(internal_mxml::get_xpath("turn", nsp), *namespace_map);

						if (turn_node_set.size() > 0)
						{
							std::shared_ptr<mv::turn_symbol> turn = internal_laban_sequence_reader::read_turn(turn_node_set.at(0), namespace_map, nsp);

							if (turn != nullptr)
							{
								result = std::make_shared<movement>(column, measure, beat, duration, turn, hold, pre_sign);
							}
						}
						else
						{
							xmlpp::NodeSet vibration_node_set = node->find(internal_mxml::get_xpath("vibration", nsp), *namespace_map);

							if (vibration_node_set.size() > 0)
							{
								std::shared_ptr<mv::vibration_symbol> vibration = internal_laban_sequence_reader::read_vibration(vibration_node_set.at(0), namespace_map, nsp);

								if (vibration != nullptr)
								{
									result = std::make_shared<movement>(column, measure, beat, duration, vibration, hold, pre_sign);
								}
							}
							else
							{
								xmlpp::NodeSet cancel_node_set = node->find(internal_mxml::get_xpath("cancel", nsp), *namespace_map);

								if (cancel_node_set.size() > 0)
								{
									std::shared_ptr<mv::cancellation_symbol> cancel = internal_laban_sequence_reader::read_cancellation(cancel_node_set.at(0), namespace_map, nsp);

									if (cancel != nullptr)
									{
										result = std::make_shared<movement>(column, measure, beat, duration, cancel, hold, pre_sign);
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

			std::shared_ptr<mv::pin> internal_laban_sequence_reader::read_pin(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::pin> result = nullptr;

				mv::e_level vertical = mv::e_level_c::parse(internal_mxml::get_node_content(node, namespace_map, "vertical", nsp, "NONE"));

				std::string horizontal_string = internal_mxml::get_node_content(node, namespace_map, "horizontal", nsp, "0");
				int horizontal = std::atoi(horizontal_string.c_str());

				result = std::make_shared<mv::pin>(vertical, horizontal);

				return result;
			}

			std::shared_ptr<mv::space_measurement> internal_laban_sequence_reader::read_space_measurement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::space_measurement> result = nullptr;

				mv::e_space vertical = mv::e_space_c::parse(internal_mxml::get_node_content(node, namespace_map, "type", nsp, "NONE"));

				std::string degree_string = internal_mxml::get_node_content(node, namespace_map, "degree", nsp, "0");
				unsigned int degree = static_cast<unsigned int>(std::atoi(degree_string.c_str()));

				mv::e_space_direction direction = mv::e_space_direction_c::parse(internal_mxml::get_node_content(node, namespace_map, "direction", nsp, "NONE"));

				result = std::make_shared<mv::space_measurement>(vertical, degree, direction);

				return result;

			}

			std::shared_ptr<mv::i_dynamics_sign> internal_laban_sequence_reader::read_dynamics(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::i_dynamics_sign> result = nullptr;

				xmlpp::NodeSet accent_node_set = node->find(internal_mxml::get_xpath("dynamics/accent", nsp), *namespace_map);

				if (accent_node_set.size() > 0)
				{
					std::string accent_string = internal_mxml::get_node_content(node, namespace_map, "dynamics/accent", nsp, "0");
					unsigned int accent = static_cast<unsigned int>(std::atoi(accent_string.c_str()));
					result = std::make_shared<mv::accent_sign>(accent);
				}
				else
				{
					xmlpp::NodeSet dynamic_node_set = node->find(internal_mxml::get_xpath("dynamics/dynamic", nsp), *namespace_map);

					if (dynamic_node_set.size() > 0)
					{
						mv::e_dynamic dynamic = mv::e_dynamic_c::parse(internal_mxml::get_node_content(node, namespace_map, "dynamics/dynamic", nsp, "NONE"));

						result = std::make_shared<mv::dynamic_sign>(dynamic);
					}
				}

				return result;
			}

			std::shared_ptr<mv::direction_symbol> internal_laban_sequence_reader::read_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::direction_symbol> result = nullptr;

				mv::e_level vertical = mv::e_level_c::parse(internal_mxml::get_node_content(node, namespace_map, "vertical", nsp, "NONE"));

				mv::e_direction horizontal = mv::e_direction_c::parse(internal_mxml::get_node_content(node, namespace_map, "horizontal", nsp, "NONE"));

				//modification pin
				xmlpp::NodeSet modification_pin_node_set = node->find(internal_mxml::get_xpath("modificationPin", nsp), *namespace_map);
				std::shared_ptr<mv::pin> modification_pin = nullptr;

				if (modification_pin_node_set.size() > 0)
				{
					modification_pin = internal_laban_sequence_reader::read_pin(modification_pin_node_set.at(0), namespace_map, nsp);
				}

				//modification pin
				xmlpp::NodeSet relationship_pin_node_set = node->find(internal_mxml::get_xpath("relationshipPin", nsp), *namespace_map);
				std::shared_ptr<mv::pin> relationship_pin = nullptr;

				if (relationship_pin_node_set.size() > 0)
				{
					relationship_pin = internal_laban_sequence_reader::read_pin(relationship_pin_node_set.at(0), namespace_map, nsp);
				}


				//spaceMeasurement
				xmlpp::NodeSet space_measurement_node_set = node->find(internal_mxml::get_xpath("spaceMeasurement", nsp), *namespace_map);
				std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

				if (space_measurement_node_set.size() > 0)
				{
					space_measurement = internal_laban_sequence_reader::read_space_measurement(space_measurement_node_set.at(0), namespace_map, nsp);
				}

				//dynamics
				xmlpp::NodeSet dynamics_node_set = node->find(internal_mxml::get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

				if (dynamics_node_set.size() > 0)
				{
					dynamics = internal_laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
				}

				//dynamics
				mv::e_contact_hook contact_hook = mv::e_contact_hook_c::parse(internal_mxml::get_node_content(node, namespace_map, "contactHook", nsp, "NONE"));

				result = std::make_shared<mv::direction_symbol>(vertical, horizontal, modification_pin, relationship_pin, dynamics, space_measurement, contact_hook);

				return result;
			}

			std::shared_ptr<mv::space_symbol> internal_laban_sequence_reader::read_space(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::space_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet space_measurement_node_set = node->find(internal_mxml::get_xpath("spaceMeasurement", nsp), *namespace_map);
				std::shared_ptr<mv::space_measurement> space_measurement = nullptr;

				if (space_measurement_node_set.size() > 0)
				{
					space_measurement = internal_laban_sequence_reader::read_space_measurement(space_measurement_node_set.at(0), namespace_map, nsp);

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find(internal_mxml::get_xpath("dynamics", nsp), *namespace_map);
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = internal_laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
					}

					result = std::make_shared<mv::space_symbol>(space_measurement, dynamics);
				}

				return result;
			}

			std::shared_ptr<mv::turn_symbol> internal_laban_sequence_reader::read_turn(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::turn_symbol> result = nullptr;

				//dynamics
				mv::e_turn_direction direction = mv::e_turn_direction_c::parse(internal_mxml::get_node_content(node, namespace_map, "direction", nsp, "NONE"));

				//dynamics
				xmlpp::NodeSet dynamics_node_set = node->find(internal_mxml::get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

				if (dynamics_node_set.size() > 0)
				{
					dynamics = internal_laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
				}

				//degree
				xmlpp::NodeSet degree_node_set = node->find(internal_mxml::get_xpath("degree", nsp), *namespace_map);
				std::shared_ptr<mv::i_degree_sign> degree = nullptr;

				if (degree_node_set.size() > 0)
				{
					xmlpp::NodeSet space_degree_node_set = node->find(internal_mxml::get_xpath("degree/qualitative", nsp), *namespace_map);

					if (space_degree_node_set.size() > 0)
					{
						degree = internal_laban_sequence_reader::read_space_measurement(space_degree_node_set.at(0), namespace_map, nsp);
					}
					else
					{
						xmlpp::NodeSet pin_degree_node_set = node->find(internal_mxml::get_xpath("degree/quantitative", nsp), *namespace_map);

						if (pin_degree_node_set.size() > 0)
						{
							degree = internal_laban_sequence_reader::read_pin(pin_degree_node_set.at(0), namespace_map, nsp);
						}
					}
				}

				result = std::make_shared<mv::turn_symbol>(direction, dynamics, degree);

				return result;
			}

			std::shared_ptr<mv::vibration_symbol> internal_laban_sequence_reader::read_vibration(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::vibration_symbol> result = nullptr;

				//dynamics
				xmlpp::NodeSet displacement_node_set = node->find(internal_mxml::get_xpath("displacement", nsp), *namespace_map);

				if (displacement_node_set.size() > 1)
				{
					std::shared_ptr<mv::pin> displacement1 = internal_laban_sequence_reader::read_pin(displacement_node_set.at(0), namespace_map, nsp);
					std::shared_ptr<mv::pin> displacement2 = internal_laban_sequence_reader::read_pin(displacement_node_set.at(1), namespace_map, nsp);

					//dynamics
					xmlpp::NodeSet dynamics_node_set = node->find(internal_mxml::get_xpath("dynamics", nsp), *namespace_map);
					std::shared_ptr<mv::i_dynamics_sign> dynamics = nullptr;

					if (dynamics_node_set.size() > 0)
					{
						dynamics = internal_laban_sequence_reader::read_dynamics(node, namespace_map, nsp);
					}

					result = std::make_shared<mv::vibration_symbol>(displacement1, displacement2, dynamics);
				}

				return result;
			}

			std::shared_ptr<mv::cancellation_symbol> internal_laban_sequence_reader::read_cancellation(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<mv::cancellation_symbol> result = nullptr;

				//cancel
				mv::e_cancel cancel = mv::e_cancel_c::parse(internal_mxml::get_node_content(node, namespace_map, "cancel", nsp, "NONE"));

				result = std::make_shared<mv::cancellation_symbol>(cancel);

				return result;
			}

			std::shared_ptr<i_movement> internal_laban_sequence_reader::read_path(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				e_path_type type = e_path_type_c::parse(internal_mxml::get_node_content(node, namespace_map, "type", nsp, "NONE"));;

				std::string measure_string = internal_mxml::get_node_content(node, namespace_map, "measure", nsp, "0");
				unsigned int measure = static_cast<unsigned int>(std::atoi(measure_string.c_str()));

				std::string beat_string = internal_mxml::get_node_content(node, namespace_map, "beat", nsp, "0");
				double beat = std::atof(beat_string.c_str());

				std::string duration_string = internal_mxml::get_node_content(node, namespace_map, "duration", nsp, "0");
				double duration = std::atof(duration_string.c_str());

				std::shared_ptr<i_movement> result = std::make_shared<path>(type, measure, beat, duration);

				return result;
			}

			std::shared_ptr<i_movement> internal_laban_sequence_reader::read_room_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{

				std::string measure_string = internal_mxml::get_node_content(node, namespace_map, "measure", nsp, "0");
				unsigned int measure = static_cast<unsigned int>(std::atoi(measure_string.c_str()));

				std::string beat_string = internal_mxml::get_node_content(node, namespace_map, "beat", nsp, "0");
				double beat = std::atof(beat_string.c_str());

				xmlpp::NodeSet direction_node_set = node->find(internal_mxml::get_xpath("direction", nsp), *namespace_map);
				std::shared_ptr<mv::pin> direction;

				if (direction_node_set.size() > 0)
				{
					direction = read_pin(direction_node_set.at(0), namespace_map, nsp);
				}

				std::shared_ptr<i_movement> result = std::make_shared<room_direction>(measure, beat, direction);

				return result;
			}

			std::shared_ptr<i_movement> internal_laban_sequence_reader::read_relationship_bow(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				e_relationship_type type = e_relationship_type_c::parse(internal_mxml::get_node_content(node, namespace_map, "type", nsp, "NONE"));

				bool grasping = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "grasping", nsp, "false"));

				bool passing = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "passing", nsp, "false"));

				bool hold = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "hold", nsp, "false"));

				std::string measure_string = internal_mxml::get_node_content(node, namespace_map, "measure", nsp, "0");
				unsigned int measure = static_cast<unsigned int>(std::atoi(measure_string.c_str()));

				std::string beat_string = internal_mxml::get_node_content(node, namespace_map, "beat", nsp, "0");
				double beat = std::atof(beat_string.c_str());

				xmlpp::NodeSet left_relationship_endpoint_node_set = node->find(internal_mxml::get_xpath("endPoints/left", nsp), *namespace_map);
				std::shared_ptr<mv::relationship_endpoint> left;

				if (left_relationship_endpoint_node_set.size() > 0)
				{
					left = read_relationship_endpoint(left_relationship_endpoint_node_set.at(0), namespace_map, nsp );
				}

				xmlpp::NodeSet right_relationship_endpoint_node_set = node->find(internal_mxml::get_xpath("endPoints/right", nsp), *namespace_map);
				std::shared_ptr<mv::relationship_endpoint> right;

				if (right_relationship_endpoint_node_set.size() > 0)
				{
					right = read_relationship_endpoint(right_relationship_endpoint_node_set.at(0), namespace_map, nsp );
				}

				std::shared_ptr<i_movement> result = std::make_shared<relationship_bow>(type, grasping, passing, hold, measure, beat, left, right);

				return result;
			}

			std::shared_ptr<mv::relationship_endpoint> internal_laban_sequence_reader::read_relationship_endpoint(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{

				std::string column_string = internal_mxml::get_node_content(node, namespace_map, "column", nsp, "0");
				int column = std::atoi(column_string.c_str());

				xmlpp::NodeSet pre_sign_node_set = node->find(internal_mxml::get_xpath("preSign", nsp), *namespace_map);
				std::shared_ptr<ps::i_pre_sign> pre_sign;

				if (pre_sign_node_set.size() > 0)
				{
					pre_sign = read_pre_sign(node, namespace_map, nsp);
				}

				xmlpp::NodeSet dynamics_node_set = node->find(internal_mxml::get_xpath("dynamics", nsp), *namespace_map);
				std::shared_ptr<mv::i_dynamics_sign> dynamics;

				if (dynamics_node_set.size() > 0)
				{
					dynamics = read_dynamics(node, namespace_map, nsp);
				}

				bool active = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "active", nsp, "false"));

				std::shared_ptr<mv::relationship_endpoint> result = std::make_shared<mv::relationship_endpoint>(column, active, pre_sign, dynamics);

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
