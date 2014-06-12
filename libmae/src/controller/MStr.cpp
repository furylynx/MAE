/*
 * MStr.cpp
 *
 *  Created on: 13.06.2014
 *      Author: keks
 */

#include "MStr.hpp"

namespace mae
{

	std::string MStr::trim(std::string value)
	{
		std::stringstream trimmer;
		trimmer << value;
		value.clear();
		trimmer >> value;
		return value;
	}

	std::pair<int, int> MStr::find_line(std::string& haystack, std::string& needle)
	{
		return MStr::find_line(haystack, needle, 0);
	}

	std::pair<int, int> MStr::find_line(std::string& haystack, const char * needle)
	{
		std::string needle_str(needle);
		return MStr::find_line(haystack, needle_str);
	}

	std::pair<int, int> MStr::find_line(std::string& haystack, const char * needle, unsigned int pos)
	{
		std::string needle_str(needle);
		return MStr::find_line(haystack, needle_str, pos);
	}

	std::pair<int, int> MStr::find_line(std::string& haystack, std::string& needle, unsigned int pos)
	{
		std::string::size_type pos_needle = haystack.find(needle, pos);
		std::string::size_type pos_endl = haystack.find("\n", (std::string::size_type) (pos_needle + needle.size()));
		return std::pair<int, int>(pos_needle, pos_endl - pos_needle);
	}

	std::vector<std::string> MStr::split(std::string& value, unsigned int pos, unsigned int n)
	{
		return MStr::split(value, ' ', pos, n);
	}

	std::vector<std::string> MStr::split(std::string& value)
	{
		return MStr::split(value, ' ', 0, (unsigned int)value.size());
	}

	std::vector<std::string> MStr::split(std::string& value, char delim, unsigned int pos, unsigned int n)
	{
		std::vector<std::string> result;

		std::string tmp(value, pos, n);

		std::stringstream ss(tmp);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			item = MStr::trim(item);
			if (item.compare("") != 0)
			{
				result.push_back(item);
			}
		}
		return result;
	}

	std::vector<std::string> MStr::split(std::string& value, char delim)
	{
		return MStr::split(value, delim, 0, (unsigned int)value.size());
	}

	std::vector<double> MStr::double_list(std::string& value, unsigned int pos, unsigned int n)
	{
		std::vector<double> result;

		std::vector<std::string> split = MStr::split(value, pos, n);

		for (unsigned int i = 0; i < split.size(); i++)
		{
			result.push_back(std::stod((std::string) split[i]));
		}

		return result;
	}

	std::vector<double> MStr::double_list(std::string& value)
	{
		return MStr::double_list(value, 0, (unsigned int)value.size());
	}

} // namespace mae
