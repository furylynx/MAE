/*
 * rewriting_rules.hpp
 *
 *  Created on: 13.08.2014
 *      Author: keks
 */

#ifndef REWRITING_RULES_HPP_
#define REWRITING_RULES_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_rules
			{
				public:
					rewriting_rules();
					virtual ~rewriting_rules();

					virtual void add_rule();

					virtual void find_rule();

					virtual void read_rules_str(std::string xml);
					virtual void read_rules_file(std::string file);

				private:

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // REWRITING_RULES_HPP_
