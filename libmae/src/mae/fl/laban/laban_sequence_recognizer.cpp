/*
 * laban_sequence_recognizer.cpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#include "laban_sequence_recognizer.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			laban_sequence_recognizer::laban_sequence_recognizer(bool debug)
			{
				debug_ = debug;
				beats_per_measure_ = laban_sequence::default_beats_per_measure();
				beat_duration_ = laban_sequence::default_beat_duration();
				time_unit_ = laban_sequence::default_time_unit();
				reserved_columns_ = laban_sequence::default_columns();

				decision_forest_ = std::shared_ptr<decision_forest>(new decision_forest(column_definitions_, reserved_columns_, beats_per_measure_, beat_duration_, time_unit_));
			}

			laban_sequence_recognizer::laban_sequence_recognizer(std::vector<std::shared_ptr<column_definition> > column_definitions, unsigned int beats_per_measure, unsigned int beat_duration, e_time_unit time_unit, bool debug)
			{
				debug_ = debug;
				column_definitions_ = column_definitions;
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;
				reserved_columns_ = laban_sequence::default_columns();

				decision_forest_ = std::shared_ptr<decision_forest>(new decision_forest(column_definitions_, reserved_columns_, beats_per_measure_, beat_duration_, time_unit_));
			}

			laban_sequence_recognizer::~laban_sequence_recognizer()
			{
			}

			void laban_sequence_recognizer::register_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				registered_sequences_.push_back(sequence);

				decision_forest_->add_sequence(sequence);
			}

			bool laban_sequence_recognizer::deregister_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = registered_sequences_.begin(); it != registered_sequences_.end(); it++)
				{
					//compare by smart pointer
					if (sequence == *it)
					{
						decision_forest_->remove_sequence(*it);

						registered_sequences_.erase(it);

						return true;
					}
				}

				return false;
			}

			bool laban_sequence_recognizer::deregister_sequence(int list_index)
			{
				if (list_index > registered_sequences_.size())
				{
					return false;
				}

				int index = 0;
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = registered_sequences_.begin(); it != registered_sequences_.end(); it++)
				{
					if (index == list_index)
					{
						decision_forest_->remove_sequence(*it);

						registered_sequences_.erase(it);

						return true;
					}

					index ++;
				}

				return false;
			}

			void laban_sequence_recognizer::clear_registered_sequences()
			{
				registered_sequences_.clear();

				//TODO clear forests
			}

			std::list<std::shared_ptr<laban_sequence> > laban_sequence_recognizer::get_registered_sequences()
			{
					return registered_sequences_;
			}

			std::vector<std::shared_ptr<laban_sequence> > laban_sequence_recognizer::recognize_sequence(std::shared_ptr<laban_sequence> sequence, std::vector<bone> body_parts)
			{
				if (debug_)
				{
					std::cout << "laban_sequence_recognizer: recognize sequence" << std::endl;
				}

				return decision_forest_->find_submatches(sequence, body_parts);
			}


		} // namespace laban
	} // namespace fl
} // namespace mae
