/*
* FLJoint.cpp
*
* Created on: 20.05.2014
* Author: keks
*/

#include "fl_joint.hpp"

namespace mae {
	namespace fl {

		//generates an invalid instance of the joint
		fl_joint::fl_joint() {
			this->phi_ = 0;
			this->theta_ = 0;

			this->valid_ = false;
		}

		//generates a valid instance of the joint
		fl_joint::fl_joint(double phi, double theta){
			this->phi_ = phi;
			this->theta_ = theta;

			this->valid_ = true;
		}

		fl_joint::~fl_joint() {
			this->valid_ = false;
		}


		void fl_joint::set_phi(double phi){
			this->phi_ = phi;
		}

		double fl_joint::get_phi() const{
			return phi_;
		}

		void fl_joint::set_theta(double theta){
			this->theta_ = theta;
		}

		double fl_joint::get_theta() const{
			return theta_;
		}


		void fl_joint::set_valid(bool isValid){
			this->valid_ = isValid;
		}

		bool fl_joint::is_valid() const{
			return valid_;
		}



	} // namespace fl
} // namespace mae
