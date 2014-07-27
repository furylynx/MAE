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

			std::shared_ptr<laban_sequence>  laban_sequence_reader::read_sequence(std::string xml_string)
			{
				std::shared_ptr<laban_sequence> result;

				std::stringstream sstr;
				sstr << xml_string;

				xmlpp::DomParser parser;
				parser.parse_stream(sstr);

				xmlpp::Document* doc = parser.get_document();
				xmlpp::Node* root_node = doc->get_root_node();

				//---------------
				// main elements
				//---------------
				xmlpp::NodeSet title_node_set = root_node->find("/score/title");
				std::string title = "unknown";

				if (title_node_set.size() > 0)
				{
					title = dynamic_cast<xmlpp::ContentNode*>(title_node_set.at(0))->get_content();
				}

				xmlpp::NodeSet authors_node_set = root_node->find("/score/author");
				std::vector<std::string> authors;

				if (authors_node_set.size() == 0)
				{
					authors.push_back("anonymous");
				}
				else
				{
					for (unsigned int i = 0; i < authors_node_set.size(); i++)
					{
						authors.push_back(dynamic_cast<xmlpp::ContentNode*>(authors_node_set.at(i))->get_content());
					}
				}


				//staff elements
				xmlpp::NodeSet measures_node_set = root_node->find("/score/staff/measures");
				unsigned int measures = 0;

				if (measures_node_set.size() > 0)
				{
					measures = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(measures_node_set.at(0))->get_content().c_str()));
				}

				xmlpp::NodeSet time_unit_node_set = root_node->find("/score/staff/timing/timeUnit");
				e_time_unit time_unit = e_time_unit::NONE;

				if (time_unit_node_set.size() > 0)
				{
					std::string time_unit_str = dynamic_cast<xmlpp::ContentNode*>(time_unit_node_set.at(0))->get_content();
					time_unit = e_time_unit_c::parse(time_unit_str);
				}

				xmlpp::NodeSet beat_duration_node_set = root_node->find("/score/staff/timing/measure/beatDuration");
				unsigned int beat_duration = 0;

				if (beat_duration_node_set.size() > 0)
				{
					beat_duration = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(beat_duration_node_set.at(0))->get_content()));
				}

				xmlpp::NodeSet beats_node_set = root_node->find("/score/staff/timing/measure/beats");
				unsigned int beats = 0;

				if (beats_node_set.size() > 0)
				{
					beats = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(beats_node_set.at(0))->get_content()));
				}

				//create the sequence and add additional information as well as columns and movements
				result = std::shared_ptr<laban_sequence>(new laban_sequence(title, authors.at(0), measures, time_unit, beat_duration, beats));

				//additional elements

				//decription
				xmlpp::NodeSet description_node_set = root_node->find("/score/description");

				if (description_node_set.size() > 0)
				{
					result->set_description(dynamic_cast<xmlpp::ContentNode*>(description_node_set.at(0))->get_content());
				}


				//column definitions
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

			std::shared_ptr<column_definition> laban_sequence_reader::read_column_definition(xmlpp::Node* node)
			{
				std::shared_ptr<column_definition> result;
				std::shared_ptr<ps::i_pre_sign> pre_sign;

				//staff elements
				xmlpp::NodeSet index_node_set = node->find("/index");
				unsigned int index = 0;

				if (index_node_set.size() > 0)
				{
				 	index = static_cast<unsigned int>(std::stoi(dynamic_cast<xmlpp::ContentNode*>(index_node_set.at(0))->get_content()));
				}

				xmlpp::NodeSet body_part_node_set = node->find("/preSign/bodyPart");
				if (body_part_node_set.size() > 0)
				{
					//side
					xmlpp::NodeSet side_node_set = node->find("/preSign/bodyPart/side");
					ps::e_side side = ps::e_side::NONE;

					if (side_node_set.size() > 0)
					{
						side = ps::e_side_c::parse(dynamic_cast<xmlpp::ContentNode*>(side_node_set.at(0))->get_content());
					}


					//area pre-sign
					xmlpp::NodeSet area_node_set = node->find("/preSign/bodyPart/part");

					if (side_node_set.size() > 0)
					{
						ps::e_area area = ps::e_area_c::parse(dynamic_cast<xmlpp::ContentNode*>(area_node_set.at(0))->get_content());

						pre_sign = std::shared_ptr<ps::i_pre_sign>(new ps::body_part(side, std::shared_ptr<ps::i_part>(new ps::area_part(area))));
					}
					else
					{
						if (true)//TODO next part
						{

						}
					}


					//TODO any other information
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

						pre_sign = std::shared_ptr<ps::i_pre_sign>(new ps::prop(name, description));
					}
				}

				result = std::shared_ptr<column_definition>(new column_definition(index, pre_sign));

				return result;
			}

			std::shared_ptr<i_movement> laban_sequence_reader::read_movement(xmlpp::Node* node)
			{
				std::shared_ptr<i_movement> result;

				//TODO read xml

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
