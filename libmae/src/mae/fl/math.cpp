/*
 * FLMath.cpp
 *
 *  Created on: 28.05.2014
 *      Author: keks
 */

#include "math.hpp"

namespace mae
{
	namespace fl
	{

		cv::Vec3d math::jointToVec(std::shared_ptr<general_joint> joint)
		{
			cv::Vec3d result;

			result[0] = joint->get_x();
			result[1] = joint->get_y();
			result[2] = joint->get_z();
			return result;
		}

		std::shared_ptr<general_joint> math::vecToJoint(cv::Vec3d vec)
		{
			return std::shared_ptr<general_joint>(new general_joint(vec[0], vec[1], vec[2]));
		}

		cv::Vec2d math::jointToVec_fl(std::shared_ptr<mae::fl::fl_joint> joint)
		{
			cv::Vec2d result;

			result[0] = joint->get_phi();
			result[1] = joint->get_theta();
			return result;
		}

		std::shared_ptr<mae::fl::fl_joint> math::vecTojoint_fl(cv::Vec2d vec)
		{
			return std::shared_ptr<mae::fl::fl_joint>(new mae::fl::fl_joint(vec[0], vec[1]));
		}

		std::vector<double> math::vecTostdVec(cv::Vec3d vec)
		{
			std::vector<double> result;

			for (int i = 0; i < 3; i++)
			{
				result.push_back(vec[i]);
			}

			return result;
		}

		std::vector<double> math::vecTostdVec(cv::Vec2d vec)
		{
			std::vector<double> result;

			for (int i = 0; i < 2; i++)
			{
				result.push_back((double) vec[i]);
			}

			return result;
		}

		cv::Vec3d math::stdVecToVec3d(std::vector<double> vec)
		{

			if (vec.size() != 3)
			{
				throw std::invalid_argument("The parameter does not match the expected 3 dimensional vector.");
			}
			else
			{
				cv::Vec3d result;

				for (int i = 0; i < 3; i++)
				{
					result[i] = vec[i];
				}

				return result;
			}
		}

		cv::Vec2d math::stdVecToVec2d(std::vector<double> vec)
		{

			if (vec.size() != 2)
			{
				throw std::invalid_argument("The parameter does not match the expected 2 dimensional vector.");
			}
			else
			{
				cv::Vec2d result;

				for (int i = 0; i < 2; i++)
				{
					result[i] = vec[i];
				}

				return result;
			}
		}

		cv::Vec3d math::matrix_mul(cv::Mat m, cv::Vec3d vec)
		{
			//point to be multiplied
			cv::Mat p = cv::Mat(3, 1, CV_64F);
			p.at<double>(0) = vec[0];
			p.at<double>(1) = vec[1];
			p.at<double>(2) = vec[2];

			cv::Mat result = m*p;
			return result.rowRange(0,3);
		}

