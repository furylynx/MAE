#ifndef MAE_FL_LABAN_MV_TURN_SYMBOL_HPP_
#define MAE_FL_LABAN_MV_TURN_SYMBOL_HPP_

//custom includes
#include "i_symbol.hpp"
#include "i_degree_sign.hpp"
#include "i_dynamics_sign.hpp"
#include "e_turn_direction.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class turn_symbol: public i_symbol
				{
					public:
						/**
						 * Returns a turn symbol.
						 *
						 * @param direction The direction of the turn.
						 * @param dynamics (optional) An attached dynamics sign. Use null if unused and degree is required.
						 * @param degree (optional) The degree of the turn
						 */
						turn_symbol(e_turn_direction direction, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<i_degree_sign> degree = nullptr);
						virtual ~turn_symbol();

						/**
						 * Return the direction of the turn.
						 *
						 * @return The direction.
						 */
						e_turn_direction get_direction() const;

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return The dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						/**
						 * Returns the degree of the turn if set. Returns null otherwise.
						 *
						 * @return The degree sign.
						 */
						std::shared_ptr<i_degree_sign> get_degree() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_symbol> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const;

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
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const turn_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<turn_symbol>& obj)
						{
							os << obj->str();
							return os;
						}

					private:
						e_turn_direction direction_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<i_degree_sign> degree_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_TURN_SYMBOL_HPP_
