#ifndef MAE_FL_LABAN_PS_DIGIT_PART_HPP_
#define MAE_FL_LABAN_PS_DIGIT_PART_HPP_

//custom includes
#include "i_endpoint.hpp"
#include "e_digit.hpp"
#include "joint_part.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class digit_part: public i_endpoint
				{
					public:
						/**
						 * Creates a digit pre-sign which consist of a digit (finger or toes) and a knuckle.
						 *
						 * @param digit The addressed digit.
						 * @param knuckle The addressed knuckle. Zero represents the whole digit, whereas
						 * 					A number represents the knuckle counted from the base. Therefore
						 * 					3 for toes and 4 for fingers is the maximum valid value.
						 */
						digit_part(e_digit digit, unsigned int knuckle);
						virtual ~digit_part();

						/**
						 * Returns the addressed digit.
						 *
						 * @return
						 */
						e_digit get_digit() const;

						/**
						 * Returns the addressed knuckle. Zero represents the whole digit whereas a number
						 * represents the knuckle counted from the base.
						 *
						 * @return
						 */
						unsigned int get_knuckle() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

						/**
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const;

						/**
						 * Returns the predecessor of the current endpoint (which is the default fixed endpoint).
						 * If the endpoint is the beginning of the extremity null is returned.
						 *
						 * If the base knuckle is zero, the hand or foot (joint part) is returned.
						 *
						 * @return The successor element.
						 */
						virtual std::shared_ptr<i_endpoint> get_fixed_end() const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_endpoint> a) const;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_endpoint> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const;

					private:
						e_digit digit_;
						unsigned int knuckle_;

						virtual std::string svg_str_dot(std::string identifier, double centerx, double centery, double radius, bool left, double mirrorpos) const;

                        virtual std::string svg_for_finger(const std::string &identifier, double posx, double posy, double width, double height, bool left) const;
                        virtual std::string svg_for_toe(const std::string &identifier, double posx, double posy, double width, double height, bool left) const;

                        virtual int get_digit_increment() const;
                };

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_DIGIT_PART_HPP_
