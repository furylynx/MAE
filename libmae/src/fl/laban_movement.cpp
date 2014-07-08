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

		laban_movement::laban_movement()
		{
			column_ = 0;
			measure_ = 0;
			beat_ = 0;
			duration_ = 0;
			hold_ = 0;
			direction_ = direction::PLACE;
			level_ = level::MIDDLE;
			contact_hook_ = contact_hook::NONE;
		}

		laban_movement::laban_movement(int column, unsigned int measure, double beat, double duration, bool hold, direction dir, level lvl, contact_hook c_hook)
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

		direction laban_movement::get_direction()
		{
			return direction_;
		}

		level laban_movement::get_level()
		{
			return level_;
		}

		std::string laban_movement::xml()
		{
			std::stringstream sstr;
			//TODO export to xml

			return sstr.str();
		}

	} // namespace fl
} // namespace mae
