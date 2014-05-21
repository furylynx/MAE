/*
 * GeneralSkeleton.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef GENERALSKELETON_HPP_
#define GENERALSKELETON_HPP_

#include "GeneralJoint.hpp"

#include <unordered_map>

namespace mae {
	namespace model {

		class GeneralSkeleton {
			public:
				virtual ~GeneralSkeleton();
				GeneralSkeleton();


				virtual void setJoint(int bodyPart, mae::model::GeneralJoint joint);
				virtual mae::model::GeneralJoint getJoint(int bodyPart);



			    static const int SKEL_HEAD = 1;
			    static const int SKEL_NECK = 2;
			    static const int SKEL_LEFT_SHOULDER = 3;
			    static const int SKEL_LEFT_ELBOW = 4;
			    static const int SKEL_LEFT_HAND = 5;
			    static const int SKEL_RIGHT_SHOULDER = 6;
			    static const int SKEL_RIGHT_ELBOW = 7;
			    static const int SKEL_RIGHT_HAND = 8;
			    static const int SKEL_TORSO = 9;
			    static const int SKEL_LEFT_HIP = 10;
			    static const int SKEL_LEFT_KNEE = 11;
			    static const int SKEL_LEFT_FOOT = 12;
			    static const int SKEL_RIGHT_HIP = 13;
			    static const int SKEL_RIGHT_KNEE = 14;
			    static const int SKEL_RIGHT_FOOT = 15;




			private:
			    std::unordered_map<int, mae::model::GeneralJoint> hashmap_joints;
		};

	} // namespace model
} // namespace mae

#endif // GENERALSKELETON_HPP_
