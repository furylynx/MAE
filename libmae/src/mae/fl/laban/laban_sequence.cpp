/*
 * FLLabanSequence.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "laban_sequence.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			laban_sequence::laban_sequence() : laban_sequence("Untitled", "Anonymous", 0, e_time_unit::MILLISECOND, 0, 0)
			{

			}

			laban_sequence::laban_sequence(std::string title, std::string author, unsigned int measures, e_time_unit time_unit, unsigned int beat_duration, unsigned int beats)
			{
				version_ = "0.5";
				authors_.push_back(author);
				title_ = title;
				description_ = "";

				measures_ = measures;
				time_unit_ = time_unit;
				beat_duration_ = beat_duration;
				beats_ = beats;
			}

			laban_sequence::~laban_sequence()
			{

			}

			std::string laban_sequence::get_version()
			{
				return version_;
			}

			void laban_sequence::set_authors(std::vector<std::string> authors)
			{
				authors_ = authors;
			}

			void laban_sequence::add_author(std::string author)
			{
				authors_.push_back(author);
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

			void laban_sequence::set_time_unit(e_time_unit tu)
			{
				time_unit_ = tu;
			}

			e_time_unit laban_sequence::get_time_unit()
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

			void laban_sequence::set_column_definitions(std::vector<std::shared_ptr<column_definition> > col_defs)
			{
				column_definitions_map_.clear();
				column_definitions_vec_.clear();

				for (unsigned int i = 0; i < col_defs.size(); i++)
				{
					add_column_definition(col_defs.at(i));
				}
			}

			void laban_sequence::add_column_definition(std::shared_ptr<column_definition> col_def)
			{
				column_definitions_vec_.push_back(col_def);

				if (column_definitions_map_.find(col_def->get_column_index()) != column_definitions_map_.end())
				{
					throw std::invalid_argument(
							"A definition for the column is already registered. Use set_column_definitions to overwrite the current definitions.");
				}
				else
				{
					column_definitions_map_.insert(std::make_pair(col_def->get_column_index(), col_def));
				}
			}

			std::vector<std::shared_ptr<column_definition> > laban_sequence::get_column_definitions()
			{
				return column_definitions_vec_;
			}

			std::shared_ptr<column_definition> laban_sequence::get_column_definition(int column_index)
			{
				if (column_definitions_map_.find(column_index) != column_definitions_map_.end())
				{
					return column_definitions_map_.at(column_index);
				}
				else
				{
					throw std::invalid_argument("Definition for column with the given index not registered.");
				}
			}

			void laban_sequence::set_movements(std::vector<std::shared_ptr<i_movement> > movements)
			{
				i_movements_vec_.clear();
				movements_vec_.clear();
				movements_map_.clear();

				for (unsigned int i = 0; i < movements.size(); i++)
				{
					add_movement(movements.at(i));
				}
			}

			std::vector<std::shared_ptr<i_movement> > laban_sequence::get_movements()
			{
				return i_movements_vec_;
			}

			void laban_sequence::add_movement(std::shared_ptr<i_movement> i_mov)
			{

				if (std::shared_ptr<movement> mov = std::dynamic_pointer_cast<movement>(i_mov))
				{
					int col_index = mov->get_column();

					if (col_index != -4 && col_index != -2 && col_index != -1 && col_index != 1 && col_index != 2
							&& col_index != 4)
					{
						if (column_definitions_map_.find(col_index) == column_definitions_map_.end())
						{
							throw std::invalid_argument(
									"No column definition found for the column (and it is no default column). Register a definition first.");
						}
					}

					movements_vec_.push_back(mov);

					std::vector<std::shared_ptr<movement> > col;
					if (movements_map_.find(mov->get_column()) != movements_map_.end())
					{
						col = movements_map_.at(mov->get_column());

						//insert new movement at the correct position in order to have ascending time in the vector
						unsigned int insert_pos = 0;
						for (insert_pos = 0; insert_pos < col.size(); insert_pos++)
						{
//							if (i == col.size())
//							{
//								//insert at the end of the vector
//								col.push_back(mov);
//
//								//must break because
//								break;
//							}
//							else

							if (col.at(insert_pos)->get_measure() <= mov->get_measure()
									&& col.at(insert_pos)->get_beat() <= mov->get_beat())
							{
								//insert at the position

								break;
							}
						}
						col.insert(col.begin() + insert_pos, mov);

						//update the map
						movements_map_[mov->get_column()] = col;
					}
					else
					{
						col.push_back(mov);
						movements_map_.insert(std::make_pair(mov->get_column(), col));
					}
				}

				i_movements_vec_.push_back(i_mov);
			}

			std::vector<std::shared_ptr<movement> > laban_sequence::get_column_movements(int column)
			{
				if (movements_map_.find(column) != movements_map_.end())
				{
					return movements_map_.at(column);
				}
				else
				{
					return std::vector<std::shared_ptr<movement> >();
				}
			}

			std::string laban_sequence::xml()
			{
				std::stringstream sstr;

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

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
				sstr << "\t\t\t" << "<timeUnit>" << e_time_unit_str::str(time_unit_) << "</timeUnit>" << std::endl;
				sstr << "\t\t\t" << "<measure>" << std::endl;
				sstr << "\t\t\t\t" << "<index>" << 0 << "</index>" << std::endl;
				sstr << "\t\t\t\t" << "<beatDuration>" << beat_duration_ << "</beatDuration>" << std::endl;
				sstr << "\t\t\t\t" << "<beats>" << beats_ << "</beats>" << std::endl;
				sstr << "\t\t\t" << "</measure>" << std::endl;
				sstr << "\t\t" << "</timing>" << std::endl;

				//print columns
				sstr << "\t\t" << "<columns>" << std::endl;
				for (unsigned int i = 0; i < column_definitions_vec_.size(); i++)
				{
					sstr << column_definitions_vec_.at(i)->xml(3);
				}
				sstr << "\t\t" << "</columns>" << std::endl;

				//print movements
				sstr << "\t\t" << "<movements>" << std::endl;
				for (unsigned int i = 0; i < i_movements_vec_.size(); i++)
				{
					std::cout << "movement print xml" << std::endl;
					sstr << i_movements_vec_.at(i)->xml(3);
				}
				sstr << "\t\t" << "</movements>" << std::endl;

				//close staff
				sstr << "\t" << "</staff>" << std::endl;

				//close score tag
				sstr << "</score>" << std::endl;

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
