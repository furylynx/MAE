/*
 * ini_reader.cpp
 *
 *  Created on: 27.06.2014
 *      Author: keks
 */

#include "ini_reader.hpp"

namespace mae
{

	ini_reader::ini_reader(std::string file)
	{
		read_file(file);
	}

	ini_reader::~ini_reader()
	{
	}

	std::string ini_reader::get_value(std::string domain, std::string key)
	{
		if (map_.find(domain) == map_.end())
		{
			throw std::invalid_argument("Domain not found!");
		}
		else
		{
			std::unordered_map<std::string, std::string> key_map = map_.at(domain);

			if (key_map.find(key) == key_map.end())
			{
				throw std::invalid_argument("Key not found!");
			}
			else
			{
				return key_map.at(key);
			}
		}
	}

	bool ini_reader::get_value_nex(std::string domain, std::string key, std::string* result)
	{
		std::string error_msg;

		return get_value_nex(domain, key, result, &error_msg);
	}

	bool ini_reader::get_value_nex(std::string domain, std::string key, std::string* result, std::string* out_error_msg)
	{
		std::string tmp = "";

		try
		{
			tmp = get_value(domain, key);
		} catch (std::exception& e)
		{
			(*out_error_msg) = e.what();
			return false;
		} catch (...)
		{
			(*out_error_msg) = "Unknown error.";
			return false;
		}

		*result = tmp;

		return true;
	}

	void ini_reader::read_file(std::string file)
	{
		try
		{
			std::ifstream in_file(file);
			std::stringstream sstr;

			std::string domain = "";

			if (in_file.is_open())
			{
				std::string line;
				while (std::getline(in_file, line))
				{
					sstr << line << std::endl;

					line = mstr::trim(line);

					if (line.size() > 0)
					{
						if (line.at(0) == '[')
						{
							std::string::size_type domain_endpos = line.find("]");
							domain = std::string(line, 1, domain_endpos - 1);
						}
						else
						{
							std::string::size_type sem_pos = line.find(";");
							std::string::size_type eq_pos = line.find("=");

							if (eq_pos < sem_pos && eq_pos != std::string::npos)
							{
								std::string key = std::string(line, 0, eq_pos);
								key = mstr::trim(key);

								std::string value;

								if (sem_pos == std::string::npos)
								{
									value = std::string(line, eq_pos + 1, line.size() - eq_pos - 1);
								}
								else
								{
									value = std::string(line, eq_pos + 1, sem_pos - eq_pos - 1);
								}

								mstr::trim_quotes(&value);

								std::unordered_map<std::string, std::string> domain_map;
								if (map_.find(domain) != map_.end())
								{
									domain_map = map_.at(domain);
								}

								if (domain_map.find(key) == domain_map.end())
								{
									domain_map.insert(std::make_pair(key, value));
								}
								else
								{
									std::cerr << "muliply defined key [" << domain << "]" << key << std::endl;
								}

								map_[domain] = domain_map;
							}
						}
					}
				}
				in_file.close();

			}
		} catch (std::exception& e)
		{
			std::cerr << "exception (" << e.what() << ") on reading the ini file." << std::endl;
		} catch (...)
		{
			std::cerr << "exception on reading the ini file." << std::endl;
		}
	}

} // namespace mae
