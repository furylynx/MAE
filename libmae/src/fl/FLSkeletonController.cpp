/*
 * FLSkeletonController.cpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#include "FLSkeletonController.hpp"


//using mae::controller::ISkeletonController<mae::fl::FLSkeleton>::~ISkeletonController;

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
			cv::Mat torso = cv::Mat::zeros(3,6,CV_64F);

			std::vector<int> bodyParts;
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_SHOULDER);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_NECK);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_TORSO);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HIP);
			bodyParts.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HIP);

			for(unsigned int i = 0; i < bodyParts.size(); i++) {
				int bodyPart = bodyParts[i];
				std::shared_ptr<mae::model::GeneralJoint> joint = skeleton->getJoint(bodyPart);

				//todo if one of the vectors is invalid -> remove from matrix
				//todo if less than 3 vectors -> invalid skeleton

				torso.at<double>(0,i) = joint->getX();
				torso.at<double>(1,i) = joint->getY();
				torso.at<double>(2,i) = joint->getZ();
			}


			// apply PCA to get 3 principal components
			cv::Mat torso_coord;
			cv::PCA torso_pca = cv::PCA(torso, cv::Mat(), CV_PCA_DATA_AS_COL, 2);

			// create basis {u,r,t}
			cv::Vec3d u = torso_pca.eigenvectors.row(0).clone();
			cv::Vec3d r = torso_pca.eigenvectors.row(1).clone();
			cv::Vec3d t = u.cross(r);

			//normalize
			u = cv::normalize(u);
			r = cv::normalize(r);
			t = cv::normalize(t);


			//align vectors top-down/right-left
			cv::Vec3d joint_torso = FLMath::jointToVec(skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_TORSO));
			cv::Vec3d joint_neck = FLMath::jointToVec(skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_NECK));

			cv::Vec3d joint_ls = FLMath::jointToVec(skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER));
			cv::Vec3d joint_rs = FLMath::jointToVec(skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_RIGHT_SHOULDER));

			if (cv::norm(joint_neck - (joint_torso+u)) < cv::norm(joint_neck - joint_torso) )
			{
				u = -u;
			}

			if (cv::norm(joint_ls - (joint_rs+r)) > cv::norm(joint_ls - joint_rs) )
			{
				r = -r;
			}

			// ---
			// Calculate spherical coordinates
			// for the resulting skeleton
			// ---

			std::shared_ptr<FLSkeleton> result = std::shared_ptr<mae::fl::FLSkeleton>(new FLSkeleton());



			//fill vector with body parts in order to process them later
			std::vector<cv::Vec3d> md;

			std::vector<std::vector<int> > extremities;
			std::vector<int> joints;

			//left arm
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_ELBOW);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HAND);

			joints.push_back(FLSkeleton::ANGLE_LEFT_UPPER_ARM);
			joints.push_back(FLSkeleton::ANGLE_LEFT_FOREARM);
			joints.push_back(FLSkeleton::ANGLE_LEFT_WHOLE_ARM);

			extremities.push_back(joints);
			md.push_back(r);
			joints.clear();

			//right arm
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_SHOULDER);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_ELBOW);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HAND);

			joints.push_back(FLSkeleton::ANGLE_RIGHT_UPPER_ARM);
			joints.push_back(FLSkeleton::ANGLE_RIGHT_FOREARM);
			joints.push_back(FLSkeleton::ANGLE_RIGHT_WHOLE_ARM);

			extremities.push_back(joints);
			md.push_back(-r);
			joints.clear();

			//left leg
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_HIP);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_KNEE);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_LEFT_FOOT);

			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_THIGH);
			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_SHANK);//unterschenkel
			joints.push_back(mae::fl::FLSkeleton::ANGLE_LEFT_WHOLE_LEG);

			extremities.push_back(joints);
			md.push_back(u);
			joints.clear();


			//left leg
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_HIP);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_KNEE);
			joints.push_back(mae::model::GeneralSkeleton::SKEL_RIGHT_FOOT);

			joints.push_back(FLSkeleton::ANGLE_RIGHT_THIGH);
			joints.push_back(FLSkeleton::ANGLE_RIGHT_SHANK);//unterschenkel
			joints.push_back(FLSkeleton::ANGLE_RIGHT_WHOLE_LEG);

			extremities.push_back(joints);
			md.push_back(u);
			joints.clear();

			for (unsigned int i = 0; i < extremities.size(); i++){
				joints = extremities[i];
				int joint_i = joints[0];
				int joint_o = joints[1];
				int joint_e = joints[2];

				int joint_fl_i = joints[3];
				int joint_fl_o = joints[4];
				int joint_fl_w = joints[5];

				cv::Vec2d angles;

				angles = FLSkeletonController::calcFirstDegreeJoint_md(skeleton, joint_i, joint_o, u, r, t, (cv::Vec3d) md[i]);
				//angles = FLSkeletonController::calcFirstDegreeJoint(skeleton, joint_i, joint_o, u, r, t);
				result->setJoint(joint_fl_i, std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint(angles[0], angles[1])));

				angles = FLSkeletonController::calcSecondDegreeJoint(skeleton, joint_i, joint_o, joint_e, u, r, t);
				result->setJoint(joint_fl_o, std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint(angles[0], angles[1])));

				//whole extremity joint
				angles = FLSkeletonController::calcFirstDegreeJoint(skeleton, joint_i, joint_e, u, r, t);
				result->setJoint(joint_fl_w, std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint(angles[0], angles[1])));
			}

			//spherical coordinates for the head
			int joint_i = mae::model::GeneralSkeleton::SKEL_NECK;
			int joint_o = mae::model::GeneralSkeleton::SKEL_HEAD;

			int joint_fl_i = mae::fl::FLSkeleton::ANGLE_HEAD;

			cv::Vec2d angles = FLSkeletonController::calcFirstDegreeJoint(skeleton, joint_i, joint_o, r, t, u);
			result->setJoint(joint_fl_i, std::shared_ptr<mae::fl::FLJoint> (new mae::fl::FLJoint(angles[0], angles[1])));



			// calculate relative skeleton
			std::shared_ptr<mae::model::GeneralSkeleton> rel_skeleton = std::shared_ptr<mae::model::GeneralSkeleton>(new mae::model::GeneralSkeleton());

			//origin of the coordinate system (torso)
			rel_skeleton->setJoint(mae::model::GeneralSkeleton::SKEL_TORSO, skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_TORSO));

			std::vector<int> skel_joint_ids = mae::model::GeneralSkeleton::get_joint_ids();
			for (unsigned int i = 0; i< skel_joint_ids.size(); i++){
				if (skel_joint_ids[i] != mae::model::GeneralSkeleton::SKEL_TORSO){
					rel_skeleton->setJoint((int)skel_joint_ids[i], FLMath::vecToJoint(FLMath::projectToBasis(FLMath::jointToVec(skeleton->getJoint((int)skel_joint_ids[i])),FLMath::jointToVec(skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_TORSO)), u, r, t)));
				}
			}

			result->setRelativeSkeleton(rel_skeleton);


			//set coordinate system
			std::vector<double> vec_u;
			vec_u.push_back(u[0]);
			vec_u.push_back(u[1]);
			vec_u.push_back(u[2]);

			std::vector<double> vec_r;
			vec_r.push_back(r[0]);
			vec_r.push_back(r[1]);
			vec_r.push_back(r[2]);

			std::vector<double> vec_t;
			vec_t.push_back(t[0]);
			vec_t.push_back(t[1]);
			vec_t.push_back(t[2]);

			result->setCoordSys(vec_u, vec_r, vec_t);

			return result;
		}

		cv::Vec2d FLSkeletonController::calcFirstDegreeJoint_md(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md){
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->getJoint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->getJoint(outer_joint));

			//set up new rotated basis
			double beta = FLMath::calcAngle(md, r);

			cv::Vec3d u_r = u;
			cv::Vec3d r_r = r;
			cv::Vec3d t_r = t;

			if (beta != 0){
				//rotate around axis b = md x r ...
				cv::Vec3d b = cv::normalize(md.cross(r));

				//todo dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				cv::Vec3d u_r = FLMath::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				cv::Vec3d r_r = FLMath::rotateAroundAxis(r, b, -beta);
				cv::Vec3d t_r = FLMath::rotateAroundAxis(t, b, -beta);
			}

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = FLMath::calcAngleHalfDeg(r_r, fdvec);


			// calculates phi in radian
			double theta;

			if (FLMath::areCollinear(r_r, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = FLMath::projectOrthogonal(vec_o, vec_i, u_r, t_r);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

				theta = FLMath::calcAngleDeg(t_r, fdvec_p);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d FLSkeletonController::calcFirstDegreeJoint(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t){
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->getJoint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->getJoint(outer_joint));


			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = FLMath::calcAngleHalfDeg(u, fdvec);


			// calculates phi in radian
			double theta;

			if (FLMath::areCollinear(u, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = FLMath::projectOrthogonal(vec_o, vec_i, r, t);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

				theta = FLMath::calcAngleDeg(r, fdvec_p);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d FLSkeletonController::calcSecondDegreeJoint(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t){

			// ---
			// calculate angles for second degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->getJoint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->getJoint(outer_joint));
			cv::Vec3d vec_e = FLMath::jointToVec(skeleton->getJoint(extremity_joint));


			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// get second degree bone vector
			cv::Vec3d sdvec = cv::normalize(vec_e- vec_o);

			// calc inclination phi
			// angle between fdvec and sdvec which is the angle between r_r and sdvec (angle ranges from 0 to 180 degree
			double phi = FLMath::calcAngleHalfDeg(fdvec, sdvec);


			// calc azimuth theta
			double theta;

			if (FLMath::areCollinear(fdvec, sdvec))
			{
				// both joint vectors fdvec and sdvec are collinear
				// therefore we can set phi to zero
				theta = 0;
			}
			else
			{

				//rotate around axis b = v x r ...
				cv::Vec3d b = cv::normalize(fdvec.cross(r));

				// ... by rotation angle beta
				//double beta = std::acos(fdvec.dot(r));
				double beta = FLMath::calcAngle(fdvec, r);

				//todo dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				cv::Vec3d u_r = FLMath::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				//cv::Vec3d r_r = FLMath::rotateAroundAxis(r, b, -beta);
				cv::Vec3d t_r = FLMath::rotateAroundAxis(t, b, -beta);

				//plane othogonal to v is E(u,t)
				cv::Vec3d sdvec_p = FLMath::projectOrthogonal(sdvec+vec_o, vec_o, u_r, t_r);
				sdvec_p = cv::normalize(vec_o - sdvec_p);

				theta = FLMath::calcAngleDeg(t_r, sdvec_p);
			}


			//return the angles
			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}


	} // namespace fl
} // namespace mae
