#ifndef MAE_FL_FLDIRECTIONMAP_HPP_
#define MAE_FL_FLDIRECTIONMAP_HPP_

//custom includes
#include "e_fl_direction.hpp"

#include "../math/math.hpp"

//global includes
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>


namespace mae
{
	namespace fl
	{

		class fl_direction_map
		{
			public:
				/**
				 * Creates a new map for fl directions to vec3ds.
				 */
				fl_direction_map();
				virtual ~fl_direction_map();

				/**
				 * Returns the normalized vector for the given direction.
				 *
				 * @param fldirection The direction.
				 */
				virtual std::shared_ptr<mae::math::vec3d> get_vec(e_fl_direction fldirection) const;

				/**
				 * Returns the normalized vector for the given direction.
				 *
				 * @param fldirection The direction.
				 */
				virtual std::shared_ptr<mae::math::vec3d> get_vec(laban::mv::e_direction direction, laban::mv::e_level level) const;

			private:
				std::unordered_map<int, std::shared_ptr<mae::math::vec3d> > map_directions_;

		};

	} // namespace fl
} // namespace mae

#endif // MAE_FL_FLDIRECTIONMAP_HPP_
