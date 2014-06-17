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
#include "GeneralPose.hpp"

//global includes
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
