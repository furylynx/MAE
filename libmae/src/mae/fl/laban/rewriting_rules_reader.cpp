/*
 * rewriting_rules_reader.cpp
 *
 *  Created on: 27.08.2014
 *      Author: keks
 */

#include "rewriting_rules_reader.hpp"

//internal includes
#include "internal_rewriting_rules_reader.hh"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			rewriting_rules_reader::rewriting_rules_reader()
			{
				// TODO Auto-generated constructor stub

			}

			rewriting_rules_reader::~rewriting_rules_reader()
			{
				// TODO Auto-generated destructor stub
			}

			std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > rewriting_rules_reader::read_rules_file(std::string file_name)
			{
				return internal_rewriting_rules_reader().read_rules_file(file_name);
			}

			std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > rewriting_rules_reader::read_rules_str(std::string xml_string)
			{
				return internal_rewriting_rules_reader().read_rules_str(xml_string);
			}



		} // namespace laban
	} // namespace fl
} // namespace mae
