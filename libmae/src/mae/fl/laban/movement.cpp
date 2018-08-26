#include "movement.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			movement::movement(int column, unsigned int measure, double beat, double duration,
					std::shared_ptr<mv::i_symbol> symbol, bool hold, std::shared_ptr<ps::i_pre_sign> pre_sign)
			{
				column_ = column;
				measure_ = measure;
				beat_ = beat;
				duration_ = duration;
				pre_sign_ = pre_sign;
				hold_ = hold;
				symbol_ = symbol;

				if (beat < 0 || duration < 0)
				{
					throw std::invalid_argument("Beat and duration must not be negative.");
				}

				if (symbol == nullptr)
				{
					throw std::invalid_argument("Symbol must not be null.");
				}
			}

			movement::~movement()
			{
			}

			int movement::get_column() const
			{
				return column_;
			}

			unsigned int movement::get_measure() const
			{
				return measure_;
			}

			double movement::get_beat() const
			{
				return beat_;
			}

			double movement::get_duration() const
			{
				return duration_;
			}

			std::shared_ptr<ps::i_pre_sign> movement::get_pre_sign() const
			{
				return pre_sign_;
			}

			bool movement::get_hold() const
			{
				return hold_;
			}

			std::shared_ptr<mv::i_symbol> movement::get_symbol() const
			{
				return symbol_;
			}

			bool movement::equals(std::shared_ptr<i_movement> a) const
			{
				return (column_ == a->get_column() && measure_ == a->get_measure() && beat_ == a->get_beat()
						&& duration_ == a->get_duration() && symbol_equals(a));
			}

			bool movement::symbol_equals(std::shared_ptr<i_movement> a) const
			{
				if (std::shared_ptr<movement> a_mov = std::dynamic_pointer_cast<movement>(a))
				{
					return (a_mov->get_symbol()->equals(symbol_) && a_mov->get_hold() == hold_
							&& ((a_mov->get_pre_sign() == nullptr && pre_sign_ == nullptr)
									|| (a_mov->get_pre_sign() != nullptr && a_mov->get_pre_sign()->equals(pre_sign_))));
				}
				else
				{
					return false;
				}
			}

			bool movement::all_types_equal(std::shared_ptr<i_movement> a) const
			{
				if (std::shared_ptr<movement> a_mov = std::dynamic_pointer_cast<movement>(a))
				{
					return (a_mov->get_symbol()->all_types_equal(symbol_) && ((a_mov->get_pre_sign() == nullptr && pre_sign_ == nullptr)
								|| (a_mov->get_pre_sign() != nullptr && a_mov->get_pre_sign()->all_types_equal(pre_sign_))));
				}
				else
				{
					return false;
				}
			}

			std::vector<double> movement::symbol_feature_vector(double hierarchy_factor) const
			{
				std::vector<double> result;

				result.push_back(hold_);

				std::vector<double> fvec_sym = symbol_->feature_vector(hierarchy_factor);

				result.insert(result.end(), fvec_sym.begin(), fvec_sym.end());

				return result;
			}

			std::vector<std::type_index> movement::get_type_path() const
			{
				std::vector<std::type_index> result;
				result.push_back(std::type_index(typeid(mae::fl::laban::i_movement)));
				result.push_back(std::type_index(typeid(mae::fl::laban::movement)));

				std::vector<std::type_index> symbol_type_path = symbol_->get_type_path();

				result.insert(result.end(), symbol_type_path.begin(), symbol_type_path.end() );

				return result;
			}

			std::string movement::xml(unsigned int indent, std::string namesp) const
			{
				std::stringstream indent_stream;

				for (unsigned int i = 0; i < indent; i++)
				{
					indent_stream << "\t";
				}

				std::string ns = namesp;
				if (ns.size() > 0 && ns.at(ns.size() - 1) != ':')
				{
					ns.push_back(':');
				}

				std::stringstream sstr;

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print definition
				sstr << indent_stream.str() << "<" << ns << "movement>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "column>" << column_ << "</" << ns << "column>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "duration>" << duration_ << "</" << ns
						<< "duration>" << std::endl;

				if (pre_sign_ != nullptr)
				{
					sstr << pre_sign_->xml(indent + 1, namesp);
				}

				sstr << indent_stream.str() << "\t" << "<" << ns << "hold>" << std::boolalpha << hold_
						<< std::noboolalpha << "</" << ns << "hold>" << std::endl;

				sstr << symbol_->xml(indent + 1, namesp);

				//close movement
				sstr << indent_stream.str() << "</" << ns << "movement>" << std::endl;

				return sstr.str();
			}

			std::string movement::svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const
			{
				return svg(draw_laban_rect(im_width, im_height, max_column, measures, beats_per_measure));
			}

			std::string movement::svg(draw_laban_rect rect, svg_style style) const
			{
				std::stringstream id_sstr;
				id_sstr << "movement-" << column_ << "-" << measure_ << "-" << beat_ ;
				std::string identifier = id_sstr.str();

				std::stringstream sstr;

				int total_beats = (rect.get_measures() + 1) * rect.get_beats_per_measure();
				double column_width = (rect.get_im_width())/(rect.get_max_column() * 2.0);
				double beat_height = (rect.get_im_height()*(0.85 - 0.01)) / total_beats;

				double draw_w = column_width / 2.0;
				double draw_x_pos = (rect.get_im_width() / 2.0) + ((column_ - (mae::math::math::sign(column_)*0.5) - 0.25)*column_width);

				double draw_y_pos = 0;
				double draw_h = 0;

				if (measure_ != 0)
				{
					draw_y_pos = rect.get_im_height()*(0.85 - 0.01) - (measure_ * rect.get_beats_per_measure() + beat_
															+ duration_) * beat_height;
					draw_h = beat_height * duration_;
				}
				else
				{
					draw_y_pos = rect.get_im_height()*(0.85) - (measure_ * rect.get_beats_per_measure() + beat_
						+ rect.get_beats_per_measure()) * beat_height;
					draw_h = beat_height * rect.get_beats_per_measure();
				}

				double draw_hold_y = 0;
				double draw_hold_h = draw_w/3.0;

				if (hold_)
				{
					draw_hold_y = draw_y_pos;

					draw_y_pos += draw_hold_h;
					draw_h -= draw_hold_h;

					if (draw_h < 0)
					{
						draw_y_pos += draw_h;
						draw_h = 0.01;
					}
				}

				double draw_ps_h = draw_w/2.0;
				if (pre_sign_ != nullptr)
				{
					//reduce height
					draw_h -= draw_ps_h;

					if (draw_h < 0)
					{
						draw_h = 0.01;
						draw_ps_h = 0.01;
					}
				}

				sstr << symbol_->svg(identifier, draw_rect(draw_x_pos, draw_y_pos, draw_w, draw_h), (column_ < 0), style);

				//draw hold sign
				if (hold_)
				{
					//draw circle
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << draw_x_pos + draw_w/2.0 + draw_hold_h/2.0 << "," << draw_hold_y + draw_hold_h/2.0 << " a " << draw_hold_h/2.0 << "," << draw_hold_h/2.0 << " 0 1 1 -" << draw_hold_h << ",0 " << draw_hold_h/2.0 << "," << draw_hold_h/2.0 << " 0 1 1 " << draw_hold_h << ",0 z\"" << std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-hold\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;
				}

				if (pre_sign_ != nullptr)
				{
					//pre sign
					double draw_ps_y = draw_y_pos + draw_h;
					sstr << pre_sign_->svg(identifier, draw_rect(draw_x_pos+draw_ps_h/2.0, draw_ps_y, draw_ps_h, draw_ps_h), false, style);
				}

				return sstr.str();
			}

			std::shared_ptr<i_movement> movement::recreate(std::map<int, int> column_mapping, unsigned int measure,
					double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				int column = column_;

				if (column_mapping.find(column_) != column_mapping.end())
				{
					column = column_mapping.at(column_);
				}

				result = std::shared_ptr<i_movement>(
						new movement(column, measure, beat, duration, symbol_, hold_, pre_sign_));

				return result;
			}

			std::string movement::str() const
			{
				std::stringstream sstr;

				sstr << "movement: [c" << column_ << ",m" << measure_ << ",b" << beat_ << ",d" << duration_ << ",h"
						<< hold_ << "] " << symbol_;

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
