#include "mstr.hpp"

namespace mae
{

	std::string mstr::trim_left(const std::string& value)
	{
		std::string result = value;

		std::size_t startpos = result.find_first_not_of(" \t\n");
		if( std::string::npos != startpos )
		{
			result = result.substr(startpos);
		}

		return result;
	}

	std::string mstr::trim_right(const std::string& value)
	{
		std::string result = value;
		//result.erase(std::find_if(result.rbegin(), result.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), result.end());

		std::size_t endpos = result.find_last_not_of(" \t\n");
		if( std::string::npos != endpos )
		{
			result = result.substr(0, endpos + 1);
		}

		return result;
	}

	std::string mstr::trim(const std::string& value)
	{
		return mstr::trim_left(mstr::trim_right(value));
	}

	void mstr::trim_quotes(std::string* value)
	{
		*value = mstr::trim(*value);

		if (value->at(0) == '"')
		{
			value->erase(value->begin());
		}

		if (value->at(value->size()-1) == '"')
		{
			value->erase(value->begin()+(value->size()-1));
		}
	}

	std::string mstr::replace(const std::string& haystack, const std::string& needle, const std::string& replacement)
	{
		std::string result = std::string(haystack);

		//the needle is empty therefore the string will be returned unmodified
		if (needle.empty())
		{
			return result;
		}

		std::string::size_type start_pos = result.find(needle);

		//iterate through the string
		while (start_pos != std::string::npos)
		{
			//replace the occurrence
			result.replace(start_pos, needle.length(), replacement);

			//move to the end of the replacement
			start_pos += replacement.length();

			start_pos = result.find(needle, start_pos);
		}

		return result;
	}

	std::string mstr::replace_esc(const std::string& haystack, const std::string& needle, const std::string& replacement)
	{
		std::stringstream sstr_rep;
		sstr_rep << "\\" << replacement;

		std::string result = replace(haystack, replacement, sstr_rep.str());
		result = replace(result, needle, replacement);

		return result;
	}

	std::string mstr::replace_unesc(const std::string& haystack, const std::string& needle, const std::string& replacement)
	{
		std::string result = std::string(haystack);

		//the needle is empty therefore the string will be returned unmodified
		if (needle.empty())
		{
			return result;
		}

		std::string::size_type start_pos = result.find(needle);

		//iterate through the string
		while (start_pos != std::string::npos)
		{
			if (start_pos == 0 || result.at(start_pos-1) != '\\')
			{
				//replace the occurrence
				result.replace(start_pos, needle.length(), replacement);

				//move to the end of the replacement
				start_pos += replacement.length();
			}
			else
			{
				//unescape the occurrence
				result.erase(result.begin()+(start_pos - 1));
				start_pos += needle.length() - 1;
			}

			start_pos = result.find(needle, start_pos);
		}

		return result;
	}

	std::string mstr::to_lower(const std::string& value)
	{
		std::locale loc;
		std::string result = value;

		for (unsigned int k = 0; k < result.length(); k++)
		{
			result[k] = std::tolower((char) result[k], loc);
		}

		return result;
	}

	std::string mstr::to_upper(const std::string& value)
	{
		std::locale loc;
		std::string result(value);

		for (unsigned int k = 0; k < result.length(); k++)
		{
			result[k] = std::toupper((char) result[k], loc);
		}

		return result;
	}

	std::pair<std::string::size_type, std::string::size_type> mstr::find_line(const std::string& haystack, const std::string& needle)
	{
		return mstr::find_line(haystack, needle, 0);
	}

	std::pair<std::string::size_type, std::string::size_type> mstr::find_line(const std::string& haystack, const std::string& needle, std::string::size_type pos)
	{
		std::string::size_type pos_needle = haystack.find(needle, pos);
		std::string::size_type pos_endl = haystack.find('\n', (pos_needle + needle.size()));

		return std::pair<std::string::size_type, std::string::size_type>(pos_needle, pos_endl - pos_needle);
	}

	std::vector<std::string> mstr::split(const std::string& value, std::string::size_type pos, std::string::size_type n)
	{
		return mstr::split(value, ' ', pos, n);
	}

	std::vector<std::string> mstr::split(const std::string& value)
	{
		return mstr::split(value, ' ', 0, value.size());
	}

	std::vector<std::string> mstr::split(const std::string& value, char delim, std::string::size_type pos, std::string::size_type n)
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

	std::vector<std::string> mstr::split(const std::string& value, char delim)
	{
		return mstr::split(value, delim, 0, value.size());
	}

	std::vector<double> mstr::double_list(const std::string& value, std::string::size_type pos, std::string::size_type n)
	{
		std::vector<double> result;

		std::vector<std::string> split = mstr::split(value, pos, n);

		for (unsigned int i = 0; i < split.size(); i++)
		{
			result.push_back(std::stod(split.at(i)));
		}

		return result;
	}

	std::vector<double> mstr::double_list(const std::string& value)
	{
		return mstr::double_list(value, 0, value.size());
	}

} // namespace mae
