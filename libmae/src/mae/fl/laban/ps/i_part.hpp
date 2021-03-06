#ifndef MAE_FL_LABAN_PS_I_PART_HPP_
#define MAE_FL_LABAN_PS_I_PART_HPP_

//custom includes
//...

//global includes
#include <string>
#include <memory>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class i_part
				{
					public:
						virtual ~i_part(){}

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const = 0;

						/**
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_I_PART_HPP_
