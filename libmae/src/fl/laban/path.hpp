/*
 * path.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef PATH_HPP_
#define PATH_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "e_path_type.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class path: public i_movement
			{
				public:
					path(e_path_type type, unsigned int measure, double beat, double duration);
					virtual ~path();

					e_path_type get_type();
					unsigned int get_measure();
					double get_beat();
					double get_duration();

					virtual std::string xml(unsigned int indent = 0);

				private:
					e_path_type type_;
					unsigned int measure_;
					double beat_;
					double duration_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // PATH_HPP_
