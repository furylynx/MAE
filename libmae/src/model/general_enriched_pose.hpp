/*
 * GeneralEnrichedPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALENRICHEDPOSE_HPP_
#define GENERALENRICHEDPOSE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "general_pose.hpp"

//global includes
#include <memory>
#include <unordered_map>

namespace mae
{

	class general_enriched_pose: public general_pose
	{
		public:
			general_enriched_pose();
			general_enriched_pose(std::shared_ptr<general_pose> pose);
			general_enriched_pose(std::unordered_map<int, bool> hashmap_keypose,
					std::unordered_map<int, bool> hashmap_inmotion);
			virtual ~general_enriched_pose();

			virtual void set_key_pose(int bodyPart, bool isKeyPose);
			virtual bool is_key_pose(int bodyPart);

			virtual void set_in_motion(int bodyPart, bool isInMotion);
			virtual bool is_in_motion(int bodyPart);

		private:
			std::unordered_map<int, bool> hashmap_keypose_;
			std::unordered_map<int, bool> hashmap_inmotion_;

	};

} //namespace mae

#endif // GENERALENRICHEDPOSE_HPP_
