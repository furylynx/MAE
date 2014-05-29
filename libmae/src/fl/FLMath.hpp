/*
 * FLMath.hpp
 *
 *  Created on: 28.05.2014
 *      Author: keks
 */

#ifndef FLMATH_HPP_
#define FLMATH_HPP_

//custom includes
#include "../model/GeneralJoint.hpp"
#include "FLJoint.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <memory>

namespace mae {
	namespace fl {

		class FLMath {
			public:

				// vector translations
				static cv::Vec3d jointToVec(std::shared_ptr<mae::model::GeneralJoint> joint);
				static std::shared_ptr<mae::model::GeneralJoint> vecToJoint(cv::Vec3d vec);

				static cv::Vec2d jointToVec_fl(std::shared_ptr<mae::fl::FLJoint> joint);
				static std::shared_ptr<mae::fl::FLJoint> vecTojoint_fl(cv::Vec2d vec);

				static std::vector<double> vecTostdVec(cv::Vec3d vec);
				static std::vector<double> vecTostdVec(cv::Vec2d vec);

				static cv::Vec3d stdVecToVec3d(std::vector<double> vec);
				static cv::Vec2d stdVecToVec2d(std::vector<double> vec);

				//projection, rotation
				static cv::Vec3d projectToBasis(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				static cv::Vec3d projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u, cv::Vec3d plane_v);
				static cv::Vec3d rotateAroundAxis(cv::Vec3d point, cv::Vec3d axis, double beta);

				//angle estimation
				static double radToDeg(double val);
				static bool areCollinear(cv::Vec3d a, cv::Vec3d b);

				static double calcAngle(cv::Vec3d a, cv::Vec3d b);
				static double calcAngleDeg(cv::Vec3d a, cv::Vec3d b);

				static double calcAngleHalf(cv::Vec3d a, cv::Vec3d b);
				static double calcAngleHalfDeg(cv::Vec3d a, cv::Vec3d b);

		};

	} /* namespace fl */
} /* namespace mae */

#endif /* FLMATH_HPP_ */
