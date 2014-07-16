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
			}

			laban_sequence_generator::laban_sequence_generator(
					std::vector<std::shared_ptr<column_definition> > column_definitions, bool debug)
			{
				column_definitions_ = column_definitions;
				debug_ = debug;
			}

			laban_sequence_generator::~laban_sequence_generator()
			{
			}

			std::shared_ptr<laban_sequence> laban_sequence_generator::generate_sequence(
					std::list<std::shared_ptr<general_enriched_pose> > key_poses, std::vector<bone> body_parts)
			{
				if (debug_)
				{
					std::cout << "laban_sequence_generator: generate sequence" << std::endl;
				}

				//TODO set framerate to framerate used by the engine
				double framerate = 1.0 / 30.0;

				//number of beats per measure
				int beats = (int) (1 / framerate);

				//one beat is one frame
				int beat_duration = 1000 * framerate;

				//One measure is one second
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
						new laban_sequence("Streamed Sequence", "mae", measures, e_time_unit::MILLISECOND,
								beat_duration, beats));

				//set column definitions
				sequence->set_column_definitions(column_definitions_);

				//fill movement data
				std::unordered_map<int, std::pair<int, std::shared_ptr<general_enriched_pose> > > tmp_kd;
				for (bone b : used_body_parts)
				{
					tmp_kd.insert(std::make_pair(b.get_id(), std::make_pair(0, nullptr)));
				}

				int curr_frame = key_poses.size();
				for (std::list<std::shared_ptr<general_enriched_pose> >::iterator it = key_poses.begin();
						it != key_poses.end(); it++)
				{
					for (bone b : used_body_parts)
					{
						//TODO remove
						//std::cout << "bone id " << b.get_id() << std::endl;

						if (tmp_kd.at(b.get_id()).second != nullptr && (*it)->is_in_motion(b.get_id()))
						{
							//get information for last pose (which is the last key pose)
							int prev_frame = tmp_kd.at(b.get_id()).first;
							std::shared_ptr<general_enriched_pose> prev_pose = tmp_kd.at(b.get_id()).second;

							int measure = (int) (curr_frame / beats);
							double beat = curr_frame - measure * beats;
							double duration = prev_frame - curr_frame;

							//find symbol from prev_pose!
							mv::e_level vertical = mv::e_level_c::lvl(
									(e_fl_direction) prev_pose->get_direction(b.get_id()));
							mv::e_direction horizontal = mv::e_direction_c::dir(
									(e_fl_direction) prev_pose->get_direction(b.get_id()));
							std::shared_ptr<mv::i_symbol> symbol = std::shared_ptr<mv::i_symbol>(
									new mv::direction_symbol(vertical, horizontal));

							//setup movement and add it to the sequence
							std::shared_ptr<i_movement> mv = std::shared_ptr<i_movement>(
									new movement(b.get_id(), measure, beat, duration, symbol));
							sequence->add_movement(mv);
						}

						//TODO remove
						std::cout << "prevXX" << std::endl;
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
