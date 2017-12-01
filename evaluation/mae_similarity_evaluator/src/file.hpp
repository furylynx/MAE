//
// Created on 2017-12-01
//

#ifndef MAE_SIMILARITY_EVALUATOR_FILE_HPP
#define MAE_SIMILARITY_EVALUATOR_FILE_HPP

//custom includes
//...

//global includes
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

std::string read_file(std::string file_name)
{
    //open the input file
    std::ifstream in_file;
    in_file.open(file_name);

    if (in_file.is_open())
    {
        //read the file
        std::stringstream sstr;
        sstr << in_file.rdbuf();

        return sstr.str();
    }
    else
    {
        std::stringstream sstr;
        sstr << "Cannot open the file " << file_name;
        throw std::runtime_error (sstr.str());
    }
}

#endif //MAE_SIMILARITY_EVALUATOR_FILE_HPP
