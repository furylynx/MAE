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

		mae::fl::FLSkeleton FLSkeletonController::calculateSpecifiedSkeleton(mae::model::GeneralSkeleton* skeleton){

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
				mae::model::GeneralJoint joint = skeleton->getJoint(i);

				torso.at<double>(0,i) = joint.getX();
				torso.at<double>(1,i) = joint.getY();
				torso.at<double>(2,i) = joint.getZ();
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
			r = cv::normalize(r);
			t = cv::normalize(t);
			u = cv::normalize(u);



			// ---
			// calculate angles for first degree joints
			// ---


			//todo extract to own method calcFirstDegreeJoint
			mae::model::GeneralJoint joint_ls = skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_LEFT_SHOULDER);
			mae::model::GeneralJoint joint_le = skeleton->getJoint(mae::model::GeneralSkeleton::SKEL_LEFT_ELBOW);

			cv::Vec3d vec_ls;

			vec_ls[0] = joint_ls.getX();
			vec_ls[1] = joint_ls.getY();
			vec_ls[2] = joint_ls.getZ();

			cv::Vec3d vec_le;
			vec_le[0] = joint_le.getX();
			vec_le[1] = joint_le.getY();
			vec_le[2] = joint_le.getZ();

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_ls - vec_le);

			// calculates phi in radian
			double phi = std::acos(u.dot(fdvec));
			// ...to degree
			phi *= 180 / M_PI;


			//calculates theta in radian
			cv::Vec3d vec_le_p = projectOrthogonal(vec_le, vec_ls, r, t);
			cv::Vec3d fdvec_p = cv::normalize(vec_ls - vec_le_p);
			double theta = std::acos(r.dot(fdvec_p));

			mae::fl::FLSkeleton result = mae::fl::FLSkeleton();

			return result;
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

	} // namespace fl
} // namespace mae
