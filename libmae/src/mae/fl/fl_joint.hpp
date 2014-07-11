/*
 * FLJoint.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLJOINT_HPP_
#define FLJOINT_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <iostream>
#include <memory>

namespace mae {
	namespace fl {

		class fl_joint {
			public:
				fl_joint();
				fl_joint(double phi, double theta);
				virtual ~fl_joint();

				virtual void set_phi(double x);
				virtual double get_phi() const;

				virtual void set_theta(double x);
				virtual double get_theta() const;

				virtual void set_valid(bool isValid);
				virtual bool is_valid() const;

				friend std::ostream& operator<<(std::ostream& os, const fl_joint& obj)
				{
					if (!obj.is_valid())
					{
						os << "(invalid joint)";
					}
					else
					{
						os << "(phi = " << obj.get_phi() << "° , theta = " << obj.get_theta() << "°)";
					}

					return os;
				}

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<fl_joint>& obj)
				{
					os << *obj;
					return os;
				}

			private:
				double theta_;
				double phi_;

				bool valid_;
		};

	} // namespace fl
} // namespace mae

#endif // FLJOINT_HPP_
