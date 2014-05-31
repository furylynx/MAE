/*
* FLJoint.cpp
*
* Created on: 20.05.2014
* Author: keks
*/

#include "FLJoint.hpp"

namespace mae {
	namespace fl {

		//generates an invalid instance of the joint
		FLJoint::FLJoint() {
			this->phi = 0;
			this->theta = 0;

			this->valid = false;
		}

		//generates a valid instance of the joint
		FLJoint::FLJoint(double phi, double theta){
			this->phi = phi;
			this->theta = theta;

			this->valid = true;
		}

		FLJoint::~FLJoint() {
			this->valid = false;
		}


		void FLJoint::setPhi(double phi){
			this->phi = phi;
		}

		double FLJoint::getPhi() const{
			return phi;
		}

		void FLJoint::setTheta(double theta){
			this->theta = theta;
		}

		double FLJoint::getTheta() const{
			return theta;
		}


		void FLJoint::setValid(bool isValid){
			this->valid = isValid;
		}

		bool FLJoint::isValid() const{
			return valid;
		}



	} // namespace fl
} // namespace mae
