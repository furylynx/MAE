#ifndef MAE_INI_READER_HPP_
#define MAE_INI_READER_HPP_

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

			/**
			 * Returns the value assigned to the key in the given domain. Suppresses the exception.
			 *
			 * @param domain The domain. "" if no domain
			 * @param key The key for the element.
			 * @return The value.
			 * @param result The pointer where to write the result.
			 * @return True if successful.
			 */
			virtual bool get_value_nex(std::string domain, std::string key, std::string* result);

			/**
			 * Returns the value assigned to the key in the given domain. Suppresses the exception.
			 *
			 * @param domain The domain. "" if no domain
			 * @param key The key for the element.
			 * @return The value.
			 * @param result The pointer where to write the result.
			 * @param out_error_msg The pointer where to write the error message.
			 * @return True if successful.
			 */
			virtual bool get_value_nex(std::string domain, std::string key, std::string* result, std::string* out_error_msg);

		private:
			std::unordered_map<std::string, std::unordered_map<std::string, std::string> > map_;

			/**
			 * Parses the file in order to get the [domain]key-value pairs.
			 *
			 * @param file The file.
			 */
			void read_file(std::string file);

	};

} // namespace mae

#endif // MAE_INI_READER_HPP_
