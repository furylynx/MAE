/*
 * body_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef BODY_PART_HPP_
#define BODY_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_pre_sign.hpp"
#include "e_side.hpp"
#include "i_part.hpp"

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

				class body_part: public i_pre_sign
				{
					public:
						body_part(e_side side, std::shared_ptr<i_part> part);
						virtual ~body_part();


						e_side get_side();
						std::shared_ptr<i_part> get_part();

						virtual std::string xml(unsigned int indent = 0);

					private:
						e_side side_;
						std::shared_ptr<i_part> part_;

				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // BODY_PART_HPP_
