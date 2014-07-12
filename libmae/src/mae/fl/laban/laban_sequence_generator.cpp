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

		laban_sequence_generator::laban_sequence_generator()
		{
		}

		laban_sequence_generator::~laban_sequence_generator()
		{
		}

		std::shared_ptr<laban_sequence> laban_sequence_generator::generate_sequence(
				std::list<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<bone> bodyParts)
		{

			//TODO set framerate to framerate used by the engine
			double framerate = 1.0/30.0;

			//number of beats per measure
			int beats = (int)(1/framerate);

			//one beat is one frame
			int beat_duration = 1000*framerate;

			//One measure is one second
			int measures = (int)(keyPoses.size()*framerate+1);



			std::shared_ptr<laban_sequence> sequence = std::shared_ptr<laban_sequence>(new laban_sequence("Streamed Sequence", "mae", measures, e_time_unit::MILLISECOND, beat_duration, beats));

			//todo set column definitions


			//fill movement data
			std::unordered_map<int, std::pair<int, std::shared_ptr<general_enriched_pose> > > tmp_kd;
			for (bone b : bodyParts)
			{
				tmp_kd.insert(std::make_pair(b.get_id(), std::make_pair(0, std::shared_ptr<general_enriched_pose>())));
			}

			int curr_frame = keyPoses.size();
			for (std::list<std::shared_ptr<general_enriched_pose> >::iterator it = keyPoses.begin(); it != keyPoses.end(); it++)
			{
				for (bone b : bodyParts)
				{
					if (tmp_kd.at(b.get_id()).second != nullptr && (*it)->is_in_motion(b.get_id()))
					{
						//get information for last pose (which is the last key pose)
						int prev_frame = tmp_kd.at(b.get_id()).first;
						std::shared_ptr<general_enriched_pose> prev_pose = tmp_kd.at(b.get_id()).second;

						int measure = (int)(curr_frame/beats);
						double beat = curr_frame-measure*beats;
						double duration = prev_frame-curr_frame;

						//find symbol from prev_pose!
						mv::e_level vertical = mv::e_level_c::lvl((e_fl_direction)prev_pose->get_direction(b.get_id()));
						mv::e_direction horizontal = mv::e_direction_c::dir((e_fl_direction)prev_pose->get_direction(b.get_id()));
						std::shared_ptr<mv::i_symbol> symbol = std::shared_ptr<mv::i_symbol>(new mv::direction_symbol(vertical, horizontal));

						//setup movement and add it to the sequence
						std::shared_ptr<i_movement> mv = std::shared_ptr<i_movement>(new movement(b.get_id(), measure, beat, duration, symbol));
						sequence->add_movement(mv);
					}

					if (tmp_kd.at(b.get_id()).second == nullptr && (*it)->is_key_pose(b.get_id()))
					{
						tmp_kd[b.get_id()] = std::make_pair(curr_frame, *it);
					}

				}

				curr_frame--;
			}

			return sequence;
		}

		} // namespace laban
	} // namespace fl
} // namespace mae
