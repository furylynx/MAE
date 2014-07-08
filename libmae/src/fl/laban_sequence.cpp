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
			version_ = "0.5";
			authors_.push_back("Anonymous");
			title_ = "Untitled";
			description_ = "";

			measures_ = 0;
			time_unit_ = time_unit::MILLISECOND;
			beat_duration_ = 0;
			beats_ = 0;
		}

		laban_sequence::~laban_sequence() {

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

		void laban_sequence::set_column_definitions(std::vector<std::shared_ptr<laban_column> > column_definitions)
		{
			column_definitions_ = column_definitions;
		}

		void laban_sequence::add_column_definition(std::shared_ptr<laban_column> definition)
		{
			column_definitions_.push_back(definition);
		}

		std::vector<std::shared_ptr<laban_column> > laban_sequence::get_column_definitions()
		{
			return column_definitions_;
		}

		void laban_sequence::set_movements(std::vector<std::shared_ptr<laban_movement> > movements)
		{
			for (unsigned int i = 0; i < movements.size(); i++)
			{
				add_movement(movements.at(i));
			}
		}

		std::vector<std::shared_ptr<laban_movement> > laban_sequence::get_movements()
		{
			return movements_vec_;
		}

		void laban_sequence::add_movement(std::shared_ptr<laban_movement> movement)
		{
			movements_vec_.push_back(movement);

			std::vector<std::shared_ptr<laban_movement> > col;
			if (movements_.find(movement->get_column()) != movements_.end())
			{
				col = movements_.at(movement->get_column());

				//insert new movement at the correct position in order to have ascending time in the vector
				for (unsigned int i = 0; i <= col.size(); i++)
				{
					if (i == col.size())
					{
						//insert at the end of the vector
						col.push_back(movement);
					}
					else if (col.at(i)->get_measure() <= movement->get_measure() && col.at(i)->get_beat() <= movement->get_beat())
					{
						//insert at the position
						col.insert(col.begin()+i, movement);
						break;
					}
				}

				//update the map
				movements_[movement->get_column()] = col;
			}
			else
			{
				col.push_back(movement);
				movements_.insert(std::make_pair(movement->get_column(), col));
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

		std::string laban_sequence::xml()
		{
			std::stringstream sstr;

			//print score tag
			sstr << "<score>" << std::endl;

			//print header
			sstr << "\t" << "<version>" << version_ << "</version>" << std::endl;

			for (unsigned int i = 0; i < authors_.size(); i++)
			{
				sstr << "\t" << "<author>" << authors_.at(i) << "</author>" << std::endl;
			}
			sstr << "\t" << "<title>" << title_ << "</title>" << std::endl;
			sstr << "\t" << "<description>" << description_ << "</description>" << std::endl;

			//print staff
			sstr << "\t" << "<staff>" << std::endl;

			//print staff header
			sstr << "\t\t" << "<measures>" << measures_ << "</measures>" << std::endl;
			sstr << "\t\t" << "<timing>" << std::endl;
			sstr << "\t\t\t" << "<timeUnit>" << time_unit_str[(int)time_unit_] << "</timeUnit>" << std::endl;
			sstr << "\t\t\t" << "<measure>" << std::endl;
			sstr << "\t\t\t\t" << "<index>" << 0 << "</index>" << std::endl;
			sstr << "\t\t\t\t" << "<beatDuration>" << beat_duration_ << "</beatDuration>" << std::endl;
			sstr << "\t\t\t\t" << "<beats>" << beats_ << "</beats>" << std::endl;
			sstr << "\t\t\t" << "</measure>" << std::endl;
			sstr << "\t\t" << "</timing>" << std::endl;

			//print columns
			sstr << "\t\t" << "<columns>" << std::endl;
			for (unsigned int i = 0; i < column_definitions_.size(); i++)
			{
				sstr << column_definitions_.at(i)->xml(3);
			}
			sstr << "\t\t" << "</columns>" << std::endl;


			//print movements
			sstr << "\t\t" << "<movements>" << std::endl;
			for (unsigned int i = 0; i < column_definitions_.size(); i++)
			{
				sstr << movements_vec_.at(i)->xml(3);
			}
			sstr << "\t\t" << "</movements>" << std::endl;

			//close staff
			sstr << "\t" << "</staff>" << std::endl;

			//close score tag
			sstr << "</score>" << std::endl;

			return sstr.str();
		}


	} // namespace fl
} // namespace mae
