/*
 * prop.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef PROP_HPP_
#define PROP_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_pre_sign.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class prop : public i_pre_sign
				{
					public:
						prop(std::string name, std::string description);
						virtual ~prop();


						std::string get_name();
						std::string get_description();

						virtual std::string xml(unsigned int indent = 0);

					private:
						std::string name_;
						std::string description_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // PROP_HPP_
