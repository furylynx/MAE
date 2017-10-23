#ifndef MAE_FL_LABAN_MV_CANCELLATION_SYMBOL_HPP_
#define MAE_FL_LABAN_MV_CANCELLATION_SYMBOL_HPP_

//custom includes
#include "i_symbol.hpp"
#include "e_cancel.hpp"

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

				class cancellation_symbol : public i_symbol
				{
					public:
						/**
						 * Creates a cancellation symbol.
						 *
						 * @param cancel The cancellation type.
						 */
						cancellation_symbol(e_cancel cancel);
						virtual ~cancellation_symbol();

						/**
						 * Returns the cancellation type.
						 *
						 * @return The cancellation type.
						 */
						e_cancel get_cancel() const;

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

						friend std::ostream& operator<<(std::ostream& os, const cancellation_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<cancellation_symbol>& obj)
						{
							os << obj->str();
							return os;
						}


					private:
						e_cancel cancel_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_CANCELLATION_SYMBOL_HPP_
