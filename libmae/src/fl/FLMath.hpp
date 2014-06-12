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

namespace mae
{
	namespace fl
	{

		class FLMath
		{
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

				static cv::Vec3d matrix_mul(cv::Mat m, cv::Vec3d vec);

				//projection, rotation
				static cv::Vec3d projectToBasis(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r,
						cv::Vec3d t);

				static cv::Vec3d projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u,
						cv::Vec3d plane_v);
				static cv::Vec3d rotateAroundAxis(cv::Vec3d point, cv::Vec3d axis, double beta);


				/**
				 * Returns the angles for the rotation matrices Rz, Rx, Ry which transform the point a to the point b. The rotation matrices are applied in z-x-y order which means that RzRxRy*a = b.
				 *
				 * @param a The point a which is meant to be rotated to b.
				 * @param b The target point.
				 * @return The angles alpha, beta and gamma that are applied by Rz(alpha), Rx(beta) and Ry(gamma).
				 */
				static cv::Vec3d rotation_angles_zxy(cv::Vec3d a, cv::Vec3d b);

				static cv::Vec3d rotation_angles_yzx(cv::Vec3d a, cv::Vec3d b);

				static cv::Vec3d rotate_zxy(cv::Vec3d a, double zeta, double xi, double ypsilon);

				/**
				 * Rotates the vector a using the NASA standard yaw, pitch, roll (also known as heading, attitude, bank).
				 *
				 * @param a The vector to be rotated.
				 * @param ypsilon The angle for Ry.
				 * @param zeta The angle for Rz.
				 * @param xi The angle for Rx.
				 * @return The rotated vector.
				 */
				static cv::Vec3d rotate_yzx(cv::Vec3d a, double ypsilon, double zeta, double xi);

				static cv::Mat matrix_rot_x(double beta);
				static cv::Mat matrix_rot_y(double beta);
				static cv::Mat matrix_rot_z(double beta);

				static cv::Mat matrix_rot_zxy(double zeta, double xi, double ypsilon);

				/**
				 * Return the quaternion representing the rotation from a to b. The returned vector begins is ordered [qw, qx, qy, qz].
				 *
				 * @param a Vector to be rotated to b.
				 * @param b Target vector.
				 * @return The quaternion as a four-dimensional vector.
				 */
				static cv::Vec4d quaternion(cv::Vec3d a, cv::Vec3d b);

				//angle estimation
				static double radToDeg(double val);
				static double degToRad(double val);
				static bool areCollinear(cv::Vec3d a, cv::Vec3d b);

				static double calcAngle(cv::Vec3d a, cv::Vec3d b);
				static double calcAngleDeg(cv::Vec3d a, cv::Vec3d b);

				static double calc_angle_plane(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal);
				static double calc_angle_plane_deg(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal);

				static double calcAngleHalf(cv::Vec3d a, cv::Vec3d b);
				static double calcAngleHalfDeg(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Returns x = a mod b, using the modulo operation for floating-point values. The result is positive only.
				 *
				 * @param a
				 * @param b
				 * @return x = a mod b on [0, b).
				 */
				static double fmod_pos(double a, double b);

				/**
				 * Returns the sign of a double value. Zero if x is zero, -1 if x is less than zero and 1 if x is greater than zero.
				 * @param x The double value.
				 * @return The sign.
				 */
				static int sign(double x);

		};

	} /* namespace fl */
} /* namespace mae */

#endif /* FLMATH_HPP_ */
