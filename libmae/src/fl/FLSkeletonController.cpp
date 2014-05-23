/*
 * FLSkeletonController.cpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#include "FLSkeletonController.hpp"

namespace mae {
	namespace fl {

		FLSkeletonController::~FLSkeletonController() {
			// TODO Auto-generated destructor stub
		}

		FLSkeletonController::FLSkeletonController() {
			// TODO Auto-generated constructor stub

		}

		std::shared_ptr<mae::fl::FLSkeleton> FLSkeletonController::calculateSpecifiedSkeleton(std::shared_ptr<mae::model::GeneralSkeleton> skeleton){

			// ---
			// calculate the torso frame
			// ---

			//todo probably other approach (shoulders+torso = coord for arms; hips+torso = coord for legs)

			// fill all joints of torso into matrix in order to
			// reduce it to three vectors that are used for the coordinate system
			cv::Mat torso = cv::Mat(3,7,CV_64F);
			//todo fill torso
			std::vector<int> bodyParts = std::vector<int>();

			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_SHOULDER);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_NECK);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_TORSO);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HIP);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HIP);

			for(unsigned int i = 0; i < bodyParts.size(); i++) {
				std::shared_ptr<mae::model::GeneralJoint> joint = skeleton->getJoint(i);

				torso.at<double>(0,i) = joint->getX();
				torso.at<double>(1,i) = joint->getY();
				torso.at<double>(2,i) = joint->getZ();
			}


			// apply PCA to get 3 principal components
			cv::Mat torso_coord;
			cv::PCA torso_pca = cv::PCA(torso, cv::Mat(), CV_PCA_DATA_AS_ROW, 2);
			torso_pca.project(torso, torso_coord);

			// create basis {u,r,t}
			cv::Vec3d u = torso_coord.col(0);
			//todo align first vector (u) in top-down (pointing to the ground)
			//todo other approach : align to head

			cv::Vec3d r = torso_coord.col(1);
			//left-right align
			//todo other approach: align to left shoulder

			cv::Vec3d t = u.cross(r);

			//normalize
			u = cv::normalize(u);
			r = cv::normalize(r);
			t = cv::normalize(t);




			// ---
			// Calculate spherical coordinates
			// for the resulting skeleton
			// ---

			std::shared_ptr<mae::fl::FLSkeleton> result = std::shared_ptr<mae::fl::FLSkeleton>(new mae::fl::FLSkeleton());


			//fill vector with body parts in order to process them later
			std::vector<std::vector<int> > extremities = std::vector<std::vector<int> >();
			std::vector<int> joints = std::vector<int>();

			//left arm
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_ELBOW);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HAND);

			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_UPPER_ARM);
			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_FOREARM);

			extremities.push_back(joints);
			joints.clear();

			//right arm
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_SHOULDER);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_ELBOW);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HAND);

			joints.push_back(mae::fl::FLSkeleton::ANGLE_RIGHT_UPPER_ARM);
			joints.push_back(mae::fl::FLSkeleton::ANGLE_RIGHT_FOREARM);

			extremities.push_back(joints);
			joints.clear();

			//left leg
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HIP);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_KNEE);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_FOOT);

			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_THIGH);
			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_SHANK);//unterschenkel

			extremities.push_back(joints);
			joints.clear();


			//left leg
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HIP);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_KNEE);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_FOOT);

			joints.push_back(mae::fl::FLSkeleton::ANGLE_RIGHT_THIGH);
			joints.push_back(mae::fl::FLSkeleton::ANGLE_RIGHT_SHANK);//unterschenkel

			extremities.push_back(joints);
			joints.clear();

			for (unsigned int i = 0; extremities.size(); i++){
				joints = extremities[i];
				int joint_i = joints[0];
				int joint_o = joints[1];
				int joint_e = joints[2];

				int joint_fl_i = joints[3];
				int joint_fl_o = joints[5];

				cv::Vec2d angles = FLSkeletonController::calcFirstDegreeJoint(skeleton, joint_i, joint_o, r, t, u);
				std::shared_ptr<mae::fl::FLJoint> joint = std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint());
				joint->setTheta(angles[0]);
				joint->setPhi(angles[1]);
				result->setJoint(joint_fl_i, joint);

				angles = FLSkeletonController::calcSecondDegreeJoint(skeleton, joint_i, joint_o, joint_e, r, t, u);
				joint = std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint());
				joint->setTheta(angles[0]);
				joint->setPhi(angles[1]);
				result->setJoint(joint_fl_o, joint);
			}



			//spherical coordinates for the head
			int joint_i = mae::model::GeneralSkeleton::SKEL_NECK;
			int joint_o = mae::model::GeneralSkeleton::SKEL_HEAD;

			int joint_fl_i = mae::fl::FLSkeleton::ANGLE_HEAD;

			cv::Vec2d angles = FLSkeletonController::calcFirstDegreeJoint(skeleton, joint_i, joint_o, r, t, u);
			std::shared_ptr<mae::fl::FLJoint> joint = std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint());
			joint->setTheta(angles[0]);
			joint->setPhi(angles[1]);
			result->setJoint(joint_fl_i, joint);


			//todo calculate relative skeleton

			//todo set coordinate system

			return result;
		}

		cv::Vec2d calcFirstDegreeJoint(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t){
			// ---
			// calculate angles for first degree joints
			// ---


			std::shared_ptr<mae::model::GeneralJoint> joint_i = skeleton->getJoint(adjacent_joint);
			std::shared_ptr<mae::model::GeneralJoint> joint_o = skeleton->getJoint(outer_joint);

			cv::Vec3d vec_i;
			vec_i[0] = joint_i->getX();
			vec_i[1] = joint_i->getY();
			vec_i[2] = joint_i->getZ();

			cv::Vec3d vec_o;
			vec_o[0] = joint_o->getX();
			vec_o[1] = joint_o->getY();
			vec_o[2] = joint_o->getZ();

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double theta = std::acos(u.dot(fdvec));
			// ...to degree
			theta *= 180 / M_PI;


			//get azimuth phi
			cv::Vec3d vec_o_p = FLSkeletonController::projectOrthogonal(vec_o, vec_i, r, t);
			cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

			// calculates phi in radian
			double phi = std::acos(r.dot(fdvec_p));

			// ...to degree
			phi *= 180 / M_PI;

			cv::Vec2d angles;
			angles[0] = theta;
			angles[1] = phi;

			return angles;

		}

		cv::Vec2d calcSecondDegreeJoint(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t){

			// ---
			// calculate angles for second degree joints
			// ---

			std::shared_ptr<mae::model::GeneralJoint> joint_i = skeleton->getJoint(adjacent_joint);
			std::shared_ptr<mae::model::GeneralJoint> joint_o = skeleton->getJoint(outer_joint);
			std::shared_ptr<mae::model::GeneralJoint> joint_lh = skeleton->getJoint(extremity_joint);


			cv::Vec3d vec_i;
			vec_i[0] = joint_i->getX();
			vec_i[1] = joint_i->getY();
			vec_i[2] = joint_i->getZ();

			cv::Vec3d vec_o;
			vec_o[0] = joint_o->getX();
			vec_o[1] = joint_o->getY();
			vec_o[2] = joint_o->getZ();

			cv::Vec3d vec_e;
			vec_e[0] = joint_lh->getX();
			vec_e[1] = joint_lh->getY();
			vec_e[2] = joint_lh->getZ();

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// get second degree bone vector
			cv::Vec3d sdvec = cv::normalize(vec_e- vec_o);

			// calc inclination theta
			// angle between fdvec and sdvec which is the angle between r_r and sdvec
			double theta = std::acos(fdvec.dot(sdvec));

			// ...to degree
			theta *= 180 / M_PI;

			// calc azimuth phi
			double phi;

			if (FLSkeletonController::areCollinear(fdvec, sdvec)){
				// both joint vectors fdvec and sdvec are collinear
				// therefore we can set phi to zero
				phi = 0;
			}else{


				//rotate around axis b = v x r ...
				cv::Vec3d b = cv::normalize(fdvec.cross(r));

				// ... by rotation angle beta
				double beta = std::acos(fdvec.dot(r));

				//apply to all
				cv::Vec3d u_r = FLSkeletonController::rotateAroundAxis(u, b, beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				//cv::Vec3d r_r = FLSkeletonController::rotateAroundAxis(r, b, beta);
				cv::Vec3d t_r = FLSkeletonController::rotateAroundAxis(t, b, beta);

				//plane othogonal to v is E(u,t)
				cv::Vec3d sdvec_p = FLSkeletonController::projectOrthogonal(sdvec, vec_o, u_r, t_r);
				sdvec_p = cv::normalize(vec_o - sdvec_p);
				phi = std::acos(t_r.dot(sdvec_p));
			}

			// ...to degree
			phi *= 180 / M_PI;


			//return the angles
			cv::Vec2d angles;
			angles[0] = theta;
			angles[1] = phi;

			return angles;

		}

		cv::Vec3d FLSkeletonController::projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u, cv::Vec3d plane_v){

			//point to be projected
			cv::Mat p = cv::Mat(4, 1, CV_64F);
			p.at<double>(0) = point[0];
			p.at<double>(1) = point[1];
			p.at<double>(2) = point[2];
			p.at<double>(3) = 1;


			plane_u = cv::normalize(plane_u);
			plane_v = cv::normalize(plane_v);

			//calc surface normal
			cv::Vec3d normal = cv::normalize(plane_u.cross(plane_v));

			//coordinate transform matrix
			cv::Mat m = cv::Mat(4, 4, CV_64F);
			for (int i = 0; i<3 ; i++){
				m.at<double>(i,0) = plane_u[i];
			}
			m.at<double>(3,0) = 0;

			for (int i = 0; i<3 ; i++){
				m.at<double>(i,1) = plane_v[i];
			}
			m.at<double>(3,1) = 0;

			for (int i = 0; i<3 ; i++){
				m.at<double>(i,2) = normal[i];
			}
			m.at<double>(3,2) = 0;

			for (int i = 0; i<3 ; i++){
				m.at<double>(i,3) = position_vector[i];
			}
			m.at<double>(3,3) = 1;

			//reduce matrix
			cv::Mat x = cv::Mat::eye(4,4, CV_64F);
			x.at<double>(2,2) = 0;

			//calc result
			cv::Mat result = m*x*m.inv()*p;

			return result.rowRange(0,3);
		}

		cv::Vec3d FLSkeletonController::rotateAroundAxis(cv::Vec3d point, cv::Vec3d axis, double beta){

			//point to be projected
			cv::Mat p = cv::Mat::zeros(3,1,CV_64F);
			p.at<double>(0) = point[0];
			p.at<double>(1) = point[1];
			p.at<double>(2) = point[2];

			//set up basis from axis
			axis = cv::normalize(axis);
			cv::Vec3d x;
			x[0] = 1;

			if (FLSkeletonController::areCollinear(axis, x)){
				x[0] = 0;
				x[1] = 1;
			}


			cv::Vec3d axis_o1 = cv::normalize(axis.cross(x));
			cv::Vec3d axis_o2 = cv::normalize(axis.cross(axis_o1));

			//coordinate transform matrix
			cv::Mat m = cv::Mat::zeros(3,3,CV_64F);
			for (int i = 0; i<3 ; i++){
				m.at<double>(i,0) = axis[i];
			}

			for (int i = 0; i<3 ; i++){
				m.at<double>(i,1) = axis_o1[i];
			}

			for (int i = 0; i<3 ; i++){
				m.at<double>(i,2) = axis_o2[i];
			}


			//rotation matrix
			double cos_beta = std::cos(beta);
			double sin_beta = std::sin(beta);

			cv::Mat r_x = cv::Mat::zeros(3,3,CV_64F);
			r_x.at<double>(0,0) = cos_beta;
			r_x.at<double>(0,1) = -sin_beta;
			r_x.at<double>(1,0) = sin_beta;
			r_x.at<double>(1,1) = cos_beta;

			cv::Mat result = m*r_x*m.inv()*p;
			return result.rowRange(0,3);
		}

		bool FLSkeletonController::areCollinear(cv::Vec3d a, cv::Vec3d b){

			// collinear if a = beta * b;


			double beta;

			for (int i = 0; i< 3; i++){
				if (b[i] != 0){
					beta = a[i]/b[i];

					if (beta == 0){
						return false;
					}

					return a[1] == beta*b[1] && a[2] == beta*b[2] && a[3] == beta*b[3];
				}else{
					if (a[i] != 0){
						return false;
					}
				}
			}

			return false;
		}

	} // namespace fl
} // namespace mae
