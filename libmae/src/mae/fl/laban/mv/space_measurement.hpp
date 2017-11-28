#ifndef MAE_FL_LABAN_MV_SPACE_MEASUREMENT_HPP_
#define MAE_FL_LABAN_MV_SPACE_MEASUREMENT_HPP_

//custom includes
#include "i_degree_sign.hpp"
#include "e_space.hpp"
#include "e_space_direction.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class space_measurement: public i_degree_sign
				{
					public:
						/**
						 * Creates a space measurement sign. It is not to be confused with the space symbol which
						 * is a symbol that represents a space measurement and therefore contains one.
						 *
						 * @param type The type of the space measurement.
						 * @param degree The degree which is an integer between 1 and 6.
						 * @param direction (optional) The space direction (similiar to the (horizontal) direction of a direction symbol).
						 */
						space_measurement(e_space type, unsigned int degree, e_space_direction direction = e_space_direction::NONE_SPACE_DIRECTION);
						virtual ~space_measurement();

						/**
						 * Returns the type of the space measurement.
						 *
						 * @return The type.
						 */
						e_space get_type() const;

						/**
						 * Returns the degree of the space measurement which is an integer between 1 and 6.
						 *
						 * @return The degree.
						 */
						unsigned int get_degree() const;

						/**
						 * Returns the space direction which is a horizontal direction similar to the (horizontal) direction
						 * of the direction symbols. Returns NONE if this element is not set.
						 *
						 * @return The space direction.
						 */
						e_space_direction get_direction() const;

						/**
						 * Compares this element to the given one and returns true if the elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_degree_sign> a) const;

						/**
						 * Returns true if the signs and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The signs to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_degree_sign> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const;

						/**
						 * Returns the path of the type hierarchy beginning with the i_degree_sign type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
						 *
						 * @return The path from the current type to the i_degree_sign type.
						 */
						virtual std::vector<std::type_index> get_type_path() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "", bool print_type = false) const;

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
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const space_measurement& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<space_measurement>& obj)
						{
							os << obj->str();
							return os;
						}


					private:
						e_space type_;
						unsigned int degree_;
						e_space_direction direction_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_SPACE_MEASUREMENT_HPP_
