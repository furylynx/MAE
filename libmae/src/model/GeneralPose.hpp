/*
 * GeneralPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALPOSE_HPP_
#define GENERALPOSE_HPP_

#include <unordered_map>

namespace mae {
	namespace model {

		class GeneralPose {
			public:
				virtual ~GeneralPose();

				virtual int getDirection(int bodyPart);
				virtual double getDistance(int bodyPart, int direction);

			private:
				std::unordered_map<int, int> hashmap;

		};

	} /* namespace model */
} /* namespace mae */

#endif /* GENERALPOSE_HPP_ */
