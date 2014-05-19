/*
 * FLLabanSequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCE_HPP_
#define FLLABANSEQUENCE_HPP_

namespace mae {
	namespace fl {

		class FLLabanSequence {
			public:
				virtual ~FLLabanSequence();

				//TODO return subsequence
				virtual void getSubsequence(int bodyPart);
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
