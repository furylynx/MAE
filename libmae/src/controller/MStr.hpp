/*
 * MStr.hpp
 *
 *  Created on: 13.06.2014
 *      Author: keks
 */

#ifndef MSTR_HPP_
#define MSTR_HPP_

//custom includes
//...

//global includes

#include <string>
#include <sstream>
#include <memory>
#include <vector>

namespace mae
{

	class MStr
	{
		public:

			static std::string trim(std::string value);

			static std::pair<int, int> find_line(std::string& haystack, std::string& needle);
			static std::pair<int, int> find_line(std::string& haystack, const char * needle);
			static std::pair<int, int> find_line(std::string& haystack, std::string& needle, unsigned int pos);
			static std::pair<int, int> find_line(std::string& haystack, const char * needle, unsigned int pos);

			static std::vector<std::string> split(std::string& value);
			static std::vector<std::string> split(std::string& value, unsigned int pos, unsigned int n);
			static std::vector<std::string> split(std::string& value, char delim);
			static std::vector<std::string> split(std::string& value, char delim, unsigned int pos, unsigned int n);

			static std::vector<double> double_list(std::string& value);
			static std::vector<double> double_list(std::string& value, unsigned int pos, unsigned int n);
	};

} // namespace mae

#endif // MSTR_HPP_
