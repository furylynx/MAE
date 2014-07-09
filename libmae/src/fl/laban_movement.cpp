/*
 * labanmovement.cpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#include "laban_movement.hpp"


namespace mae
{
	namespace fl
	{

		laban_movement::laban_movement(int column, unsigned int measure, double beat, double duration, bool hold,
				laban_direction dir, laban_level lvl, contact_hook c_hook)
		{
			column_ = column;
			measure_ = measure;
			beat_ = beat;
			duration_ = duration;
			hold_ = hold;
			direction_ = dir;
			level_ = lvl;
			contact_hook_ = c_hook;
		}

		laban_movement::~laban_movement()
		{
			// TODO Auto-generated destructor stub
		}

		int laban_movement::get_column()
		{
			return column_;
		}

		unsigned int laban_movement::get_measure()
		{
			return measure_;
		}

		double laban_movement::get_beat()
		{
			return beat_;
		}

		double laban_movement::get_duration()
		{
			return duration_;
		}

		bool laban_movement::get_hold()
		{
			return hold_;
		}

		laban_direction laban_movement::get_direction()
		{
			return direction_;
		}

		laban_level laban_movement::get_level()
		{
			return level_;
		}

		std::string laban_movement::xml(unsigned int indent)
		{
			std::stringstream indent_stream;

			for (unsigned int i = 0; i < indent; i++)
			{
				indent_stream << "\t";
			}

			std::stringstream sstr;

			//print definition
			sstr << indent_stream.str() << "<movement>" << std::endl;

			sstr << indent_stream.str() << "\t" << "<column>" << column_ << "</column>" << std::endl;
			sstr << indent_stream.str() << "\t" << "<measure>" << measure_ << "</measure>" << std::endl;
			sstr << indent_stream.str() << "\t" << "<beat>" << beat_ << "</beat>" << std::endl;
			sstr << indent_stream.str() << "\t" << "<duration>" << duration_ << "</duration>" << std::endl;
			//TODO pre-sign...
			sstr << indent_stream.str() << "\t" << "<hold>" << std::boolalpha << hold_ << std::noboolalpha << "</hold>"
					<< std::endl;

			if (direction_ != laban_direction::NONE && level_ != laban_level::NONE)
			{
				//print direction
				sstr << indent_stream.str() << "\t" << "<direction>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "<vertical>" << laban_level_str[(int)level_] << "</vertical>"
						<< std::endl;
				sstr << indent_stream.str() << "\t\t" << "<horizontal>" << laban_direction_str[(int)direction_]
						<< "</horizontal>" << std::endl;

				//TODO modification pin
				//TODO relationship pin
				//TODO space measurement
				//TODO dynamics

				if (contact_hook_ != contact_hook::NONE)
				{
					sstr << indent_stream.str() << "\t\t" << "<contactHook>" << contact_hook_str[(int)contact_hook_]
							<< "</contactHook>" << std::endl;
				}

				//close direction
				sstr << indent_stream.str() << "\t" << "<direction>" << std::endl;
			}

			//TODO other movements apart from directions...

			//close movement
			sstr << indent_stream.str() << "</movement>" << std::endl;

			return sstr.str();
		}

	} // namespace fl
} // namespace mae
