/*
 * room_direction.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "room_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			room_direction::room_direction(unsigned int measure, double beat, std::shared_ptr<mv::pin> direction)
			{
				measure_ = measure;
				beat_ = beat;
				direction_ = direction;

				if (beat < 0)
				{
					throw std::invalid_argument("Beat must not be negative.");
				}

				if (direction == nullptr)
				{
					throw std::invalid_argument("Direction must not be null.");
				}

			}

			room_direction::~room_direction()
			{
			}

			int room_direction::get_column()
			{
				return 0;
			}

			unsigned int room_direction::get_measure()
			{
				return measure_;
			}

			double room_direction::get_beat()
			{
				return beat_;
			}

			double room_direction::get_duration()
			{
				return 0;
			}

			std::shared_ptr<mv::pin> room_direction::get_direction()
			{
				return direction_;
			}

			std::string room_direction::xml(unsigned int indent, std::string namesp)
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

				sstr << std::fixed << std::setprecision(2);

				//print turn symbol
				sstr << indent_stream.str() << "<" << ns << "roomDirection>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>" << std::endl;
				sstr << direction_->xml(indent+1, namesp);

				sstr << indent_stream.str() << "</" << ns << "roomDirection>" << std::endl;

				return sstr.str();

			}

			std::shared_ptr<i_movement> room_direction::recreate(std::unordered_map<int, int> column_mapping, unsigned int measure, double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				result = std::shared_ptr<i_movement>(new room_direction(measure, beat, direction_));

				return result;
			}

			std::string room_direction::str() const
			{
				std::stringstream sstr;

				sstr << "(ROOM_DIRECTION)";

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
