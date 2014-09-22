/*
 * GeneralJoint.h
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef GENERALJOINT_H_
#define GENERALJOINT_H_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#include <iostream>
#include <sstream>
#include <memory>

namespace mae
{

	class general_joint
	{
		public:
			virtual ~general_joint();

			/**
			 * Creates an initially invalid general joint.
			 */
			general_joint();

			/**
			 * Creates a general joint with values set.
			 *
			 * @param x The x-coordinate.
			 * @param y The y-coordinate.
			 * @param z The z-coordinate.
			 * @param rotation The rotation of the bone of which this joint is the end point (ranging from 0 to 360 degree).
			 * @param confidence The confidence (ranging from zero to one, where one is the most confident)
			 */
			general_joint(double x, double y, double z, double rotation = 0, double confidence = 1);

			/**
			 * Sets the x-coordinate.
			 *
			 * @param x The x-coordinate.
			 */
			virtual void set_x(double x);

			/**
			 * Returns the x-coordinate.
			 * @return The x-coordinate.
			 */
			virtual double get_x() const;

			/**
			 * Sets the y-coordinate.
			 *
			 * @param y The y-coordinate.
			 */
			virtual void set_y(double y);

			/**
			 * Returns the y-coordinate.
			 *
			 * @return The y-coordinate.
			 */
			virtual double get_y() const;

			/**
			 * Sets the z-coordinate.
			 *
			 * @param z The z-coordinate.
			 */
			virtual void set_z(double z);

			/**
			 * Returns the z-coordinate.
			 *
			 * @return The z-coordinate.
			 */
			virtual double get_z() const;

			/**
			 * Sets the validity of this joint.
			 *
			 * @param is_valid Returns true if the joint is valid.
			 */
			virtual void set_valid(bool is_valid);

			/**
			 * Returns the validity of this joint.
			 *
			 * @return True if valid.
			 */
			virtual bool is_valid() const;

			/**
			 * Sets the confidence which is a value between zero and one.
			 * One stands for the most confidence while zero stands for uncertain.
			 *
			 * @param confidence The confidence to be applied.
			 */
			virtual void set_confidence(double confidence);

			/**
			 * Returns the confidence which is a value between zero and one.
			 * One stands for the most confidence while zero stands for uncertain.
			 *
			 * @return The confidence.
			 */
			virtual double get_confidence();

			/**
			 * Sets the rotation of the bone of which this joint is the end point.
			 * The rotation is in the interval ranges from zero (not rotated) to 360
			 * degrees (one full rotation).
			 *
			 * @param rotation The rotation to be applied.
			 */
			virtual void set_rotation(double rotation);

			/**
			 * Returns the rotation of the bone of which this joint is the end
			 * point. The rotation is in the interval ranges from zero (not rotated) to 360
			 * degrees (one full rotation).
			 *
			 * @return The rotation value.
			 */
			virtual double get_rotation();

			/**
			 * Returns true if this joint equals the given joint.
			 *
			 * @param joint A joint.
			 * @return True if equal.
			 */
			virtual bool equals(general_joint joint) const;

			/**
			 * Returns true if this joint equals the given joint.
			 *
			 * @param joint A joint.
			 * @return True if equal.
			 */
			virtual bool equals(std::shared_ptr<general_joint> joint) const;

			/**
			 * Returns the string representation of this joint.
			 *
			 * @return The string.
			 */
			virtual std::string str() const;

			friend std::ostream& operator<<(std::ostream& os, const general_joint& obj)
			{
				os << obj.str();
				return os;
			}

			friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<general_joint>& obj)
			{
				os << obj->str();
				return os;
			}

		private:
			double x_;
			double y_;
			double z_;

			double confidence_;

			double rotation_;

			bool valid_;

	};

} // namespace mae

#endif // GENERALJOINT_H_
