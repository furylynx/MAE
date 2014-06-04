/*
 * FLLabanSequence.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "FLLabanSequence.hpp"

namespace mae {
	namespace fl {

		FLLabanSequence::FLLabanSequence() {
			// TODO Auto-generated destructor stub
		}

		FLLabanSequence::~FLLabanSequence() {
			// TODO Auto-generated destructor stub
		}

		std::shared_ptr<mae::fl::FLLabanSubsequence> FLLabanSequence::getSubsequence(int bodyPart){

			std::shared_ptr<mae::fl::FLLabanSubsequence> subsequence;// = std::shared_ptr<mae::fl::FLLabanSubsequence>(new mae::fl::FLLabanSubsequence());

			//todo do stuff in here

			return subsequence;

		}



//		//directions and levels
//		const int FLLabanSequence::PLACE_HIGH = 1;
//		const int FLLabanSequence::PLACE_MID = 2;
//		const int FLLabanSequence::PLACE_LOW = 3;
//
//		const int FLLabanSequence::LEFT_HIGH = 4;
//		const int FLLabanSequence::LEFT_MID = 5;
//		const int FLLabanSequence::LEFT_LOW = 6;
//
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_HIGH = 7;
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_MID = 8;
//		const int FLLabanSequence::DIAGONAL_FORWARD_LEFT_LOW = 9;
//
//		const int FLLabanSequence::FORWARD_LEFT_HIGH = 10;
//		const int FLLabanSequence::FORWARD_LEFT_MID = 11;
//		const int FLLabanSequence::FORWARD_LEFT_LOW = 12;
//
//		const int FLLabanSequence::FORWARD_RIGHT_HIGH = 13;
//		const int FLLabanSequence::FORWARD_RIGHT_MID = 14;
//		const int FLLabanSequence::FORWARD_RIGHT_LOW = 15;
//
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_HIGH = 16;
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_MID = 17;
//		const int FLLabanSequence::DIAGONAL_FORWARD_RIGHT_LOW = 18;
//
//		const int FLLabanSequence::RIGHT_HIGH = 19;
//		const int FLLabanSequence::RIGHT_MID = 20;
//		const int FLLabanSequence::RIGHT_LOW = 21;
//
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_HIGH = 22;
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_MID = 23;
//		const int FLLabanSequence::DIAGONAL_BACK_RIGHT_LOW = 24;
//
//		const int FLLabanSequence::BACK_RIGHT_HIGH = 25;
//		const int FLLabanSequence::BACK_RIGHT_MID = 26;
//		const int FLLabanSequence::BACK_RIGHT_LOW = 27;
//
//		const int FLLabanSequence::BACK_LEFT_HIGH = 28;
//		const int FLLabanSequence::BACK_LEFT_MID = 29;
//		const int FLLabanSequence::BACK_LEFT_LOW = 30;
//
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_HIGH = 31;
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_MID = 32;
//		const int FLLabanSequence::DIAGONAL_BACK_LEFT_LOW = 33;

	} // namespace fl
} // namespace mae