		cv::Vec3d math::projectToBasis(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r,
				cv::Vec3d t)
		{
			//point to be projected
			cv::Mat p = cv::Mat(4, 1, CV_64F);
			p.at<double>(0) = point[0];
			p.at<double>(1) = point[1];
			p.at<double>(2) = point[2];
			p.at<double>(3) = 1;

			//coordinate transform matrix
			cv::Mat m = cv::Mat(4, 4, CV_64F);
			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 0) = u[i];
			}
			m.at<double>(3, 0) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 1) = r[i];
			}
			m.at<double>(3, 1) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 2) = t[i];
			}
			m.at<double>(3, 2) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 3) = position_vector[i];
			}
			m.at<double>(3, 3) = 1;

			//calc result
			cv::Mat result = m.inv() * p;

			return result.rowRange(0, 3);
		}

		cv::Vec3d math::projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u,
				cv::Vec3d plane_v)
		{

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
			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 0) = plane_u[i];
			}
			m.at<double>(3, 0) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 1) = plane_v[i];
			}
			m.at<double>(3, 1) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 2) = normal[i];
			}
			m.at<double>(3, 2) = 0;

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 3) = position_vector[i];
			}
			m.at<double>(3, 3) = 1;

			//reduce matrix
			cv::Mat x = cv::Mat::eye(4, 4, CV_64F);
			x.at<double>(2, 2) = 0;

			//calc result
			cv::Mat result = m * x * m.inv() * p;

			return result.rowRange(0, 3);
		}

		cv::Vec3d math::rotateAroundAxis(cv::Vec3d point, cv::Vec3d axis, double beta)
		{

			if (beta == 0)
			{
				return point;
			}

			//point to be projected
			cv::Mat p = cv::Mat::zeros(3, 1, CV_64F);
			p.at<double>(0) = point[0];
			p.at<double>(1) = point[1];
			p.at<double>(2) = point[2];

			//set up basis from axis
			axis = cv::normalize(axis);
			cv::Vec3d x;
			x[0] = 1;
			x[1] = 0;
			x[2] = 0;

			if (math::areCollinear(axis, x))
			{
				x[0] = 0;
				x[1] = 1;
			}

			cv::Vec3d axis_o1 = cv::normalize(axis.cross(x));
			cv::Vec3d axis_o2 = cv::normalize(axis.cross(axis_o1));

			//coordinate transform matrix
			cv::Mat m = cv::Mat::zeros(3, 3, CV_64F);
			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 0) = axis[i];
			}

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 1) = axis_o1[i];
			}

			for (int i = 0; i < 3; i++)
			{
				m.at<double>(i, 2) = axis_o2[i];
			}

			//rotation matrix
			double cos_beta = std::cos(beta);
			double sin_beta = std::sin(beta);

			cv::Mat r_x = cv::Mat::zeros(3, 3, CV_64F);
			r_x.at<double>(1, 1) = cos_beta;
			r_x.at<double>(1, 2) = -sin_beta;
			r_x.at<double>(2, 1) = sin_beta;
			r_x.at<double>(2, 2) = cos_beta;
			r_x.at<double>(0, 0) = 1;

			cv::Mat result = m * r_x * m.inv() * p;
			return result.rowRange(0, 3);
		}

		cv::Vec3d math::rotation_angles_zxy(cv::Vec3d a, cv::Vec3d b)
		{

			//---------------------------------------------------------------
			//quaternion
			//---------------------------------------------------------------
			cv::Vec4d q = math::quaternion(a, b);


			double alpha = math::calcAngleHalf(a,b);
			if (alpha < 0.01 && alpha > -0.01)
			{
				return cv::Vec3d(0,0,0);
			}

			//w is first coefficient (note that other forms put w at the end)
			double qw = q[0];
			double qx = q[1];
			double qy = q[2];
			double qz = q[3];

			//case zxy
			double r11 = -2 * (qx * qy - qw * qz);
			double r12 = qw * qw - qx * qx + qy * qy - qz * qz;
			double r21 = 2 * (qy * qz + qw * qx);
			double r31 = -2 * (qx * qz - qw * qy);
			double r32 = qw * qw - qx * qx - qy * qy + qz * qz;

			double ypsilon = std::atan2(r31, r32);
			double xi = std::asin(r21);
			double zeta = std::atan2(r11, r12);

			return cv::Vec3d(zeta, xi, ypsilon);
		}

		cv::Vec3d math::rotation_angles_yzx(cv::Vec3d a, cv::Vec3d b)
		{
			//---------------------------------------------------------------
			//axis angle approach yzx order!!
			//---------------------------------------------------------------

			cv::Vec3d e1(1, 0, 0);
			cv::Vec3d e2(0, 1, 0);
			cv::Vec3d e3(0, 0, 1);

			//orthogonal vector which is the rotation axis
			cv::Vec3d v;
			if (math::areCollinear(a, b))
			{
				if (math::areCollinear(a, e1))
				{
					if (math::areCollinear(a, e2))
					{
						v = cv::normalize(a.cross(e3));
					}
					else
					{
						v = cv::normalize(a.cross(e2));
					}
				}
				else
				{
					v = cv::normalize(a.cross(e1));
				}
			}
			else
			{
				v = cv::normalize(a.cross(b));
			}

			//angle for axis-angle representation
			double alpha = math::calc_angle_plane(a, b, v);

			if (alpha < 0.01 && alpha > -0.01)
			{
				return cv::Vec3d(0,0,0);
			}

			double s = std::sin(alpha);
			double c = std::cos(alpha);
			double t = 1 - c;

			double x = v[0];
			double y = v[1];
			double z = v[2];

			double ypsilon = 0;
			double zeta = 0;
			double xi = 0;

			//check singularities
			if ((x * y * t + z * s) > 0.998)
			{
				// north pole singularity detected
				ypsilon = 2 * std::atan2(x * std::sin(alpha / 2), std::cos(alpha / 2));
				zeta = M_PI_2;
				xi = 0;
				return cv::Vec3d(ypsilon, zeta, xi);
			}
			if ((x * y * t + z * s) < -0.998)
			{
				// south pole singularity detected
				ypsilon = -2 * std::atan2(x * std::sin(alpha / 2), std::cos(alpha / 2));
				zeta = M_PI_2;
				xi = 0;
				return cv::Vec3d(ypsilon, zeta, xi);
			}
			ypsilon = std::atan2(y * s - x * z * t, 1 - (y * y + z * z) * t);
			zeta = std::asin(x * y * t + z * s);
			xi = std::atan2(x * s - y * z * t, 1 - (x * x + z * z) * t);

			return cv::Vec3d(ypsilon, zeta, xi);
		}

		cv::Vec3d math::rotate_zxy(cv::Vec3d a, double zeta, double xi, double ypsilon)
		{
			//point to matrix
			cv::Mat a_m = cv::Mat::zeros(3, 1, CV_64F);
			a_m.at<double>(0) = a[0];
			a_m.at<double>(1) = a[1];
			a_m.at<double>(2) = a[2];

			cv::Mat result = math::matrix_rot_z(zeta) * math::matrix_rot_x(xi) * math::matrix_rot_y(ypsilon)
					* a_m;
			return result.rowRange(0, 3);
		}

		cv::Vec3d math::rotate_yzx(cv::Vec3d a, double ypsilon, double zeta, double xi)
		{
			//point to matrix
			cv::Mat a_m = cv::Mat::zeros(3, 1, CV_64F);
			a_m.at<double>(0) = a[0];
			a_m.at<double>(1) = a[1];
			a_m.at<double>(2) = a[2];

			cv::Mat result = math::matrix_rot_y(ypsilon) * math::matrix_rot_z(zeta) * math::matrix_rot_x(xi)
					* a_m;
			return result.rowRange(0, 3);
		}

		cv::Mat math::matrix_rot_x(double beta)
		{
			//rotation matrix
			double cos_beta = std::cos(beta);
			double sin_beta = std::sin(beta);

			cv::Mat result = cv::Mat::zeros(3, 3, CV_64F);
			result.at<double>(0, 0) = 1;
			result.at<double>(1, 1) = cos_beta;
			result.at<double>(1, 2) = -sin_beta;
			result.at<double>(2, 1) = sin_beta;
			result.at<double>(2, 2) = cos_beta;

			return result;
		}

		cv::Mat math::matrix_rot_y(double beta)
		{
			//rotation matrix
			double cos_beta = std::cos(beta);
			double sin_beta = std::sin(beta);

			cv::Mat result = cv::Mat::zeros(3, 3, CV_64F);
			result.at<double>(1, 1) = 1;
			result.at<double>(0, 0) = cos_beta;
			result.at<double>(0, 2) = sin_beta;
			result.at<double>(2, 0) = -sin_beta;
			result.at<double>(2, 2) = cos_beta;

			return result;
		}

		cv::Mat math::matrix_rot_z(double beta)
		{
			//rotation matrix
			double cos_beta = std::cos(beta);
			double sin_beta = std::sin(beta);

			cv::Mat result = cv::Mat::zeros(3, 3, CV_64F);
			result.at<double>(2, 2) = 1;
			result.at<double>(0, 0) = cos_beta;
			result.at<double>(0, 1) = -sin_beta;
			result.at<double>(1, 0) = sin_beta;
			result.at<double>(1, 1) = cos_beta;

			return result;
		}

		cv::Mat math::matrix_rot_zxy(double zeta, double xi, double ypsilon)
		{
			//TODO use direction matrix not calculation for all together

			return math::matrix_rot_z(zeta) * math::matrix_rot_x(xi) * math::matrix_rot_y(ypsilon);
		}

		cv::Vec4d math::quaternion(cv::Vec3d a, cv::Vec3d b)
		{
			a = cv::normalize(a);
			b = cv::normalize(b);

			cv::Vec3d v;
			if (math::areCollinear(a, b))
			{
				//handle singularity

				cv::Vec3d e1(1,0,0);
				cv::Vec3d e2(0,1,0);
				cv::Vec3d e3(0,0,1);

				if (math::areCollinear(a, e1))
				{
					if (math::areCollinear(a, e2))
					{
						v = a.cross(e3);
					}
					else
					{
						v = a.cross(e2);
					}
				}
				else
				{
					v = a.cross(e1);
				}
			}
			else
			{
				v = a.cross(b);
			}

			cv::Vec4d q(1.0 + a.dot(b), v[0], v[1], v[2]);
			return cv::normalize(q);
		}

		bool math::areCollinear(cv::Vec3d a, cv::Vec3d b)
		{
			// assumption: angle between both is 0 or 180 degree
			double angle = math::calcAngleHalf(a, b);

			//fix round-off errors
			return (angle > -0.01 && angle < 0.01) || (angle > (M_PI - 0.01) && angle < (M_PI + 0.01))
					|| (angle > (-M_PI - 0.01) && angle < (-M_PI + 0.01));
		}

