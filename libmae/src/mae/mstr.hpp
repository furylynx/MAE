#ifndef MAE_MSTR_HPP_
#define MAE_MSTR_HPP_

//custom includes
//...

//global includes

#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <iostream>



namespace mae
{

	class mstr
	{
		public:

			/**
			 * Performs a left trim of the string.
			 *
			 * @param value The string.
			 * @return
			 */
			static std::string trim_left(const std::string& value);

			/**
			 * Performs a left trim of the string.
			 *
			 * @param value The string.
			 * @return
			 */
			static std::string trim_right(const std::string& value);

			/**
			 * Performs a trim of the string.
			 *
			 * @param value The string.
			 * @return
			 */
			static std::string trim(const std::string& value);

			/**
			 * Performs a trim and removes the leading and trailing quotation mark if present.
			 *
			 * @param value The pointer to the string.
			 */
			static void trim_quotes(std::string* value);

			/**
			 * Replaces all occurences in the haystack with the given replacement.
			 *
			 * @param haystack The haystack.
			 * @param needle The needle.
			 * @param replacement The replacement.
			 * @return The result.
			 */
			static std::string replace(const std::string& haystack, const std::string& needle, const std::string& replacement);

			/**
			 * Replaces all occurrences in the haystack with the given replacement. Escapes all occurrences of the replacement with '\'.
			 *
			 * @param haystack The haystack.
			 * @param needle The needle.
			 * @param replacement The replacement.
			 * @return The result.
			 * @return The result.
			 */
			static std::string replace_esc(const std::string& haystack, const std::string& needle, const std::string& replacement);

			/**
			 * Replaces all non-escaped occurrences in the haystack with the given replacement. Unscapes all occurrences of the replacement.
			 *
			 * @param haystack The haystack.
			 * @param needle The needle.
			 * @param replacement The replacement.
			 * @return The result.
			 * @return The result.
			 */
			static std::string replace_unesc(const std::string& haystack, const std::string& needle, const std::string& replacement);

			/**
			 * Transforms the string to lower case.
			 *
			 * @param value The string.
			 * @return The result.
			 */
			static std::string to_lower(const std::string& value);

			/**
			 * Transforms the string to upper case.
			 *
			 * @param value The string.
			 * @return The result.
			 */
			static std::string to_upper(const std::string& value);

			/**
			 * Find the first occurence of the needle in the line and returns the line break too.
			 *
			 * @param haystack The haystack.
			 * @param needle The needle.
			 * @return A pair of positions defining the occurence of the needle and the end of line.
			 */
			static std::pair<std::string::size_type, std::string::size_type> find_line(const std::string& haystack, const std::string& needle);
			/**
			 * Find the first occurence of the needle after the given position in the line and returns the line break too.
			 *
			 * @param haystack The haystack.
			 * @param needle The needle.
			 * @param pos The start position of the search.
			 * @return A pair of positions defining the occurence of the needle and the end of line.
			 */
			static std::pair<std::string::size_type, std::string::size_type> find_line(const std::string& haystack, const std::string& needle, std::string::size_type pos);

			/**
			 * Splits the string on white spaces.
			 *
			 * @param value The string.
			 * @return The result.
			 */
			static std::vector<std::string> split(const std::string&  value);

			/**
			 * Splits the string on white spaces beginning at the given position and regarding only n characters.
			 *
			 * @param value The string.
			 * @param pos The start position for the split.
			 * @param n The number of characters to be regarded.
			 * @return The result.
			 */
			static std::vector<std::string> split(const std::string&  value, std::string::size_type pos, std::string::size_type n);

			/**
			 * Splits the string on the given delimiter.
			 *
			 * @param value The string.
			 * @param delim The delimiter.
			 * @return The result.
			 */
			static std::vector<std::string> split(const std::string&  value, char delim);

			/**
			 * Splits the string on the given delimiter beginning at the given position and regarding only n characters.
			 *
			 * @param value The string.
			 * @param delim The delimiter.
			 * @param pos The start position for the split.
			 * @param n The number of characters to be regarded.
			 * @return The result.
			 */
			static std::vector<std::string> split(const std::string&  value, char delim, std::string::size_type pos, std::string::size_type n);

			/**
			 * Splits the string and parses the values to doubles.
			 *
			 * @param value The string.
			 * @return The result.
			 */
			static std::vector<double> double_list(const std::string&  value);

			/**
			 * Splits the string and parses the values to doubles beginning at the given position and regarding only n characters.
			 *
			 * @param value The string.
			 * @param pos The start position for the split.
			 * @param n The number of characters to be regarded.
			 * @return The result.
			 */
			static std::vector<double> double_list(const std::string&  value, std::string::size_type pos, std::string::size_type n);
	};

} // namespace mae

#endif // MAE_MSTR_HPP_
