/*
 * labanmovement.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef LABANMOVEMENT_HPP_
#define LABANMOVEMENT_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>
#include <string>

namespace mae
{
	namespace fl
	{

		enum class direction {PLACE, FORWARD, BACKWARD, LEFT, RIGHT, LEFT_FORWARD, LEFT_BACKWARD, RIGHT_FORWARD, RIGHT_BACKWARD};
		enum class level {HIGH, MIDDLE, LOW};

		enum class contact_hook {NONE, NAIL, TIP, PAD, BALL, HALF_BALL, QUARTER_BALL, FOOT, HALF_HEEL, QUARTER_HEEL, FULL_HEEL, FULL_BALL};

		class laban_movement
		{
			public:
				laban_movement();
				laban_movement(int column, unsigned int measure, double beat, double duration, bool hold, direction dir, level lvl, contact_hook c_hook = contact_hook::NONE);
				virtual ~laban_movement();

				virtual std::string xml();

				int get_column();
				unsigned int get_measure();
				double get_beat();
				double get_duration();
				bool get_hold();
				direction get_direction();
				level get_level();

			private:
				int column_;
				unsigned int measure_;
				double beat_;
				double duration_;
				bool hold_;

				direction direction_;
				level level_;

				//TODO modification pin

				//TODO relationship pin

				//TODO space measurement

				//TODO dynamics

				contact_hook contact_hook_;

		};

	} // namespace fl
} // namespace mae

#endif // LABANMOVEMENT_HPP_
