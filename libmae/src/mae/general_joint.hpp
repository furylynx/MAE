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
			general_joint();
			general_joint(double x, double y, double z);

			virtual void set_x(double x);
			virtual double get_x() const;

			virtual void set_y(double y);
			virtual double get_y() const;

			virtual void set_z(double z);
			virtual double get_z() const;

			virtual void set_valid(bool isValid);
			virtual bool is_valid() const;

			virtual bool equals(general_joint joint) const;
			virtual bool equals(std::shared_ptr<general_joint> joint) const;

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
