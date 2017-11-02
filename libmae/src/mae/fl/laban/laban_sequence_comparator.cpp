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

            laban_sequence_comparator::laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<i_movement> > > > distance_measure,  bool ignore_empty_columns, unsigned int frames_per_beat)
            {
                distance_measure_ = distance_measure;
                ignore_empty_columns_ = ignore_empty_columns;
                frames_per_beat_ = frames_per_beat;

                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_ARM));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_ARM));
            }

            laban_sequence_comparator::~laban_sequence_comparator()
            {

            }

            double laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                //map columns to each other and find unmappable columns
                std::vector<std::shared_ptr<column_definition> > el1_coldefs = element1->get_column_definitions();
                std::vector<std::shared_ptr<column_definition> > el2_coldefs = element2->get_column_definitions();


                std::unordered_map<int,int> mapped_columns;
                std::unordered_map<int,int> mapped_columns_2_to_1;
                std::unordered_map<bool,std::shared_ptr<column_definition> > prel_unmappable_columns;
                std::unordered_map<bool,std::shared_ptr<column_definition> > unmappable_columns;

                for (std::shared_ptr<column_definition> coldef : el1_coldefs)
                {
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
                        for (std::shared_ptr<column_definition> coldef2 : el2_coldefs)
                        {
                            if (coldef->equals(coldef2))
                            {
                                //matching column definition found
                                mapped_columns[col_id] = coldef2->get_column_index();
                                mapped_columns_2_to_1[coldef2->get_column_index()] = col_id;

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
                    for (std::shared_ptr<column_definition> coldef2 : el2_coldefs)
                    {
                        int col2_id = coldef2->get_column_index();

                        if (mapped_columns_2_to_1.find(col2_id) == mapped_columns_2_to_1.end())
                        {
                            prel_unmappable_columns[false] = coldef2;
                        }
                    }
                }

                //check mapping for unmappable within default columns
                for (std::pair<bool,std::shared_ptr<column_definition> > pair : prel_unmappable_columns)
                {
                    bool is_element_1 = pair.first;
                    std::shared_ptr<column_definition> coldef = pair.second;

                    bool found_match = false;

                    for (std::shared_ptr<column_definition> default_def : default_definitions_)
                    {
                        if (coldef->equals(default_def))
                        {
                            if (is_element_1)
                            {
                                if (mapped_columns_2_to_1.find(default_def->get_column_index()) == mapped_columns_2_to_1.end())
                                {
                                    //matching column definition found in default definition
                                    mapped_columns[coldef->get_column_index()] = default_def->get_column_index();
                                    mapped_columns_2_to_1[default_def->get_column_index()] = coldef->get_column_index();

                                    found_match = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (mapped_columns.find(default_def->get_column_index()) == mapped_columns.end())
                                {
                                    //matching column definition found in default definition
                                    mapped_columns[default_def->get_column_index()] = coldef->get_column_index();
                                    mapped_columns_2_to_1[coldef->get_column_index()] = default_def->get_column_index();

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

                //add default columns if not reserved
                for (std::shared_ptr<column_definition> default_def : default_definitions_)
                {
                    int col_id = default_def->get_column_index();

                    if (mapped_columns.find(col_id) == mapped_columns.end() && mapped_columns_2_to_1.find(col_id) == mapped_columns_2_to_1.end())
                    {
                        //default definition not overwritten on any of the sequences
                        mapped_columns[col_id] = col_id;
                        mapped_columns_2_to_1[col_id] = col_id;
                    }
                    else
                    {
                        if (mapped_columns.find(col_id) != mapped_columns.end() && mapped_columns_2_to_1.find(col_id) == mapped_columns_2_to_1.end())
                        {
                            //default definition only defined on one side and since a definition elsewhere is already checked the default column has no matching partner
                            unmappable_columns[false] = default_def;
                        }
                        else if (mapped_columns.find(col_id) == mapped_columns.end() && mapped_columns_2_to_1.find(col_id) != mapped_columns_2_to_1.end())
                        {
                            //default definition only defined on one side and since a definition elsewhere is already checked the default column has no matching partner
                            unmappable_columns[true] = default_def;
                        }
                    }
                }

                //similarities
                double similarities_sum = 0;
                std::size_t similarities_size = 0;;

                //punish unmappables
                similarities_size += mapped_columns.size() + unmappable_columns.size();

                for (std::pair<int,int> pair : mapped_columns)
                {
                    int col1_id = pair.first;
                    int col2_id = pair.second;

                    //quantize symbol
                    std::vector<std::shared_ptr<i_movement> > movements1_steps = create_stretched(element1->get_column_movements(col1_id));
                    std::vector<std::shared_ptr<i_movement> > movements2_steps = create_stretched(element2->get_column_movements(col2_id));

                    //get distance using distance measure, distance = 0 if one sequence has no movements defined for the column and ignore flag is set (movement agnostic for that column)
                    double distance = 0;

                    if ((!movements1_steps.empty() && !movements2_steps.empty()) || !ignore_empty_columns_)
                    {
                        distance = distance_measure_->distance(movements1_steps, movements2_steps);
                    }

                    //TODO max distance
                    double max_distance = 100000;

                    //distance to similarity
                    double similarity = 0;

                    if (distance != std::numeric_limits<double>::infinity())
                    {
                        similarity = 1 / (1 + distance);
                    }

                    //TODO remove
                    std::cout << "similarity [" << col1_id << "," << col2_id << "] " << similarity << " for dist " << distance << std::endl;

                    similarities_size++;
                    similarities_sum += similarity;

                }

                //average similarities
                return similarities_sum / (double) similarities_size;
            }


            std::vector<std::shared_ptr<i_movement> > laban_sequence_comparator::create_stretched(std::vector<std::shared_ptr<i_movement> > non_streched) const
            {
                if (0 == frames_per_beat_)
                {
                    return non_streched;
                }

                std::vector<std::shared_ptr<i_movement> > result;

                for (std::shared_ptr<i_movement> symbol : non_streched)
                {
                    int times = (int) (frames_per_beat_ * symbol->get_duration());

                    if (times < 1)
                    {
                        times = 1;
                    }

                    for (int i = 0; i < times; i++)
                    {
                        result.push_back(symbol);
                    }
                }

                return result;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
