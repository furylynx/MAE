/*
 * GeneralEnrichedPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALENRICHEDPOSE_HPP_
#define GENERALENRICHEDPOSE_HPP_

#include "GeneralPose.hpp"

#include <unordered_map>

namespace mae {
	namespace model {

		class GeneralEnrichedPose: public GeneralPose
		{
			public:
				GeneralEnrichedPose();
				GeneralEnrichedPose(std::unordered_map<int, bool> hashmap_keypose, std::unordered_map<int, bool> hashmap_inmotion);
				virtual ~GeneralEnrichedPose();

				virtual void setKeyPose(int bodyPart, bool isKeyPose);
				virtual bool isKeyPose(int bodyPart);


				virtual void setInMotion(int bodyPart, bool isInMotion);
				virtual bool isInMotion(int bodyPart);

			private:
				std::unordered_map<int, bool> hashmap_keypose;
				std::unordered_map<int, bool> hashmap_inmotion;

		};

	} // namespace model
} //namespace mae

#endif // GENERALENRICHEDPOSE_HPP_
