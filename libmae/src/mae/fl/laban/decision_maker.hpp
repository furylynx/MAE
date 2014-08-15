/*
 * decision_maker.hpp
 *
 *  Created on: 15.08.2014
 *      Author: keks
 */

#ifndef DECISION_MAKER_HPP_
#define DECISION_MAKER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_decision_maker.hpp"
#include "i_movement.hpp"
#include "movement.hpp"
#include "path.hpp"
#include "room_direction.hpp"

//global includes



namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_maker: public i_decision_maker<i_movement>
			{
				public:
					decision_maker(int beats_per_measure);
					virtual ~decision_maker();

					virtual bool decide(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b);

					virtual bool distance_okay(std::shared_ptr<i_movement> dist_from, std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check);

				private:
					int beats_per_measure_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_MAKER_HPP_
