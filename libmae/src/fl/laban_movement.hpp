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
#include <sstream>
#include <ios>


namespace mae
{
	namespace fl
	{

		enum class laban_direction {NONE, PLACE, FORWARD, BACKWARD, LEFT, RIGHT, LEFT_FORWARD, LEFT_BACKWARD, RIGHT_FORWARD, RIGHT_BACKWARD, SIZE};
		static const char* laban_direction_str[(int) laban_direction::SIZE] = {"none", "place", "forward", "backward", "left", "right", "left-forward", "left-backward", "right-forward", "right-backward"};

		enum class laban_level {NONE, HIGH, MIDDLE, LOW, SIZE};
		static const char* laban_level_str[(int) laban_level::SIZE] = {"none", "high", "middle", "low"};

		enum class contact_hook {NONE, NAIL, TIP, PAD, BALL, HALF_BALL, QUARTER_BALL, FOOT, HALF_HEEL, QUARTER_HEEL, FULL_HEEL, FULL_BALL, SIZE};
		static const char* contact_hook_str[(int) contact_hook::SIZE] = {"none", "nail", "tip", "pad", "ball", "halfBall", "quarterBall", "foot", "halfHeel", "quarterHeel", "fullHeel", "fullBall"};

		class laban_movement
		{
			public:
				laban_movement(int column, unsigned int measure, double beat, double duration, bool hold, laban_direction dir, laban_level lvl, contact_hook c_hook = contact_hook::NONE);
				virtual ~laban_movement();

				virtual std::string xml(unsigned int indent = 3);

				int get_column();
				unsigned int get_measure();
				double get_beat();
				double get_duration();
				bool get_hold();
				laban_direction get_direction();
				laban_level get_level();

			private:
				int column_;
				unsigned int measure_;
				double beat_;
				double duration_;
				bool hold_;

				laban_direction direction_;
				laban_level level_;

				//TODO pre-sign

				//TODO modification pin

				//TODO relationship pin

				//TODO space measurement

				//TODO dynamics

				contact_hook contact_hook_;

				//TODO other movements apart from directions... (turn, vibration, cancellation)


		};

	} // namespace fl
} // namespace mae

#endif // LABANMOVEMENT_HPP_
