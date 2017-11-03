//
// Created on 2017-11-03
//

#include "laban_subsequence_mapper.hpp"


namespace mae {
    namespace fl {
        namespace laban {

            laban_subsequence_mapper::laban_subsequence_mapper(std::shared_ptr<laban_sequence> sequence1, std::shared_ptr<laban_sequence> sequence2)
            {
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::RIGHT_WHOLE_ARM));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_LEG));
                default_definitions_.push_back(std::make_shared<mae::fl::laban::column_definition>(e_bone::LEFT_WHOLE_ARM));

                map_columns(sequence1,sequence2);
            }

            laban_subsequence_mapper::~laban_subsequence_mapper()
            {
            }


            std::unordered_map<int,int> laban_subsequence_mapper::get_mapped_columns() const
            {
                return mapped_columns_;
            }

            std::unordered_map<bool,std::shared_ptr<column_definition> > laban_subsequence_mapper::get_unmappable_columns() const
            {
                return unmappable_columns_;
            }

            void laban_subsequence_mapper::map_columns(std::shared_ptr<laban_sequence> sequence1, std::shared_ptr<laban_sequence> sequence2)
            {
                //map columns to each other and find unmappable columns
                std::vector<std::shared_ptr<column_definition> > el1_coldefs = sequence1->get_column_definitions();
                std::vector<std::shared_ptr<column_definition> > el2_coldefs = sequence2->get_column_definitions();


                std::unordered_map<int,int> mapped_columns_2_to_1;
                std::unordered_map<bool,std::shared_ptr<column_definition> > prel_unmappable_columns;

                for (std::shared_ptr<column_definition> coldef : el1_coldefs)
                {
                    int col_id = coldef->get_column_index();

                    if (coldef->equals(sequence2->get_column_definition(col_id)))
                    {
                        //column is defined at the same id on both sequences
                        mapped_columns_[col_id] = col_id;
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
                                mapped_columns_[col_id] = coldef2->get_column_index();
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
                                    mapped_columns_[coldef->get_column_index()] = default_def->get_column_index();
                                    mapped_columns_2_to_1[default_def->get_column_index()] = coldef->get_column_index();

                                    found_match = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (mapped_columns_.find(default_def->get_column_index()) == mapped_columns_.end())
                                {
                                    //matching column definition found in default definition
                                    mapped_columns_[default_def->get_column_index()] = coldef->get_column_index();
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
                        unmappable_columns_[is_element_1] = coldef;
                    }
                }

                //add default columns if not reserved
                for (std::shared_ptr<column_definition> default_def : default_definitions_)
                {
                    int col_id = default_def->get_column_index();

                    if (mapped_columns_.find(col_id) == mapped_columns_.end() && mapped_columns_2_to_1.find(col_id) == mapped_columns_2_to_1.end())
                    {
                        //default definition not overwritten on any of the sequences
                        mapped_columns_[col_id] = col_id;
                        mapped_columns_2_to_1[col_id] = col_id;
                    }
                    else
                    {
                        if (mapped_columns_.find(col_id) != mapped_columns_.end() && mapped_columns_2_to_1.find(col_id) == mapped_columns_2_to_1.end())
                        {
                            //default definition only defined on one side and since a definition elsewhere is already checked the default column has no matching partner
                            unmappable_columns_[false] = default_def;
                        }
                        else if (mapped_columns_.find(col_id) == mapped_columns_.end() && mapped_columns_2_to_1.find(col_id) != mapped_columns_2_to_1.end())
                        {
                            //default definition only defined on one side and since a definition elsewhere is already checked the default column has no matching partner
                            unmappable_columns_[true] = default_def;
                        }
                    }
                }
            }

        } // namespace laban
    } // namespace fl
} // namespace mae