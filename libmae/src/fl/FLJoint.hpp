/*
 * FLJoint.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLJOINT_HPP_
#define FLJOINT_HPP_

namespace mae {
	namespace fl {

		class FLJoint {
			public:
				FLJoint();
				FLJoint(double phi, double theta);
				virtual ~FLJoint();

				virtual void setPhi(double x);
				virtual double getPhi() const;

				virtual void setTheta(double x);
				virtual double getTheta() const;

				virtual void setValid(bool isValid);
				virtual bool isValid() const;

			private:
				double theta;
				double phi;

				bool valid;
		};

	} // namespace fl
} // namespace mae

#endif // FLJOINT_HPP_