//		double math::calcAngle(cv::Vec3d a, cv::Vec3d b)
//		{
//
//			double halfAngle = math::calcAngleHalf(a, b);
//
//			if (halfAngle == 0 || halfAngle == M_PI || halfAngle == -M_PI)
//			{
//				return halfAngle;
//			}
//
//			//calc cross product
//			cv::Vec3d cross = a.cross(b);
//
//			int sign = (cross[2] > 0) - (cross[2] < 0);
//
//			if (sign == 0)
//			{
//				sign = (cross[1] > 0) - (cross[1] < 0);
//
//				if (sign == 0)
//				{
//					sign = (cross[0] > 0) - (cross[0] < 0);
//
//					if (sign == 0)
//					{
//						//todo throw exception ?
//						std::cerr << "This case should not occur" << std::endl;
//						std::cerr << "a=" << a << std::endl;
//						std::cerr << "b=" << b << std::endl;
//						std::cerr << "half angle=" << math::radToDeg(halfAngle) << "° " << std::endl;
//						return halfAngle;
//					}
//				}
//			}
//
//			return halfAngle * sign;
//		}
//
//		double math::calcAngleDeg(cv::Vec3d a, cv::Vec3d b)
//		{
//			return math::radToDeg(math::calcAngle(a, b));
//		}

		double math::calc_angle_plane(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal)
		{
			a = cv::normalize(a);
			b = cv::normalize(b);
			normal = cv::normalize(normal);

			double dot = a.dot(b);
			double det = a[0] * b[1] * normal[2] + b[0] * normal[1] * a[2] + normal[0] * a[1] * b[2]
					- normal[0] * b[1] * a[2] - b[0] * a[1] * normal[2] - a[0] * normal[1] * b[2];

			return std::atan2(det, dot);
		}

		double math::calc_angle_plane_deg(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal)
		{
			return math::radToDeg(math::calc_angle_plane(a, b, normal));
		}

		double math::calcAngleHalf(cv::Vec3d a, cv::Vec3d b)
		{
			a = cv::normalize(a);
			b = cv::normalize(b);

			double dot = a.dot(b);

			// fix round-off errors
			if ((dot > 1 && dot < 1.01) || (dot < -1 && dot > -1.01))
			{
				dot = (int) dot;
			}

			return std::acos(dot);
		}

		double math::calcAngleHalfDeg(cv::Vec3d a, cv::Vec3d b)
		{
			return math::radToDeg(math::calcAngleHalf(a, b));
		}

		double math::radToDeg(double val)
		{
			return val * 180 / M_PI;
		}

		double math::degToRad(double val)
		{
			return val * M_PI / 180;
		}

		double math::fmod_pos(double a, double b)
		{
			double tmp = std::fmod(a, b);

			if (tmp < 0)
			{
				tmp = b + tmp;
			}

			return tmp;
		}

		int math::sign(double x)
		{
			return (x > 0) - (x < 0);
		}

	} // namespace fl
} // namespace mae
