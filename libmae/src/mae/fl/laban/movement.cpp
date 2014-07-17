/*
 * labanmovement.cpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

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

				if (column == 0)
				{
					throw std::invalid_argument("Column must not be zero.");
				}

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

			int movement::get_column()
			{
				return column_;
			}

			unsigned int movement::get_measure()
			{
				return measure_;
			}

			double movement::get_beat()
			{
				return beat_;
			}

			double movement::get_duration()
			{
				return duration_;
			}

			std::shared_ptr<ps::i_pre_sign> movement::get_pre_sign()
			{
				return pre_sign_;
			}

			bool movement::get_hold()
			{
				return hold_;
			}

			std::shared_ptr<mv::i_symbol> movement::get_symbol()
			{
				return symbol_;
			}

			std::string movement::xml(unsigned int indent, std::string namesp)
			{
				std::stringstream indent_stream;

				for (unsigned int i = 0; i < indent; i++)
				{
					indent_stream << "\t";
				}

				std::string ns = namesp;
				if (ns.size() > 0 && ns.at(ns.size()-1) != ':')
				{
					ns.push_back(':');
				}


				std::stringstream sstr;

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print definition
				sstr << indent_stream.str() << "<" << ns << "movement>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "column>" << column_ << "</" << ns << "column>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "duration>" << duration_ << "</" << ns << "duration>" << std::endl;

				if (pre_sign_ != nullptr)
				{
					sstr << pre_sign_->xml(indent + 1, namesp);
				}

				sstr << indent_stream.str() << "\t" << "<" << ns << "hold>" << std::boolalpha << hold_ << std::noboolalpha
						<< "</" << ns << "hold>" << std::endl;

				sstr << symbol_->xml(indent + 1, namesp);

				//close movement
				sstr << indent_stream.str() << "</" << ns << "movement>" << std::endl;

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae