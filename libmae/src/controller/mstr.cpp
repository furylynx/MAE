/*
 * MStr.cpp
 *
 *  Created on: 13.06.2014
 *      Author: keks
 */

#include "mstr.hpp"

namespace mae
{

	std::string mstr::trim(std::string value)
	{
		std::stringstream trimmer;
		trimmer << value;
		value.clear();
		trimmer >> value;
		return value;
	}

	std::pair<int, int> mstr::find_line(std::string& haystack, std::string needle)
	{
		return mstr::find_line(haystack, needle, 0);
	}

	std::pair<int, int> mstr::find_line(std::string& haystack, std::string needle, unsigned int pos)
	{
		unsigned int pos_needle = haystack.find(needle, pos);
		unsigned int pos_endl = haystack.find("\n", (pos_needle + needle.size()));
		return std::pair<int, int>(pos_needle, pos_endl - pos_needle);
	}

	std::vector<std::string> mstr::split(std::string& value, unsigned int pos, unsigned int n)
	{
		return mstr::split(value, ' ', pos, n);
	}

	std::vector<std::string> mstr::split(std::string& value)
	{
		return mstr::split(value, ' ', 0, value.size());
	}

	std::vector<std::string> mstr::split(std::string& value, char delim, unsigned int pos, unsigned int n)
	{
		std::vector<std::string> result;

		std::string tmp(value, pos, n);

		std::stringstream ss(tmp);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			item = mstr::trim(item);
			if (item.compare("") != 0)
			{
				result.push_back(item);
			}
		}
		return result;
	}

	std::vector<std::string> mstr::split(std::string& value, char delim)
	{
		return mstr::split(value, delim, 0, value.size());
	}

	std::vector<double> mstr::double_list(std::string& value, unsigned int pos, unsigned int n)
	{
		std::vector<double> result;

		std::vector<std::string> split = mstr::split(value, pos, n);

		for (unsigned int i = 0; i < split.size(); i++)
		{
			result.push_back(std::stod(split.at(i)));
		}

		return result;
	}

	std::vector<double> mstr::double_list(std::string& value)
	{
		return mstr::double_list(value, 0, value.size());
	}

} // namespace mae
