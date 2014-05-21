/*
 * GeneralJoint.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#include "GeneralJoint.hpp"

namespace mae {
	namespace model {

		GeneralJoint::~GeneralJoint() {
			this->valid = false;
		}

		GeneralJoint::GeneralJoint() {
			this->x = 0;
			this->y = 0;
			this->z = 0;

			this->valid = false;
		}

		GeneralJoint::GeneralJoint(double x, double y, double z){
			this->x = x;
			this->y = y;
			this->z = z;

			this->valid = true;
		}

		void GeneralJoint::setX(double x){
			this->x = x;
		}

		double GeneralJoint::getX() const{
			return x;
		}

		void GeneralJoint::setY(double y){
			this->y = y;
		}

		double GeneralJoint::getY() const{
			return y;
		}

		void GeneralJoint::setZ(double z){
			this->z = z;
		}

		double GeneralJoint::getZ() const{
			return z;
		}

		void GeneralJoint::setValid(bool isValid){
			this->valid = isValid;
		}

		bool GeneralJoint::isValid() const{
			return valid;
		}

	} // namespace model
} // namespace mae
