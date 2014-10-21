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

			laban_sequence::laban_sequence()
					: laban_sequence("Untitled", "Anonymous", 0, e_time_unit::MILLISECOND, 0, 0)
			{

			}

			laban_sequence::laban_sequence(std::string title, std::string author, unsigned int measures,
					e_time_unit time_unit, unsigned int beat_duration, unsigned int beats)
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

			std::string laban_sequence::get_version() const
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

			std::vector<std::string> laban_sequence::get_authors() const
			{
				return authors_;
			}

			void laban_sequence::set_title(std::string title)
			{
				title_ = title;
			}

			std::string laban_sequence::get_title() const
			{
				return title_;
			}

			void laban_sequence::set_description(std::string description)
			{
				description_ = description;
			}

			std::string laban_sequence::get_description() const
			{
				return description_;
			}

			void laban_sequence::set_measures(unsigned int measures)
			{
				measures_ = measures;
			}

			unsigned int laban_sequence::get_measures() const
			{
				return measures_;
			}

			void laban_sequence::set_time_unit(e_time_unit tu)
			{
				time_unit_ = tu;
			}

			e_time_unit laban_sequence::get_time_unit() const
			{
				return time_unit_;
			}

			void laban_sequence::set_beat_duration(unsigned int beat_duration)
			{
				beat_duration_ = beat_duration;
			}

			unsigned int laban_sequence::get_beat_duration() const
			{
				return beat_duration_;
			}

			void laban_sequence::set_beats(unsigned int beats)
			{
				beats_ = beats;
			}

			unsigned int laban_sequence::get_beats() const
			{
				return beats_;
			}

			void laban_sequence::set_column_definitions(std::vector<std::shared_ptr<column_definition> > col_defs)
			{
				clear_column_definitions();

				for (unsigned int i = 0; i < col_defs.size(); i++)
				{
					add_column_definition(col_defs.at(i));
				}
			}

			void laban_sequence::add_column_definition(std::shared_ptr<column_definition> col_def)
			{
				if (col_def == nullptr)
				{
					throw std::invalid_argument("Column definition must not be null!");
				}

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

			std::vector<std::shared_ptr<column_definition> > laban_sequence::get_column_definitions() const
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

			void laban_sequence::clear_column_definitions()
			{
				if (i_movements_vec_.size() > 0)
				{
					throw std::runtime_error(
							"laban_sequence: Cannot clear the column definitions because there are already movements registered. Clear movements first.");
				}

				column_definitions_map_.clear();
				column_definitions_vec_.clear();
			}

			std::vector<int> laban_sequence::get_columns() const
			{
				std::vector<int> result;

				result.push_back(-4);
				result.push_back(-2);
				result.push_back(-1);
				result.push_back(1);
				result.push_back(2);
				result.push_back(4);

				//insert all defined columns too regarding the order of the vector
				for (unsigned int i = 0; i < column_definitions_vec_.size(); i++)
				{
					//TODO remove
					std::cout << i + 1 << "/" << column_definitions_vec_.size() << std::endl;
					std::cout << " >> col index " << column_definitions_vec_.at(i)->get_column_index() << std::endl;

					for (std::vector<int>::iterator it = result.begin(); it != result.end(); it++)
					{
						if (*it > column_definitions_vec_.at(i)->get_column_index())
						{
							result.insert(it, column_definitions_vec_.at(i)->get_column_index());
							break;
						}
					}
				}

				return result;

			}

			void laban_sequence::set_movements(std::vector<std::shared_ptr<i_movement> > movements)
			{
				clear_movements();

				for (unsigned int i = 0; i < movements.size(); i++)
				{
					add_movement(movements.at(i));
				}
			}

			std::vector<std::shared_ptr<i_movement> > laban_sequence::get_movements() const
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

					if (last_movement_ == nullptr
							|| (last_movement_->get_measure() < mov->get_measure()
									|| (last_movement_->get_measure() == mov->get_measure()
											&& last_movement_->get_beat() < mov->get_beat())))
					{
						last_movement_ = i_mov;
					}

					std::vector<std::shared_ptr<i_movement> > col;
					if (movements_map_.find(mov->get_column()) != movements_map_.end())
					{
						col = movements_map_.at(mov->get_column());

						//insert new movement at the correct position in order to have ascending time in the vector
						unsigned int insert_pos = 0;
						for (unsigned int i = 0; i < col.size(); i++)
						{
							std::shared_ptr<i_movement> col_item = col.at(insert_pos);

							if (col_item->get_measure() > mov->get_measure()
									|| (col_item->get_measure() == mov->get_measure()
											&& col_item->get_beat() >= mov->get_beat()))
							{
								//insert at the position

								break;
							}
							else
							{
								insert_pos++;
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

			std::vector<std::shared_ptr<i_movement> > laban_sequence::get_column_movements(int column) const
			{
				if (movements_map_.find(column) != movements_map_.end())
				{
					return movements_map_.at(column);
				}
				else
				{
					return std::vector<std::shared_ptr<i_movement> >();
				}
			}

			std::shared_ptr<i_movement> laban_sequence::get_last_movement() const
			{
				return last_movement_;
			}

			void laban_sequence::clear_movements()
			{
				i_movements_vec_.clear();
				movements_vec_.clear();
				movements_map_.clear();
				last_movement_ = nullptr;
			}

			std::string laban_sequence::xml(bool no_header, unsigned int indent, std::string namesp) const
			{
				std::stringstream sstr_indent;

				for (unsigned int i = 0; i < indent; i++)
				{
					sstr_indent << "\t";
				}
				std::string str_indent = sstr_indent.str();

				std::string namesp_r = namesp;
				if (namesp.size() > 0)
				{
					namesp_r.append(":");
				}

				std::stringstream sstr;

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print xml header
				if (!no_header)
				{
					sstr << str_indent << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
				}

				//print score tag
				if (!no_header)
				{
					sstr << str_indent << "<" << namesp_r << "score " << xml_namespace_header(namesp) << ">"
							<< std::endl;
				}
				else
				{
					sstr << str_indent << "<" << namesp_r << "score>" << std::endl;
				}

				//print header
				sstr << str_indent << "\t" << "<" << namesp_r << "version>" << version_ << "</" << namesp_r
						<< "version>" << std::endl;

				for (unsigned int i = 0; i < authors_.size(); i++)
				{
					sstr << str_indent << "\t" << "<" << namesp_r << "author>" << authors_.at(i) << "</" << namesp_r
							<< "author>" << std::endl;
				}
				sstr << str_indent << "\t" << "<" << namesp_r << "title>" << title_ << "</" << namesp_r << "title>"
						<< std::endl;
				sstr << str_indent << "\t" << "<" << namesp_r << "description>" << description_ << "</" << namesp_r
						<< "description>" << std::endl;

				//print staff
				sstr << str_indent << "\t" << "<" << namesp_r << "staff>" << std::endl;

				//print staff header
				sstr << str_indent << "\t\t" << "<" << namesp_r << "measures>" << measures_ << "</" << namesp_r
						<< "measures>" << std::endl;
				sstr << str_indent << "\t\t" << "<" << namesp_r << "timing>" << std::endl;
				sstr << str_indent << "\t\t\t" << "<" << namesp_r << "timeUnit>" << e_time_unit_c::str(time_unit_)
						<< "</" << namesp_r << "timeUnit>" << std::endl;
				sstr << str_indent << "\t\t\t" << "<" << namesp_r << "measure>" << std::endl;
				sstr << str_indent << "\t\t\t\t" << "<" << namesp_r << "index>" << 0 << "</" << namesp_r << "index>"
						<< std::endl;
				sstr << str_indent << "\t\t\t\t" << "<" << namesp_r << "beatDuration>" << beat_duration_ << "</"
						<< namesp_r << "beatDuration>" << std::endl;
				sstr << str_indent << "\t\t\t\t" << "<" << namesp_r << "beats>" << beats_ << "</" << namesp_r
						<< "beats>" << std::endl;
				sstr << str_indent << "\t\t\t" << "</" << namesp_r << "measure>" << std::endl;
				sstr << str_indent << "\t\t" << "</" << namesp_r << "timing>" << std::endl;

				//print columns
				sstr << str_indent << "\t\t" << "<" << namesp_r << "columns>" << std::endl;
				for (unsigned int i = 0; i < column_definitions_vec_.size(); i++)
				{
					sstr << column_definitions_vec_.at(i)->xml(indent + 3, namesp);
				}
				sstr << str_indent << "\t\t" << "</" << namesp_r << "columns>" << std::endl;

				//print movements
				sstr << str_indent << "\t\t" << "<" << namesp_r << "movements>" << std::endl;
				for (unsigned int i = 0; i < i_movements_vec_.size(); i++)
				{
					sstr << i_movements_vec_.at(i)->xml(indent + 3, namesp);
				}
				sstr << str_indent << "\t\t" << "</" << namesp_r << "movements>" << std::endl;

				//close staff
				sstr << str_indent << "\t" << "</" << namesp_r << "staff>" << std::endl;

				//close score tag
				sstr << str_indent << "</" << namesp_r << "score>" << std::endl;

				return sstr.str();
			}

			std::string laban_sequence::xml_namespace_header(std::string namesp) const
			{
				std::stringstream sstr;

				sstr << "xmlns";
				if (namesp.size() > 0)
				{
					sstr << ":" << namesp;
				}

				sstr
						<< "=\"http://www.example.org/labanotation\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\""
						<< xml_schema_location() << "\"";

				return sstr.str();
			}

			std::string laban_sequence::xml_schema_location() const
			{
				return "http://www.example.org/labanotation labanotation.xsd";
			}

			std::string laban_sequence::xml_namespace_uri() const
			{
				return "http://www.example.org/labanotation";
			}

			void laban_sequence::xml_file(std::string path) const
			{
				std::ofstream outfile(path);

				if (outfile.is_open())
				{
					outfile << xml();
					outfile.close();
				}
				else
				{
					throw std::invalid_argument("Cannot write to the file.");
				}
			}

			std::string laban_sequence::svg(unsigned int im_width, unsigned int im_height) const
			{
				std::stringstream sstr;

				//print header
				sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
				sstr << "<svg" << std::endl;
				sstr << "\txmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << std::endl;
				sstr << "\txmlns:cc=\"http://creativecommons.org/ns#\"" << std::endl;
				sstr << "\txmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"" << std::endl;
				sstr << "\txmlns:svg=\"http://www.w3.org/2000/svg\"" << std::endl;
				sstr << "\txmlns=\"http://www.w3.org/2000/svg\"" << std::endl;
				sstr << "\tversion=\"1.1\"" << std::endl;
				sstr << "\twidth=\"" << im_width << "\"" << std::endl;
				sstr << "\theight=\"" << im_height << "\"" << std::endl;
				sstr << "\tid=\"svg3545\">" << std::endl;
				sstr << "\t<defs id=\"defs3547\" >" << std::endl;
				sstr << svg_fill_pattern("fillpattern", im_width, im_height) << std::endl;
				sstr << "\t</defs>" << std::endl;

				sstr << "\t<metadata id=\"metadata3550\">" << std::endl;
				sstr << "\t\t<rdf:RDF>" << std::endl;
				sstr << "\t\t\t<cc:Work rdf:about=\"\">" << std::endl;
				sstr << "\t\t\t\t<dc:format>image/svg+xml</dc:format>" << std::endl;
				sstr << "\t\t\t\t<dc:type rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />" << std::endl;
				sstr << "\t\t\t\t<dc:title></dc:title>" << std::endl;
				sstr << "\t\t\t</cc:Work>" << std::endl;
				sstr << "\t\t</rdf:RDF>" << std::endl;
				sstr << "\t</metadata>" << std::endl;
				sstr << "\t<g id=\"layer1\">" << std::endl;

				//print staff
				std::vector<int> cols = get_columns();
				int max_index = std::abs(cols.at(0));
				if (std::abs(cols.back()) > max_index)
				{
					max_index = cols.back();
				}

				int total_beats = measures_ * beats_;
				double beat_height = (im_height*(0.85 - 0.01)) / total_beats;
				double column_width = (im_width) / (max_index * 2.0);

				//draw staff
				int left_bound = (int) ((im_width / 2.0) - (2.0 * column_width));
				int right_bound = (int) ((im_width / 2.0) + (2.0 * column_width));
				int bottom_bound = (int)(im_height*0.85);
				int top_bound = 0;
				int center = (int) (im_width / 2.0);

				//bottom line
				sstr << "\t\t<path d=\"m " << left_bound << "," << bottom_bound << " " << right_bound - left_bound << ","
						<< 0 << "\" id=\"bottomline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				//top line
				sstr << "\t\t<path d=\"m " << left_bound << "," << 0 << " "
						<< (im_width / 2 + 2 * column_width) - left_bound << "," << 0 << "\" id=\"topline\""
						<< std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				//draw movement start lines
				int start_line_y = (int) (im_height*(0.85) - (beat_height * beats_));

				sstr << "\t\t<path d=\"m " << left_bound << "," << start_line_y << " " << right_bound - left_bound << ","
						<< 0 << "\" id=\"upperstartline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				sstr << "\t\t<path d=\"m " << left_bound << "," << start_line_y - im_height*(0.01) << " " << right_bound - left_bound
						<< "," << 0 << "\" id=\"lowerstartline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				//draw center line
				sstr << "\t\t<path d=\"m " << center << "," << top_bound << " " << 0 << "," << bottom_bound - top_bound
						<< "\" id=\"centerline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				//draw right and left line
				sstr << "\t\t<path d=\"m " << left_bound << "," << top_bound << " " << 0 << ","
						<< bottom_bound - top_bound << "\" id=\"leftline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				sstr << "\t\t<path d=\"m " << right_bound << "," << top_bound << " " << 0 << ","
						<< bottom_bound - top_bound << "\" id=\"rightline\"" << std::endl;
				sstr
						<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
						<< std::endl;

				//draw beat and measure marks
				for (unsigned int i = beats_ + 1; i < measures_ * beats_; i++)
				{
					int mark_pos_y = (int) (im_height*(0.85 - 0.01) - (i * beat_height));
					if ((i % beats_) == 0)
					{
						//is a measure -> more width
						sstr << "\t\t<path d=\"m " << left_bound << "," << mark_pos_y << " " << right_bound - left_bound
								<< "," << 0 << "\" id=\"measuremark" << i / beats_ << "\"" << std::endl;
						sstr
								<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
								<< std::endl;
					}
					else
					{
						//is a beat -> less width
						sstr << "\t\t<path d=\"m " << center - (column_width / 6.0) << "," << mark_pos_y << " "
								<< (column_width / 3.0) << "," << 0 << "\" id=\"beatmark" << i << "\"" << std::endl;
						sstr
								<< "\t\t\t style=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
								<< std::endl;
					}
				}

				//TODO coldefs...

				//handle movements
				for (unsigned int i = 0; i < movements_vec_.size(); i++)
				{
					sstr << movements_vec_.at(i)->svg(im_width, im_height, max_index, measures_, beats_);
				}

				sstr << "\t</g>" << std::endl;
				sstr << "</svg>" << std::endl;

				return sstr.str();
			}

			void laban_sequence::svg_file(std::string path, unsigned int im_width, unsigned int im_height) const
			{
				std::ofstream outfile(path);

				if (outfile.is_open())
				{
					outfile << svg(im_width, im_height);
					outfile.close();
				}
				else
				{
					throw std::invalid_argument("Cannot write to the file.");
				}
			}

			std::string laban_sequence::svg_fill_pattern(std::string pattern_name, unsigned int im_width,
					unsigned int im_height) const
			{
				int step = std::ceil(im_height / 25.0);

				std::stringstream sstr;

				sstr << "\t\t<pattern" << std::endl;
				sstr << "\t\t\t\tid=\"" << pattern_name << "\"" << std::endl;
				sstr << "\t\t\t\tpatternTransform=\"translate(550.0,-750.0)\"" << std::endl;
				sstr << "\t\t\t\theight=\"2195.3125\"" << std::endl;
				sstr << "\t\t\t\twidth=\"2028.4062\"" << std::endl;
				sstr << "\t\t\t\tpatternUnits=\"userSpaceOnUse\">" << std::endl;
				sstr << "\t\t\t<g" << std::endl;
				sstr << "\t\t\t\ttransform=\"translate(639.625,561.71875)\"" << std::endl;
				sstr << "\t\t\t\tid=\"pattern-graphics\">" << std::endl;

				for (unsigned int i = 0; i < im_height + (im_width * 3); i += step)
				{
					sstr << "\t\t\t\t<path" << std::endl;
					sstr << "\t\t\t\t\tid=\"fillpattern-path" << i << "\"" << std::endl;
					sstr << "\t\t\t\t\td=\"m " << -(int)im_width << "," << i << " " << im_width * 3.0 << "," << -(int)im_width * 3.0
							<< "\"" << std::endl;
					sstr
							<< "\t\t\t\t\tstyle=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
							<< std::endl;
				}

				sstr << "\t\t\t</g>" << std::endl;
				sstr << "\t\t</pattern>";

				return sstr.str();
			}

			std::string laban_sequence::str() const
			{
				return title_;
			}

			unsigned int laban_sequence::default_beat_duration()
			{
				return 200;
			}

			unsigned int laban_sequence::default_beats_per_measure()
			{
				return 5;
			}

			e_time_unit laban_sequence::default_time_unit()
			{
				return e_time_unit::MILLISECOND;
			}

			std::vector<int> laban_sequence::default_columns()
			{
				std::vector<int> result;
				result.push_back(-4);
				result.push_back(-2);
				//result.push_back(-3); // not reserved by Groeschner's XML schema
				result.push_back(-1);
				result.push_back(1);
				result.push_back(2);
				//result.push_back(3); // not reserved by Groeschner's XML schema
				result.push_back(4);

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
