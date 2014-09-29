/*
 * FLJoint.cpp
 *
 * Created on: 20.05.2014
 * Author: keks
 */

#include "angular_joint.hpp"

namespace mae
{
	namespace fl
	{

		//generates an invalid instance of the joint
		angular_joint::angular_joint()
		{
			phi_ = 0;
			theta_ = 0;

			confidence_ = 0;

			valid_ = false;
		}

		//generates a valid instance of the joint
		angular_joint::angular_joint(double phi, double theta, double confidence)
		{
			phi_ = phi;
			theta_ = theta;

			confidence_ = confidence;

			valid_ = true;
		}

		angular_joint::~angular_joint()
		{
			this->valid_ = false;
		}

		void angular_joint::set_phi(double phi)
		{
			this->phi_ = phi;
		}

		double angular_joint::get_phi() const
		{
			return phi_;
		}

		void angular_joint::set_theta(double theta)
		{
			this->theta_ = theta;
		}

		double angular_joint::get_theta() const
		{
			return theta_;
		}

		void angular_joint::set_valid(bool isValid)
		{
			this->valid_ = isValid;
		}

		bool angular_joint::is_valid() const
		{
			return valid_;
		}

		void angular_joint::set_confidence(double confidence)
		{
			confidence_ = confidence;
		}

		double angular_joint::get_confidence() const
		{
			return confidence_;
		}

	} // namespace fl
} // namespace mae
