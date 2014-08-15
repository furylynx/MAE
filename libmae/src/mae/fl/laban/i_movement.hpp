/*
 * i_movement.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_MOVEMENT_HPP_
#define I_MOVEMENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class i_movement
			{
				public:
					virtual ~i_movement(){}

					/**
					 * Returns the column this movement is attached to. Room direction
					 * and path sign have their own specific column only for those signs
					 * and therefore return 0.
					 *
					 * @return The column id.
					 */
					virtual int get_column();

					/**
					 * Returns the measure in which this symbols begins.
					 * @return
					 */
					virtual unsigned int get_measure();

					/**
					 * Returns the beat in which this symbol begins.
					 *
					 * @return
					 */
					virtual double get_beat();

					/**
					 * Returns the duration of the symbol. Room direction symbols do not have a duration and will return 0.
					 *
					 * @return
					 */
					virtual double get_duration();

					virtual std::string xml(unsigned int indent = 0, std::string namesp = "") = 0;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_MOVEMENT_HPP_
