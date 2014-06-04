/*
 * FLMath.cpp
 *
 *  Created on: 28.05.2014
 *      Author: keks
 */

#include "FLMath.hpp"

namespace mae
{
	namespace fl
	{

		cv::Vec3d FLMath::jointToVec(std::shared_ptr<mae::model::GeneralJoint> joint)
		{
			cv::Vec3d result;

			result[0] = joint->getX();
			result[1] = joint->getY();
			result[2] = joint->getZ();
			return result;
		}

		std::shared_ptr<mae::model::GeneralJoint> FLMath::vecToJoint(cv::Vec3d vec)
		{
			return std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint(vec[0], vec[1], vec[2]));
		}

		cv::Vec2d FLMath::jointToVec_fl(std::shared_ptr<mae::fl::FLJoint> joint)
		{
			cv::Vec2d result;

			result[0] = joint->getPhi();
			result[1] = joint->getTheta();
			return result;
		}

		std::shared_ptr<mae::fl::FLJoint> FLMath::vecTojoint_fl(cv::Vec2d vec)
		{
			return std::shared_ptr<mae::fl::FLJoint>(new mae::fl::FLJoint(vec[0], vec[1]));
		}

		std::vector<double> FLMath::vecTostdVec(cv::Vec3d vec)
		{
			std::vector<double> result;

			for (int i = 0; i < 3; i++)
			{
				result.push_back(vec[i]);
			}

			return result;
		}

		std::vector<double> FLMath::vecTostdVec(cv::Vec2d vec)
		{
			std::vector<double> result;

			for (int i = 0; i < 2; i++)
			{
				result.push_back((double) vec[i]);
			}

			return result;
		}

		cv::Vec3d FLMath::stdVecToVec3d(std::vector<double> vec)
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

		cv::Vec2d FLMath::stdVecToVec2d(std::vector<double> vec)
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

		cv::Vec3d FLMath::projectToBasis(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d u, cv::Vec3d r,
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

		cv::Vec3d FLMath::projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u,
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

		cv::Vec3d FLMath::rotateAroundAxis(cv::Vec3d point, cv::Vec3d axis, double beta)
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

			if (FLMath::areCollinear(axis, x))
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

		bool FLMath::areCollinear(cv::Vec3d a, cv::Vec3d b)
		{

			// collinear if a = beta * b;

			// assumption: angle between both is 0 or 180 degree (seems to be more robust than calculating beta)
			a = cv::normalize(a);
			b = cv::normalize(b);

			//no need for angle ranging from 0-360 therefore this does the trick
			double angle = FLMath::calcAngleHalf(a, b); //std::acos(a.dot(b));

			//fix round-off errors
			return (angle > -0.01 && angle < 0.01) || (angle > (M_PI - 0.01) && angle < (M_PI + 0.01))
					|| (angle > (-M_PI - 0.01) && angle < (-M_PI + 0.01));
		}

		double FLMath::calcAngle(cv::Vec3d a, cv::Vec3d b)
		{

			double halfAngle = FLMath::calcAngleHalf(a, b);

			if (halfAngle == 0 || halfAngle == M_PI || halfAngle == -M_PI)
			{
				return halfAngle;
			}

			//calc cross product
			cv::Vec3d cross = a.cross(b);

			int sign = (cross[2] > 0) - (cross[2] < 0);

			if (sign == 0)
			{
				sign = (cross[1] > 0) - (cross[1] < 0);

				if (sign == 0)
				{
					sign = (cross[0] > 0) - (cross[0] < 0);

					if (sign == 0)
					{
						//todo throw exception ?
						std::cerr << "This case should not occur" << std::endl;
						std::cerr << "a=" << a << std::endl;
						std::cerr << "b=" << b << std::endl;
						std::cerr << "half angle=" << FLMath::radToDeg(halfAngle) << "° " << std::endl;
						return halfAngle;
					}
				}
			}

			return halfAngle * sign;
		}

		double FLMath::calcAngleDeg(cv::Vec3d a, cv::Vec3d b)
		{
			return FLMath::radToDeg(FLMath::calcAngle(a, b));
		}

		double FLMath::calc_angle_plane(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal)
		{
			a = cv::normalize(a);
			b = cv::normalize(b);
			normal = cv::normalize(normal);

			double dot = a.dot(b);
			double det = a[0] * b[1] * normal[2] + b[0] * normal[1] * a[2] + normal[0] * a[1] * b[3]
					- normal[0] * b[1] * a[2] - b[0] * a[1] * normal[2] - a[0] * normal[1] * b[2];

			return std::atan2(det, dot);
		}

		double FLMath::calc_angle_plane_deg(cv::Vec3d a, cv::Vec3d b, cv::Vec3d normal)
		{
			return FLMath::radToDeg(FLMath::calc_angle_plane(a, b, normal));
		}

		double FLMath::calcAngleHalf(cv::Vec3d a, cv::Vec3d b)
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

		double FLMath::calcAngleHalfDeg(cv::Vec3d a, cv::Vec3d b)
		{
			return FLMath::radToDeg(FLMath::calcAngleHalf(a, b));
		}

		double FLMath::radToDeg(double val)
		{
			return val * 180 / M_PI;
		}

		double FLMath::fmod_pos(double a, double b)
		{
			double tmp = std::fmod(a, b);

			if (tmp < 0)
			{
				tmp = b + tmp;
			}

			return tmp;
		}
	//todo other

	}// namespace fl
} // namespace mae