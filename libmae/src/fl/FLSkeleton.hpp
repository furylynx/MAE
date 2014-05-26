/*
 * FLSkeleton.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLSKELETON_HPP_
#define FLSKELETON_HPP_

//custom includes
#include "FLJoint.hpp"
#include "../model/GeneralSkeleton.hpp"


//global includes
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace mae {
	namespace fl {

		class FLSkeleton {
			public:
				FLSkeleton();
				virtual ~FLSkeleton();

				//todo joints are angular - but central coordinate system necessary?

				//angular joint
				virtual void setJoint(int bodyPart, std::shared_ptr<mae::fl::FLJoint> joint);
				virtual std::shared_ptr<mae::fl::FLJoint> getJoint(int bodyPart);

				//get central coordinate system
				virtual void setCoordSys(std::vector<double> u, std::vector<double> r, std::vector<double> t);
				virtual std::vector<std::vector<double> > getCoordSys();

				//todo get vectors by themselves


				// Torso joint is center of coordinate system; therefore torso joint has coordinates (0,0,0).
				// Stored torso joint is therefore used for the offset of the world coordinate system given
				// by the depth sensor. The central coordinate system of this FLSkeleton is used for the
				// representation by translating it into the torso joint.
				virtual void setRelativeSkeleton(std::shared_ptr<mae::model::GeneralSkeleton> relative_skeleton);
				virtual std::shared_ptr<mae::model::GeneralSkeleton> getRelativeSkeleton();



				//angle representations
				static const int ANGLE_HEAD ;
				static const int ANGLE_LEFT_UPPER_ARM ;
				static const int ANGLE_LEFT_FOREARM ;
				static const int ANGLE_LEFT_WHOLE_ARM;
				static const int ANGLE_RIGHT_UPPER_ARM ;
				static const int ANGLE_RIGHT_FOREARM ;
				static const int ANGLE_RIGHT_WHOLE_ARM ;
				static const int ANGLE_LEFT_THIGH; //Oberschenkel
				static const int ANGLE_LEFT_SHANK ; //Unterschenkel
				static const int ANGLE_LEFT_WHOLE_LEG ;
				static const int ANGLE_RIGHT_THIGH ; //Oberschenkel
				static const int ANGLE_RIGHT_SHANK ; //Unterschenkel
				static const int ANGLE_RIGHT_WHOLE_LEG ;

//				static const int ANGLE_HEAD = 16;
//				static const int ANGLE_LEFT_UPPER_ARM = 17;
//				static const int ANGLE_LEFT_FOREARM = 18;
//				static const int ANGLE_LEFT_WHOLE_ARM = 19;
//				static const int ANGLE_RIGHT_UPPER_ARM = 20;
//				static const int ANGLE_RIGHT_FOREARM = 21;
//				static const int ANGLE_RIGHT_WHOLE_ARM = 22;
//				static const int ANGLE_LEFT_THIGH = 23; //Oberschenkel
//				static const int ANGLE_LEFT_SHANK = 24; //Unterschenkel
//				static const int ANGLE_LEFT_WHOLE_LEG = 25;
//				static const int ANGLE_RIGHT_THIGH = 26; //Oberschenkel
//				static const int ANGLE_RIGHT_SHANK = 27; //Unterschenkel
//				static const int ANGLE_RIGHT_WHOLE_LEG = 28;

			private:
			    std::unordered_map<int, std::shared_ptr<mae::fl::FLJoint> > hashmap_joints;
			    std::shared_ptr<mae::model::GeneralSkeleton> relative_skeleton;

			    //central coordinate system
			    std::vector<double> u;
			    std::vector<double> r;
			    std::vector<double> t;
		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
