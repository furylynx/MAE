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

				//direction quantization
				static const int PLACE_HIGH;
				static const int PLACE_MID;
				static const int PLACE_LOW;

				static const int LEFT_HIGH;
				static const int LEFT_MID;
				static const int LEFT_LOW;

				static const int DIAGONAL_FORWARD_LEFT_HIGH;
				static const int DIAGONAL_FORWARD_LEFT_MID;
				static const int DIAGONAL_FORWARD_LEFT_LOW;

				static const int FORWARD_LEFT_HIGH;
				static const int FORWARD_LEFT_MID;
				static const int FORWARD_LEFT_LOW;

				static const int FORWARD_RIGHT_HIGH;
				static const int FORWARD_RIGHT_MID;
				static const int FORWARD_RIGHT_LOW;

				static const int DIAGONAL_FORWARD_RIGHT_HIGH;
				static const int DIAGONAL_FORWARD_RIGHT_MID;
				static const int DIAGONAL_FORWARD_RIGHT_LOW;

				static const int RIGHT_HIGH;
				static const int RIGHT_MID;
				static const int RIGHT_LOW;

				static const int DIAGONAL_BACK_RIGHT_HIGH;
				static const int DIAGONAL_BACK_RIGHT_MID;
				static const int DIAGONAL_BACK_RIGHT_LOW;

				static const int BACK_RIGHT_HIGH;
				static const int BACK_RIGHT_MID;
				static const int BACK_RIGHT_LOW;

				static const int BACK_LEFT_HIGH;
				static const int BACK_LEFT_MID;
				static const int BACK_LEFT_LOW;

				static const int DIAGONAL_BACK_LEFT_HIGH;
				static const int DIAGONAL_BACK_LEFT_MID;
				static const int DIAGONAL_BACK_LEFT_LOW;

		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
