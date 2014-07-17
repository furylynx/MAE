/*
 * default_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DEFAULT_LIMB_HPP_
#define DEFAULT_LIMB_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_limb.hpp"
#include "e_limb.hpp"

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

				class default_limb: public i_limb
				{
					public:
						default_limb(e_limb limb);
						virtual ~default_limb();

						e_limb get_limb();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_limb limb_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DEFAULT_LIMB_HPP_
