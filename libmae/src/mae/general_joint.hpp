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
			 * Creates a general joint.
			 */
			general_joint();

			/**
			 * Creates a general joint with values set.
			 *
			 * @param x The x-coordinate.
			 * @param y The y-coordinate.
			 * @param z The z-coordinate.
			 */
			general_joint(double x, double y, double z);

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
			double x;
			double y;
			double z;

			bool valid;

	};

} // namespace mae

#endif // GENERALJOINT_H_
