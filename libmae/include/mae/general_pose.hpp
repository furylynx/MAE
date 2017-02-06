/*
 * GeneralPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALPOSE_HPP_
#define GENERALPOSE_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#include <unordered_map>
#include <iostream>
#include <list>
#include <stdexcept>

namespace mae
{

	class general_pose
	{
		public:

			/**
			 * Creates a new empty pose.
			 */
			general_pose();

			virtual ~general_pose();

			/**
			 * Sets the direction for the given body part. The direction should not be zero unless
			 * the direction of the body part is meant to be invalidated.
			 *
			 * See fl/fld.hpp for laban direction codes used by the fl_movement_controller.
			 *
			 * @param body_part The id of the body part (e.g. for the left forearm).
			 * @param direction The direction code.
			 */
			virtual void set_direction(int body_part, int direction);

			/**
			 * Returns the direction assigned to the body part with the id. If the body part is
			 * not listed in this pose zero will be returned indicating an invalid direction.
			 *
			 * See fl/fld.hpp for laban direction codes used by the fl_movement_controller.
			 *
			 * @param body_part The id of the body part (e.g. for the left forearm).
			 * @return The direction code.
			 */
			virtual int get_direction(int body_part) const;

			/**
			 * Sets the distance of a body part to a certain direction. These distances can be used
			 * to identify the beginning of a motion from one direction to another. The distance should
			 * be positive since -1 is used to indicate invalid distances.
			 *
			 * See fl/fld.hpp for laban direction codes used by the fl_movement_controller.
			 *
			 * @param body_part The id of the body part (e.g. for the left forearm).
			 * @param direction The direction code.
			 * @param distance The distance.
			 */
			virtual void set_distance(int body_part, int direction, double distance);

			/**
			 * Returns the distance of the actual pose to the requested direction for the specific
			 * body part. Returns -1 if the distance is invalid.
			 *
			 * See fl/fld.hpp for laban direction codes used by the fl_movement_controller.
			 *
			 * @param body_part The id of the body part (e.g. for the left forearm).
			 * @param direction The direction code.
			 * @return The distance.
			 */
			virtual double get_distance(int body_part, int direction) const;

			/**
			 * Sets the rotation of the body part in the specific pose.
			 *
			 * @param body_part The body part.
			 * @param rotation The rotation.
			 */
			virtual void set_rotation(int body_part, double rotation);

			/**
			 * Returns the rotation of the body part in the specific pose.
			 *
			 * @param body_part The body part.
			 * @return The rotation.
			 */
			virtual double get_rotation(int body_part) const;

			/**
			 * Returns all body parts that have a direction assigned to it.
			 *
			 * @return All used body parts in this pose.
			 */
			virtual std::list<int> get_body_parts() const;

			/**
			 * Returns all directions that have a distance assigned.
			 *
			 * @return All directions.
			 */
			virtual std::list<int> get_directions() const;

		private:
			std::unordered_map<int, int> hashmap_direction_;
			std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance_;

			std::unordered_map<int, double> hashmap_rotation_;

			std::list<int> body_parts_;

			std::unordered_map<int, int> hashmap_directions_;
			std::list<int> directions_;

	};

} // namespace mae

#endif // GENERALPOSE_HPP_
