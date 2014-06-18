/*
 * MStr.hpp
 *
 *  Created on: 13.06.2014
 *      Author: keks
 */

#ifndef MSTR_HPP_
#define MSTR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes

#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>


namespace mae
{

	class mstr
	{
		public:

			static std::string trim(const std::string& value);

			static std::string replace(const std::string& haystack, const std::string& needle, const std::string& replacement);

			static std::string to_lower(const std::string& value);
			static std::string to_upper(const std::string& value);

			static std::pair<std::string::size_type, std::string::size_type> find_line(const std::string& haystack, const std::string& needle);
			static std::pair<std::string::size_type, std::string::size_type> find_line(const std::string& haystack, const std::string& needle, unsigned int pos);

			static std::vector<std::string> split(const std::string& value);
			static std::vector<std::string> split(const std::string& value, std::string::size_type pos, std::string::size_type n);
			static std::vector<std::string> split(const std::string& value, char delim);
			static std::vector<std::string> split(const std::string& value, char delim, std::string::size_type pos, std::string::size_type n);

			static std::vector<double> double_list(const std::string& value);
			static std::vector<double> double_list(const std::string& value, std::string::size_type pos, std::string::size_type n);
	};

} // namespace mae

#endif // MSTR_HPP_
