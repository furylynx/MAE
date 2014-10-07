/*
 * GeneralEnrichedPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALENRICHEDPOSE_HPP_
#define GENERALENRICHEDPOSE_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_pose.hpp"

//global includes
#include <memory>
#include <unordered_map>
#include <stdexcept>

namespace mae
{

	class general_enriched_pose: public general_pose
	{
		public:
			/**
			 * Creates an enriched pose.
			 */
			general_enriched_pose();

			/**
			 * Creates an enriched pose from the general pose.
			 *
			 * @param pose The general pose.
			 */
			general_enriched_pose(std::shared_ptr<general_pose> pose);

			virtual ~general_enriched_pose();

			/**
			 * Sets this pose as a key pose for the given body part.
			 *
			 * @param bodyPart The addressed body part.
			 * @param isKeyPose The value for the key pose
			 */
			virtual void set_key_pose(int body_part, bool is_key_pose);

			/**
			 * Returns true if this pose is a key pose for the given body part.
			 *
			 * @param body_part The addressed body part.
			 * @return True if key pose.
			 */
			virtual bool is_key_pose(int body_part);

			/**
			 * Sets the motion value for the given body part.
			 *
			 * @param body_part The addressed body part.
			 * @param is_in_motion The value for the motion.
			 */
			virtual void set_in_motion(int body_part, bool is_in_motion);

			/**
			 * Returns true if this pose is the start of a new motion sequence on the body part..
			 *
			 * @param body_part The addressed body part.
			 * @return True if motion begin.
			 */
			virtual bool is_in_motion(int body_part);

		private:
			std::unordered_map<int, bool> hashmap_keypose_;
			std::unordered_map<int, bool> hashmap_inmotion_;

	};

} //namespace mae

#endif // GENERALENRICHEDPOSE_HPP_
