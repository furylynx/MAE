/*
 * i_decision_maker.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef I_DECISION_MAKER_HPP_
#define I_DECISION_MAKER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"

//global includes
#include <memory>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class i_decision_maker
			{
				public:
					virtual ~i_decision_maker(){}

					virtual bool decide(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DECISION_MAKER_HPP_
