//
// Created on 2017-11-03
//

#ifndef MAE_FL_LABAN_SUBSEQUENCE_MAPPER_HPP
#define MAE_FL_LABAN_SUBSEQUENCE_MAPPER_HPP

//custom includes
#include "laban_sequence.hpp"

//global includes
#include <memory>
#include <unordered_map>
#include <vector>


namespace mae {
    namespace fl {
        namespace laban {

            class laban_subsequence_mapper {
                public:
                    laban_subsequence_mapper(std::shared_ptr<laban_sequence> sequence1, std::shared_ptr<laban_sequence> sequence2);
                    virtual ~laban_subsequence_mapper();

                    std::unordered_map<int,int> get_mapped_columns() const;
                    std::unordered_map<bool,std::shared_ptr<column_definition> > get_unmappable_columns() const;

                private:
                    std::vector<std::shared_ptr<column_definition> > default_definitions_;
                    std::unordered_map<int,int> mapped_columns_;
                    std::unordered_map<bool,std::shared_ptr<column_definition> > unmappable_columns_;

                    void map_columns(std::shared_ptr<laban_sequence> sequence1, std::shared_ptr<laban_sequence> sequence2);

            };


        } // namespace laban
    } // namespace fl
} // namespace mae


#endif //MAE_FL_LABAN_SUBSEQUENCE_MAPPER_HPP
