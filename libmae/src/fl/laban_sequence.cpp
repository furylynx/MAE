/*
 * FLLabanSequence.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "laban_sequence.hpp"

namespace mae {
	namespace fl {

		laban_sequence::laban_sequence() {
			// TODO Auto-generated destructor stub
		}

		laban_sequence::~laban_sequence() {
			// TODO Auto-generated destructor stub
		}

		void laban_sequence::set_version(std::string version)
		{
			version_ = version;
		}

		std::string laban_sequence::get_version()
		{
			return version_;
		}

		void laban_sequence::set_authors(std::vector<std::string> authors)
		{
			authors_ = authors;
		}
		std::vector<std::string> laban_sequence::get_authors()
		{
			return authors_;
		}

		void laban_sequence::set_title(std::string title)
		{
			title_ = title;
		}

		std::string laban_sequence::get_title()
		{
			return title_;
		}

		void laban_sequence::set_description(std::string description)
		{
			description_ = description;
		}

		std::string laban_sequence::get_description()
		{
			return description_;
		}

		void laban_sequence::set_measures(unsigned int measures)
		{
			measures_ = measures;
		}

		unsigned int laban_sequence::get_measures()
		{
			return measures_;
		}

		void laban_sequence::set_time_unit(time_unit tu)
		{
			time_unit_ = tu;
		}

		time_unit laban_sequence::get_time_unit()
		{
			return time_unit_;
		}

		void laban_sequence::set_beat_duration(unsigned int beat_duration)
		{
			beat_duration_ = beat_duration;
		}

		unsigned int laban_sequence::get_beat_duration()
		{
			return beat_duration_;
		}

		void laban_sequence::set_beats(unsigned int beats)
		{
			beats_ = beats;
		}

		unsigned int laban_sequence::get_beats()
		{
			return beats_;
		}

		void laban_sequence::set_column_definitions(std::vector<std::string> column_definitions)
		{
			column_definitions_ = column_definitions;
		}
		std::vector<std::string> laban_sequence::get_column_definitions()
		{
			return column_definitions_;
		}

		void laban_sequence::set_movements(std::vector<std::shared_ptr<laban_movement> > movements)
		{
			movements_vec_ = movements;

			//TODO
//			for (unsigned int i = 0; i< movements.size(); i++)
//			{
//				movements_.insert(std::make_pair(movements.at(i)->get_column(), movements.at(i)));
//			}
		}

		std::vector<std::shared_ptr<laban_movement> > laban_sequence::get_movements()
		{
			return movements_vec_;
		}

		void laban_sequence::add_movement(int column, std::shared_ptr<laban_movement> movement)
		{
			movements_vec_.push_back(movement);

			std::vector<std::shared_ptr<laban_movement> > col;
			if (movements_.find(movement->get_column()) != movements_.end())
			{
				col = movements_.at(movement->get_column());

				//TODO insert at correct position (order by time)
				//TODO check for intersections...
				col.push_back(movement);
				movements_[movement->get_column()] = col;
			}
			else
			{
				col.push_back(movement);
				movements_.insert(col);
			}
		}

		std::vector<std::shared_ptr<laban_movement> > laban_sequence::get_movements(int column)
		{
			if (movements_.find(column) != movements_.end())
			{
				return movements_.at(column);
			}
			else
			{
				return std::vector<std::shared_ptr<laban_movement> >();
			}
		}


//		//directions and levels
//		const int FLLabanSequence::PLACE_HIGH = 1;
//		const int FLLabanSequence::PLACE_MID = 2;
//		const int FLLabanSequence::PLACE_LOW = 3;
//
//		const int FLLabanSequence::LEFT_HIGH = 4;
//		const int FLLabanSequence::LEFT_MID = 5;
//		const int FLLabanSequence::LEFT_LOW = 6;
//
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_HIGH = 7;
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_MID = 8;
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_LOW = 9;
//
//		const int FLLabanSequence::FORWARD_LEFT_HIGH = 10;
//		const int FLLabanSequence::FORWARD_LEFT_MID = 11;
//		const int FLLabanSequence::FORWARD_LEFT_LOW = 12;
//
//		const int FLLabanSequence::FORWARD_RIGHT_HIGH = 13;
//		const int FLLabanSequence::FORWARD_RIGHT_MID = 14;
//		const int FLLabanSequence::FORWARD_RIGHT_LOW = 15;
//
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_HIGH = 16;
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_MID = 17;
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_LOW = 18;
//
//		const int FLLabanSequence::RIGHT_HIGH = 19;
//		const int FLLabanSequence::RIGHT_MID = 20;
//		const int FLLabanSequence::RIGHT_LOW = 21;
//
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_HIGH = 22;
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_MID = 23;
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_LOW = 24;
//
//		const int FLLabanSequence::BACK_RIGHT_HIGH = 25;
//		const int FLLabanSequence::BACK_RIGHT_MID = 26;
//		const int FLLabanSequence::BACK_RIGHT_LOW = 27;
//
//		const int FLLabanSequence::BACK_LEFT_HIGH = 28;
//		const int FLLabanSequence::BACK_LEFT_MID = 29;
//		const int FLLabanSequence::BACK_LEFT_LOW = 30;
//
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_HIGH = 31;
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_MID = 32;
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_LOW = 33;

	} // namespace fl
} // namespace mae
