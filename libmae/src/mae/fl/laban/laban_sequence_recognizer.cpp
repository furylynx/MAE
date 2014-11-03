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
				if (debug)
				{
					std::cout << "creating laban sequence recognizer.";
				}

				debug_ = debug;
				column_definitions_ = column_definitions;
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;
				reserved_columns_ = laban_sequence::default_columns();

				//TODO rewriting rules...
				decision_forest_ = std::shared_ptr<decision_forest>(new decision_forest(column_definitions_, reserved_columns_, beats_per_measure_, beat_duration_, time_unit_));

			}

			laban_sequence_recognizer::~laban_sequence_recognizer()
			{
			}

			void laban_sequence_recognizer::set_recognition_tolerance(double tolerance)
			{
				decision_forest_->set_recognition_tolerance(tolerance);
			}

			std::shared_ptr<decision_forest> laban_sequence_recognizer::get_decision_forest() const
			{
				return decision_forest_;
			}

			void laban_sequence_recognizer::register_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				decision_forest_->add_sequence(sequence);
			}

			bool laban_sequence_recognizer::deregister_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				return decision_forest_->remove_sequence(sequence);
			}

			bool laban_sequence_recognizer::deregister_sequence(unsigned int list_index)
			{
				return decision_forest_->remove_sequence(list_index);
			}

			void laban_sequence_recognizer::clear_registered_sequences()
			{
				decision_forest_->clear();
			}

			std::list<std::shared_ptr<laban_sequence> > laban_sequence_recognizer::get_registered_sequences() const
			{
				return decision_forest_->get_sequences();
			}

			int laban_sequence_recognizer::get_sequence_length(std::shared_ptr<laban_sequence> sequence) const
			{
				return decision_forest_->get_sequence_length(sequence);
			}

			std::vector<std::shared_ptr<laban_sequence> > laban_sequence_recognizer::recognize_sequence(std::shared_ptr<laban_sequence> sequence, std::vector<bone> body_parts)
			{
				if (debug_)
				{
					std::cout << "laban_sequence_recognizer: recognize sequence" << std::endl;
				}

				return decision_forest_->find_submatches(sequence, body_parts);
			}

			std::string laban_sequence_recognizer::str() const
			{
				return decision_forest_->str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
