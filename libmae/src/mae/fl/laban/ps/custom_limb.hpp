/*
 * custom_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef CUSTOM_LIMB_HPP_
#define CUSTOM_LIMB_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_limb.hpp"
#include "i_endpoint.hpp"

//global includes
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class custom_limb: public i_limb
				{
					public:
						custom_limb(std::shared_ptr<i_endpoint> fixed_end, std::shared_ptr<i_endpoint> extremity);
						virtual ~custom_limb();

						std::shared_ptr<i_endpoint> get_fixed_end();
						std::shared_ptr<i_endpoint> get_extremity();

						virtual std::string xml(unsigned int indent = 0);

					private:
						std::shared_ptr<i_endpoint> fixed_end_;
						std::shared_ptr<i_endpoint> extremity_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // CUSTOM_LIMB_HPP_
