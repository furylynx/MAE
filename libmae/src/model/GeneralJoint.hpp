/*
 * GeneralJoint.h
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef GENERALJOINT_H_
#define GENERALJOINT_H_

//custom includes

//global includes
#include <iostream>

namespace mae {
	namespace model {

		class GeneralJoint {
			public:
				virtual ~GeneralJoint();
				GeneralJoint();
				GeneralJoint(double x, double y, double z);

				virtual void setX(double x);
				virtual double getX() const;

				virtual void setY(double y);
				virtual double getY() const;

				virtual void setZ(double z);
				virtual double getZ() const;

				virtual void setValid(bool isValid);
				virtual bool isValid() const;


				friend std::ostream& operator<<(std::ostream& os, const GeneralJoint& obj)
				{
					if (!obj.isValid())
					{
						os << "(invalid joint)";
					}
					else
					{
						os << "(" << obj.getX() << ", "<< obj.getY() << ", "<< obj.getZ() << ")";
					}

					return os;
				}

			private:
				double x;
				double y;
				double z;

				bool valid;


		};

	} // namespace model
} // namespace mae

#endif // GENERALJOINT_H_
