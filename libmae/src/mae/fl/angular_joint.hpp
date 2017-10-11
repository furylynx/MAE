#ifndef MAE_FL_FLJOINT_HPP_
#define MAE_FL_FLJOINT_HPP_


//custom includes
//...

//global includes
#include <iostream>
#include <memory>


namespace mae
{
	namespace fl
	{

		class angular_joint
		{
			public:
				/**
				 * Creates a new invalid joint.
				 */
				angular_joint();

				/**
				 * Creates a new joint with the values set.
				 *
				 * @param phi The elevation phi.
				 * @param theta The azimuth theta.
				 * @param confidence The confidence (a value between zero and one, where one is the most confident).
				 */
				angular_joint(double phi, double theta, double confidence = 1.0);

				virtual ~angular_joint();

				/**
				 * Sets the value for phi.
				 *
				 * @param x The value.
				 */
				virtual void set_phi(double x);

				/**
				 * Returns the value for phi.
				 *
				 * @return The value.
				 */
				virtual double get_phi() const;

				/**
				 * Sets the value for theta.
				 *
				 * @param x The value.
				 */
				virtual void set_theta(double x);
				/**
				 * Returns the value for theta.
				 *
				 * @return The value.
				 */
				virtual double get_theta() const;

				/**
				 * Sets the validity of this joint.
				 *
				 * @param isValid The validity.
				 */
				virtual void set_valid(bool isValid);

				/**
				 * Returns the validity of this joint.
				 *
				 * @return True if valid.
				 */
				virtual bool is_valid() const;

				/**
				 * Sets the confidence for this joint which is a value between zero and one, where one is the most confident.
				 *
				 * @param confidence The confidence.
				 */
				virtual void set_confidence(double confidence);

				/**
				 * Returns the confidence for this joint which is a value between zero and one, where one is the most confident.
				 */
				virtual double get_confidence() const;

				friend std::ostream& operator<<(std::ostream& os, const angular_joint& obj)
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

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<angular_joint>& obj)
				{
					os << *obj;
					return os;
				}

			private:
				double theta_;
				double phi_;

				double confidence_;

				bool valid_;
		};

	} // namespace fl
} // namespace mae

#endif // MAE_FL_FLJOINT_HPP_
