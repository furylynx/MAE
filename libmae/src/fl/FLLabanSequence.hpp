/*
 * FLLabanSequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCE_HPP_
#define FLLABANSEQUENCE_HPP_

//custom includes
#include "FLLabanSubsequence.hpp"

//global includes
#include <memory>

namespace mae {
	namespace fl {

		class FLLabanSequence {
			public:
				FLLabanSequence();
				virtual ~FLLabanSequence();


				virtual std::shared_ptr<mae::fl::FLLabanSubsequence> getSubsequence(int bodyPart);
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
