/*
 * FLLabanSequenceGenerator.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

//custom includes
#include "laban_sequence_generator.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			laban_sequence_generator::laban_sequence_generator(bool debug)
			{
				debug_ = debug;
				beats_per_measure_ = laban_sequence::default_beats_per_measure();
				beat_duration_ = laban_sequence::default_beat_duration();
				time_unit_ = laban_sequence::default_time_unit();
			}

			laban_sequence_generator::laban_sequence_generator(std::vector<std::shared_ptr<column_definition> > column_definitions, unsigned int beats_per_measure, unsigned int beat_duration, e_time_unit time_unit, bool debug)
			{
				column_definitions_ = column_definitions;
				debug_ = debug;
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;
			}

			laban_sequence_generator::~laban_sequence_generator()
			{
			}

			std::shared_ptr<laban_sequence> laban_sequence_generator::generate_sequence(double framerate,
					std::list<std::shared_ptr<general_enriched_pose> > key_poses, std::vector<bone> body_parts)
			{
				if (debug_)
				{
					std::cout << "laban_sequence_generator: generate sequence" << std::endl;
				}

				//TODO handle glitches?!

				//number of measures in the staff
				int measures = (int) (key_poses.size() * framerate + 1);

				//remove those body parts from the vector that have no column defined
				std::vector<bone> used_body_parts;
				for (unsigned int i = 0; i < body_parts.size(); i++)
				{
					bool defined = std::abs(body_parts.at(i).get_id()) == 4 || std::abs(body_parts.at(i).get_id()) == 2
							|| std::abs(body_parts.at(i).get_id()) == 1;

					if (!defined)
					{
						for (unsigned int j = 0; j < column_definitions_.size(); j++)
						{
							if (column_definitions_.at(j)->get_column_index() == body_parts.at(i).get_id())
							{
								defined = true;
								break;
							}
						}
					}

					if (defined)
					{
						used_body_parts.push_back(body_parts.at(i));
					}
				}

				std::shared_ptr<laban_sequence> sequence = std::shared_ptr<laban_sequence>(
						new laban_sequence("Streamed Sequence", "mae", measures, time_unit_,
								beat_duration_, beats_per_measure_));

				//set column definitions
				sequence->set_column_definitions(column_definitions_);

				//fill movement data
				for (bone b : used_body_parts)
				{
					std::shared_ptr<general_enriched_pose> prev_kp = nullptr;
					int prev_kp_frame = 0;

					int curr_frame = key_poses.size();

					for (std::list<std::shared_ptr<general_enriched_pose> >::iterator it = key_poses.begin();
							it != key_poses.end(); it++)
					{

						if (prev_kp != nullptr && (*it)->is_in_motion(b.get_id()))
						{
							//get information for last pose (which is the last key pose)
							int measure = (int) (curr_frame * framerate * 1000.0 / (beats_per_measure_ * beat_duration_));
							double beat = (((curr_frame * framerate * 1000.0) - (measure * beats_per_measure_ * beat_duration_))
									/ beat_duration_);
							double duration = (prev_kp_frame - curr_frame) * framerate * 1000.0 / beat_duration_;

							//find symbol from prev_pose!
							mv::e_level vertical = mv::e_level_c::lvl(
									(e_fl_direction) prev_kp->get_direction(b.get_id()));
							mv::e_direction horizontal = mv::e_direction_c::dir(
									(e_fl_direction) prev_kp->get_direction(b.get_id()));
							std::shared_ptr<mv::i_symbol> symbol = std::shared_ptr<mv::i_symbol>(
									new mv::direction_symbol(vertical, horizontal));

							//setup movement and add it to the sequence
							std::shared_ptr<i_movement> mv = std::shared_ptr<i_movement>(
									new movement(b.get_id(), measure + 1, beat, duration, symbol));

							sequence->add_movement(mv);

							//reset tmp
							prev_kp_frame = 0;
							prev_kp = nullptr;
						}

						if (prev_kp == nullptr && (*it)->is_key_pose(b.get_id()))
						{
							prev_kp = *it;
							prev_kp_frame = curr_frame;
						}

						curr_frame--;
					}
				}

				return sequence;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
