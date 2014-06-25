/*
 * GeneralKeyPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef GENERALKEYPOSEDETECTOR_HPP_
#define GENERALKEYPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_kp_detector.hpp"

#include "../model/bone.hpp"

//global includes
#include <iostream>
#include <list>
#include <memory>

namespace mae
{

	class kp_detector: public i_kp_detector
	{
		public:
			kp_detector();
			virtual ~kp_detector();

			virtual std::shared_ptr<general_enriched_pose> estimate_frame(std::shared_ptr<general_pose> current_pose,
					std::list<std::shared_ptr<general_enriched_pose> > previous_sequence, std::vector<bone> body_parts);

		private:
			const unsigned int RANGE_KP = 5; //10 ??
	};

} // namespace mae

#endif // GENERALKEYPOSEDETECTOR_HPP_
