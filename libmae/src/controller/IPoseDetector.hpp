/*
 * IPoseDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IPOSEDETECTOR_HPP_
#define IPOSEDETECTOR_HPP_

#include "GeneralPose.hpp"

namespace mae {
	namespace controller {

		template <class T>
		class IPoseDetector {
			public:
				virtual ~IPoseDetector();

				virtual mae::model::GeneralPose detectPose(T skeleton, int bodyParts[], int bodyPartsSize) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // IPOSEDETECTOR_HPP_
