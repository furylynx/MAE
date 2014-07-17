/*
 * surface_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef SURFACE_PART_HPP_
#define SURFACE_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_part.hpp"
#include "e_limb_side.hpp"
#include "i_limb.hpp"

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

				class surface_part : public i_part
				{
					public:
						surface_part(e_limb_side lside, std::shared_ptr<i_limb> limb);
						virtual ~surface_part();


						e_limb_side get_limb_side();
						std::shared_ptr<i_limb> get_limb();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_limb_side lside_;
						std::shared_ptr<i_limb> limb_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // SURFACE_PART_HPP_
