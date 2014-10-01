/*
 * FLMath.hpp
 *
 *  Created on: 28.05.2014
 *      Author: keks
 */

#ifndef FLMATH_HPP_
#define FLMATH_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "angular_joint.hpp"

#include "../basis.hpp"
#include "../general_joint.hpp"

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

		class math
		{
			public:

				/**
				 * Translates the joint to a 3D vector.
				 *
				 * @param joint The joint.
				 * @return The result.
				 */
				static cv::Vec3d joint_to_vec(std::shared_ptr<general_joint> joint);

				/**
				 * Translates the 3D vector to a joint.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static std::shared_ptr<general_joint> vec_to_joint(cv::Vec3d vec);

				/**
				 * Translates the fl_joint to a 2D vector.
				 *
				 * @param joint The joint.
				 * @return The result.
				 */
				static cv::Vec2d joint_to_vec_fl(std::shared_ptr<mae::fl::angular_joint> joint);

				/**
				 * Translates the 2D vector to a fl_joint.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static std::shared_ptr<mae::fl::angular_joint> vec_to_joint_fl(cv::Vec2d vec);

				/**
				 * Translates the 3D vector to a std::vector.
				 * @param vec The vector.
				 * @return The result.
				 */
				static std::vector<double> vec_to_stdvec(cv::Vec3d vec);

				/**
				 * Translates the 2D vector to a std::vector.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static std::vector<double> vec_to_stdvec(cv::Vec2d vec);

				/**
				 * Translates the std::vector to a 3D vector.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static cv::Vec3d stdvec_to_vec3d(std::vector<double> vec);

				/**
				 * Translates the std::vector to a 2D vector.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static cv::Vec2d stdvec_to_vec2d(std::vector<double> vec);

				/**
				 * Translates the vec3d of mae to a 3D vector of cv.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static cv::Vec3d maevec_to_vec3d(std::shared_ptr<vec3d> vec);

				/**
				 * Translates the 3D vector of cv to a vec3d of mae.
				 *
				 * @param vec The vector.
				 * @return The result.
				 */
				static std::shared_ptr<vec3d> vec3d_to_maevec(cv::Vec3d vec);

				/**
				 * Performs a matrix calculation.
				 *
				 * @param m The matrix.
				 * @param vec The vector.
				 * @return The result.
				 */
				static cv::Vec3d matrix_mul(cv::Mat m, cv::Vec3d vec);

				/**
				 * Projects the point to the new basis given in coordinates of the points current basis.
				 * @param point The point to be translated.
				 * @param position_vector The point of origin of the new basis.
				 * @param u The new basis' u vector.
				 * @param r The new basis' r vector.
				 * @param t The new basis' t vector.
				 * @return The result.
				 */
				static cv::Vec3d project_to_basis(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r,
						cv::Vec3d t);

				/**
				 * Projects the point to the new basis given in coordinates of the points current basis.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static cv::Vec3d project_to_basis(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);


				/**
				 * Projects the point to the new basis given in coordinates of the points current basis.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static std::shared_ptr<vec3d> project_to_basis_maevec(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);

				/**
				 * Projects the point given by the basis to the default coordinate system.
				 *
				 * @param point The point to be translated.
				 * @param position_vector The point of origin of the basis.
				 * @param u The basis' u vector.
				 * @param r The basis' r vector.
				 * @param t The basis' t vector.
				 * @return The result.
				 */
				static cv::Vec3d project_back_to_default(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r,
						cv::Vec3d t);

				/**
				 * Projects the point given by the basis to the default coordinate system.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static cv::Vec3d project_back_to_default(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);

				/**
				 * Projects the point given by the basis to the default coordinate system.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static std::shared_ptr<vec3d> project_back_to_default_maevec(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);

				/**
				 * Performs an orthogonal projection to the plane spanned by plane_u and plane_v positioned
				 * where the position vector points.
				 *
				 * @param point The point to be translated
				 * @param position_vector The position vector of the plane.
				 * @param plane_u The first direction vector of the plane which spans it.
				 * @param plane_v The second direction vector of the plane which spans it.
				 * @return The result.
				 */
				static cv::Vec3d project_orthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u,
						cv::Vec3d plane_v);

				/**
				 * Rotates the point around the given axis.
				 *
				 * @param point The point to be rotated.
				 * @param axis The axis
				 * @param beta The angle.
				 * @return The result.
				 */
				static cv::Vec3d rotate_around_axis(cv::Vec3d point, cv::Vec3d axis, double beta);

				/**
				 * Returns the angles for the rotation matrices Rz, Rx, Ry which transform the point a to the point b. The rotation matrices are applied in z-x-y order which means that RzRxRy*a = b.
				 *
				 * @param a The point a which is meant to be rotated to b.
				 * @param b The target point.
				 * @return The angles alpha, beta and gamma that are applied by Rz(alpha), Rx(beta) and Ry(gamma).
				 */
				static cv::Vec3d rotation_angles_zxy(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Returns the angles for the rotation matrices Ry, Rz, Rx which transform the point a to the point b. The rotation matrices are applied in y-z-x order which means that RyRzRx*a = b.
				 *
				 * @param a The point a which is meant to be rotated to b.
				 * @param b The target point.
				 * @return The angles alpha, beta and gamma that are applied by Ry(alpha), Rz(beta) and Rx(gamma).
				 */
				static cv::Vec3d rotation_angles_yzx(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Rotates in zxy order.
				 *
				 * @param a The vector to be rotated.
				 * @param zeta The angle for Rz.
				 * @param xi The angle for Rx.
				 * @param ypsilon The angle for Ry.
				 * @return The rotated vector.
				 */
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

				/**
				 * Returns the rotation matrix for the x-axis.
				 *
				 * @param beta The angle
				 * @return The matrix.
				 */
				static cv::Mat matrix_rot_x(double beta);

				/**
				 * Returns the rotation matrix for the y-axis.
				 *
				 * @param beta The angle
				 * @return The matrix.
				 */
				static cv::Mat matrix_rot_y(double beta);

				/**
				 * Returns the rotation matrix for the z-axis.
				 *
				 * @param beta The angle
				 * @return The matrix.
				 */
				static cv::Mat matrix_rot_z(double beta);

				/**
				 * Returns the rotation matrix for a rotation in the zxy-order.
				 *
				 * @param zeta
				 * @param xi
				 * @param ypsilon
				 * @return
				 */
				static cv::Mat matrix_rot_zxy(double zeta, double xi, double ypsilon);

				/**
				 * Returns the quaternion representing the rotation from a to b. The returned vector begins is ordered [qw, qx, qy, qz].
				 *
				 * @param a Vector to be rotated to b.
				 * @param b Target vector.
				 * @return The quaternion as a four-dimensional vector.
				 */
				static cv::Vec4d quaternion(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Translates the angle in radian to degree.
				 *
				 * @param val The angle in radian.
				 * @return The angle in degree.
				 */
				static double rad_to_deg(double val);

				/**
				 * Translates the angle in degree to radian.
				 *
				 * @param val The angle in degree.
				 * @return The angle in radian.
				 */
				static double deg_to_rad(double val);

				/**
				 * Returns true if the vectors are approximately collinear.
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return True if collinear.
				 */
				static bool are_collinear(cv::Vec3d a, cv::Vec3d b);

//				/**
//				 * Calculates the angle in radian between the two vectors.
//				 *
//				 * @param a The vector a.
//				 * @param b The vector a.
//				 * @return The result.
//				 */
//				static double calcAngle(cv::Vec3d a, cv::Vec3d b);
//
//				/**
//				 * Calculates the angle in degree between the two vectors.
//				 *
//				 * @param a The vector a.
//				 * @param b The vector a.
//				 * @return The result.
//				 */
//				static double calcAngleDeg(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Calculates the angle in radian oriented to the plane whose normal is given (-PI to PI).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @param normal The normal to the plane.
				 * @return The result.
				 */
				static double calc_angle_plane(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal);

				/**
				 * Calculates the angle in degree oriented to the plane whose normal is given (-180 to 180 degree).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @param normal The normal to the plane.
				 * @return The result.
				 */
				static double calc_angle_plane_deg(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal);

				/**
				 * Calculates the angle in radian between the two vectors (0 to PI).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return The result.
				 */
				static double calc_angle_half(cv::Vec3d a, cv::Vec3d b);

				/**
				 * Calculates the angle in degree between the two vectors (0 to 180 degree).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return The result.
				 */
				static double calc_angle_half_deg(cv::Vec3d a, cv::Vec3d b);

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
				 *
				 * @param x The double value.
				 * @return The sign.
				 */
				static int sign(double x);

		};

	} // namespace fl
} // namespace mae

#endif // FLMATH_HPP_
