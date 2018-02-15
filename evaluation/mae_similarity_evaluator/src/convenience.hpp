//
// Created on 2017-12-01
//

#ifndef MAE_SIMILARITY_EVALUATOR_CONVENIENCE_HPP
#define MAE_SIMILARITY_EVALUATOR_CONVENIENCE_HPP

//custom includes
//...

//global includes
#include <mae/mae.hpp>


struct laban_sequence_info { int id; std::string path; std::string filename; std::string directory; std::shared_ptr<mae::fl::laban::laban_sequence> laban_sequence; };

laban_sequence_info initialize_laban_sequence_info(int id, std::string path, std::string filename, std::string directory, std::shared_ptr<mae::fl::laban::laban_sequence> laban_sequence)
{
    laban_sequence_info result;
    result.id=id;
    result.path = path;
    result.filename = filename;
    result.directory = directory;
    result.laban_sequence = laban_sequence;

    return result;
}

struct comparator_info { int id; std::string name; std::string description; std::shared_ptr<mae::math::i_similarity_measure<std::shared_ptr<mae::fl::laban::laban_sequence> > > comparator; };

comparator_info initialize_comparator_info(int id, std::string name, std::string description, std::shared_ptr<mae::math::i_similarity_measure<std::shared_ptr<mae::fl::laban::laban_sequence> > > comparator)
{
    comparator_info result;
    result.id=id;
    result.name = name;
    result.description = description;
    result.comparator = comparator;

    return result;
}



#endif //MAE_SIMILARITY_EVALUATOR_CONVENIENCE_HPP
