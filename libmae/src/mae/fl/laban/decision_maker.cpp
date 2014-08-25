/*
 * decision_maker.cpp
 *
 *  Created on: 15.08.2014
 *      Author: keks
 */

#include "decision_maker.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			decision_maker::decision_maker(int beats_per_measure)
			{
				beats_per_measure_ = beats_per_measure;
			}

			decision_maker::~decision_maker()
			{
			}

			bool decision_maker::decide(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> a_predecessor, std::shared_ptr<i_movement> b, std::shared_ptr<i_movement> b_predecessor)
			{
				//TODO : define good values for deviation; currently 1/2 beat
				double pos_deviation_max = 0.5;
				double dur_deviation_max = 0.5;

				//don't check position of predecessors are unknown or one of the elements is a starting pose

				double pos_deviation = 0;
				if (a_predecessor != nullptr && b_predecessor != nullptr && a->get_measure() != 0 && b->get_measure() != 0)
				{
					//check position approx. equal if predecessors defined
					double pos_a = (a_predecessor->get_measure() - a->get_measure()) * beats_per_measure_ + (a_predecessor->get_beat() - a->get_beat());
					double pos_b = (b_predecessor->get_measure() - b->get_measure()) * beats_per_measure_ + (b_predecessor->get_beat() - b->get_beat());
					pos_deviation = std::abs(pos_a - pos_b);
				}

				//don't check duration if one of the elements is a starting pose
				double dur_deviation = 0;
				if (a->get_measure() != 0 && b->get_measure() != 0)
				{
					dur_deviation = std::abs(a->get_duration() - b->get_duration());
				}

				if (pos_deviation > pos_deviation_max || dur_deviation > dur_deviation_max)
				{
					return false;
				}

				//check type equal
				std::shared_ptr<movement> a_mov;
				std::shared_ptr<movement> b_mov;
				std::shared_ptr<room_direction> a_rd;
				std::shared_ptr<room_direction> b_rd;
				std::shared_ptr<path> a_p;
				std::shared_ptr<path> b_p;

				if ((a_mov = std::dynamic_pointer_cast<movement>(a))
						&& (b_mov = std::dynamic_pointer_cast<movement>(b)))
				{

					if (a_mov->get_symbol()->equals(b_mov->get_symbol()))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ((a_rd = std::dynamic_pointer_cast<room_direction>(a))
						&& (b_rd = std::dynamic_pointer_cast<room_direction>(b)))
				{
					if (a_rd->get_direction()->equals(b_rd->get_direction()))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ((a_p = std::dynamic_pointer_cast<path>(a)) && (b_p = std::dynamic_pointer_cast<path>(b)))
				{
					if (a_p->get_type() == b_p->get_type())
					{
						return true;
					}
					else
					{
						return false;
					}
				}

				//TODO relationship bow

				return false;
			}

			bool decision_maker::distance_okay(std::shared_ptr<i_movement> dist_from,
					std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check)
			{

				//distance between from and to
				//check whether position of check is less than distance -> true; false otherwise
				double beat_dist = (dist_from->get_measure() - dist_to->get_measure()) * beats_per_measure_
						+ (dist_from->get_beat() - dist_to->get_beat()) - dist_to->get_duration();

				double beat_pos = check->get_measure() * beats_per_measure_ + check->get_beat();

				if (beat_dist > beat_pos)
				{
					return true;
				}

				return false;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
