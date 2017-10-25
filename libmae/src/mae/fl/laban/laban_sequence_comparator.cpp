//
// Created by furylynx on 2017-10-23
//

#include "laban_sequence_comparator.hpp"



namespace mae
{
    namespace fl
    {
        namespace laban
        {

            laban_sequence_comparator::laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<i_movement> > > > distance_measure, unsigned int steps_per_beat)
            {
                distance_measure_ = distance_measure;
                steps_per_beat_ = steps_per_beat;

                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_ARM));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_ARM));
            }

            laban_sequence_comparator::~laban_sequence_comparator()
            {

            }

            double laban_sequence_comparator::distance(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                //map columns to each other and find unmappable columns
                std::vector<std::shared_ptr<column_definition> > el1_coldefs = element1->get_column_definitions();
                std::vector<std::shared_ptr<column_definition> > el2_coldefs = element2->get_column_definitions();


                std::unordered_map<int,int> mapped_columns;
                std::unordered_map<int,int> mapped_columns_2_to_1;
                std::unordered_map<bool,std::shared_ptr<column_definition> > prel_unmappable_columns;
                std::unordered_map<bool,std::shared_ptr<column_definition> > unmappable_columns;

                for (std::size_t i = 0; i < el1_coldefs.size(); i++)
                {
                    std::shared_ptr<column_definition> coldef = el1_coldefs.at(i);
                    int col_id = coldef->get_column_index();

                    if (coldef->equals(element2->get_column_definition(col_id)))
                    {
                        //column is defined at the same id on both sequences
                        mapped_columns[col_id] = col_id;
                        mapped_columns_2_to_1[col_id] = col_id;
                    }
                    else
                    {
                        //find matching coldef
                        bool found_match = false;
                        for (std::size_t j = 0; j < el2_coldefs.size() ; j++)
                        {
                            if (coldef->equals(el2_coldefs.at(j)))
                            {
                                //matching column definition found
                                mapped_columns[col_id] = el2_coldefs.at(j)->get_column_index();
                                mapped_columns_2_to_1[el2_coldefs.at(j)->get_column_index()] = col_id;

                                found_match = true;
                                break;
                            }
                        }

                        if (!found_match)
                        {
                            //no matching column definition found
                            prel_unmappable_columns[true] = coldef;
                        }
                    }
                }

                if (el2_coldefs.size() != mapped_columns_2_to_1.size())
                {
                    //check unmappable columns from sequence 2
                    for (std::size_t i = 0; i < el2_coldefs.size(); i++)
                    {
                        int col2_id = el2_coldefs.at(i)->get_column_index();

                        if (mapped_columns_2_to_1.find(col2_id) == mapped_columns_2_to_1.end())
                        {
                            prel_unmappable_columns[false] = el2_coldefs.at(i);
                        }
                    }
                }

                //check mapping for unmappable within default columns
                for (std::pair<bool,int> pair : prel_unmappable_columns)
                {
                    bool is_element_1 = pair.first;
                    std::shared_ptr<column_definition> coldef = pair.second;

                    bool found_match = false;

                    for (std::size_t i = 0; i < default_definitions_.size() ; i++)
                    {
                        if (coldef->equals(default_definitions_.at(i)))
                        {
                            if (is_element_1)
                            {
                                if (mapped_columns_2_to_1.find(default_definitions_.at(i)->get_column_index()) == mapped_columns_2_to_1.end())
                                {
                                    //matching column definition found in default definition
                                    mapped_columns[coldef->get_column_index()] = default_definitions_.at(i)->get_column_index();
                                    mapped_columns_2_to_1[default_definitions_.at(i)->get_column_index()] = coldef->get_column_index();

                                    found_match = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (mapped_columns.find(default_definitions_.at(i)->get_column_index()) == mapped_columns.end())
                                {
                                    //TODO change correctly
                                    //matching column definition found in default definition
                                    mapped_columns[default_definitions_.at(i)->get_column_index()] = coldef->get_column_index();
                                    mapped_columns_2_to_1[coldef->get_column_index()] = default_definitions_.at(i)->get_column_index();

                                    found_match = true;
                                    break;
                                }
                            }
                        }
                    }

                    if (!found_match)
                    {
                        //no matching column definition found
                        unmappable_columns[is_element_1] = coldef;
                    }
                }

                //TODO add default columns if not reserved
//                for (std::size_t i = 0; i < default_definitions_.size() ; i++)
//                {
//                    std::shared_ptr<column_definition> coldef = pair.second;
//
//                    if (mapped_columns.find(default_definitions_.at(i)->get_column_index()) == mapped_columns.end())
//                    {
//
//                    }
//                    else
//                    {
//                        //default definition only defined on one side
//                        unmappable_columns[is_element_1] = coldef;
//                    }
//                }


                //create vector for similarities
                std::vector<double> similarities (mapped_columns.size() + unmappable_columns.size());

                //punish unmappables
                for (std::size_t i = 0; i < unmappable_columns.size(); i++)
                {
                    similarities.push_back(0);
                }

                for (std::pair<int,int> pair : mapped_columns)
                {
                    int col1_id = pair.first;
                    int col2_id = pair.second;

                    std::vector<std::shared_ptr<i_movement> > movements1 = element1->get_column_movements(col1_id);
                    std::vector<std::shared_ptr<i_movement> > movements2 = element2->get_column_movements(col2_id);

                    //TODO quantize symbol
                    std::vector<std::shared_ptr<i_movement> > movements1_steps;
                    std::vector<std::shared_ptr<i_movement> > movements2_steps;

                    //get distance using distance measure
                    double distance = distance_measure_->distance(movements1_steps, movements2_steps);

                    //TODO distance = 0 if one sequence has no movements defined for the column (movement agnostic for that column)

                    //TODO distance to similarity

                }

                //TODO average similarities

                return 0;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
