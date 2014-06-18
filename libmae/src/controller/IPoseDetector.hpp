/*
 * IPoseDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IPOSEDETECTOR_HPP_
#define IPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/general_pose.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae {
	namespace controller {

		template <typename T>
		class IPoseDetector {
			public:
				virtual ~IPoseDetector(){}

				virtual std::shared_ptr<general_pose> pose(std::shared_ptr<T> skeleton, std::vector<int> body_parts) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // IPOSEDETECTOR_HPP_
