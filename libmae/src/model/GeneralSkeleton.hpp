/*
 * GeneralSkeleton.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef GENERALSKELETON_HPP_
#define GENERALSKELETON_HPP_

//custom includes
#include "GeneralJoint.hpp"

//global includes
#include <unordered_map>
#include <memory>

namespace mae {
	namespace model {

		class GeneralSkeleton {
			public:
				virtual ~GeneralSkeleton();
				GeneralSkeleton();


				virtual void setJoint(int bodyPart, std::shared_ptr<mae::model::GeneralJoint> joint);
				virtual std::shared_ptr<mae::model::GeneralJoint> getJoint(int bodyPart);


			    static const int SKEL_HEAD;
			    static const int SKEL_NECK;
			    static const int SKEL_LEFT_SHOULDER;
			    static const int SKEL_LEFT_ELBOW;
			    static const int SKEL_LEFT_HAND;
			    static const int SKEL_RIGHT_SHOULDER;
			    static const int SKEL_RIGHT_ELBOW;
			    static const int SKEL_RIGHT_HAND;
			    static const int SKEL_TORSO;
			    static const int SKEL_LEFT_HIP;
			    static const int SKEL_LEFT_KNEE;
			    static const int SKEL_LEFT_FOOT;
			    static const int SKEL_RIGHT_HIP;
			    static const int SKEL_RIGHT_KNEE;
			    static const int SKEL_RIGHT_FOOT;


			private:
			    std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> > hashmap_joints;
		};

	} // namespace model
} // namespace mae

#endif // GENERALSKELETON_HPP_
