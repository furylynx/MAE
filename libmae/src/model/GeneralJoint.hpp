/*
 * GeneralJoint.h
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef GENERALJOINT_H_
#define GENERALJOINT_H_

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


			private:
				int x;
				int y;
				int z;

				bool valid;


		};

	} // namespace model
} // namespace mae

#endif // GENERALJOINT_H_
