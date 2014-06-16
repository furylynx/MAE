/*
 * GeneralJoint.h
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef GENERALJOINT_H_
#define GENERALJOINT_H_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <iostream>
#include <sstream>
#include <memory>

namespace mae
{
	namespace model
	{

		class GeneralJoint
		{
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

				virtual std::string str() const;

				friend std::ostream& operator<<(std::ostream& os, const GeneralJoint& obj)
				{
					os << obj.str();
					return os;
				}

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<GeneralJoint>& obj)
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

	} // namespace model
} // namespace mae

#endif // GENERALJOINT_H_
