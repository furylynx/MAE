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

			virtual void setKeyPose(int bodyPart, bool isKeyPose);
			virtual bool isKeyPose(int bodyPart);

			virtual void setInMotion(int bodyPart, bool isInMotion);
			virtual bool isInMotion(int bodyPart);

		private:
			std::unordered_map<int, bool> hashmap_keypose;
			std::unordered_map<int, bool> hashmap_inmotion;

	};

} //namespace mae

#endif // GENERALENRICHEDPOSE_HPP_
