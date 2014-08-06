/*
 * ini_reader.hpp
 *
 *  Created on: 27.06.2014
 *      Author: keks
 */

#ifndef INI_READER_HPP_
#define INI_READER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "mstr.hpp"

//global includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace mae
{

	class ini_reader
	{
		public:
			/**
			 * Creates a new ini reader. Reads the file and allows access via this class.
			 *
			 * @param file
			 */
			ini_reader(std::string file);

			virtual ~ini_reader();

			/**
			 * Returns the value assigned to the key in the given domain.
			 *
			 * @param domain The domain. "" if no domain
			 * @param key The key for the element.
			 * @return The value.
			 */
			virtual std::string get_value(std::string domain, std::string key);


		private:
			std::unordered_map<std::string, std::unordered_map<std::string, std::string> > map_;

			void read_file(std::string file);

	};

} // namespace mae

#endif // INI_READER_HPP_
