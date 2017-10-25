#ifndef MAE_FL_LABAN_PS_AREA_PART_HPP_
#define MAE_FL_LABAN_PS_AREA_PART_HPP_

//custom includes
#include "i_endpoint.hpp"
#include "e_area.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class area_part: public i_endpoint
				{
					public:
						/**
						 * Creates a new area pre-sign.
						 *
						 * @param area The addressed area.
						 */
						area_part(e_area area);
						virtual ~area_part();

						/**
						 * Returns the addressed area.
						 *
						 * @return
						 */
						e_area get_area() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "")  const;

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
						 * Returns the successor of the current endpoint (which is the default extremity endpoint). If the endpoint is the end of the extremity null is returned.
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
						 * Returns the feature vector for the symbol.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const;

					private:
						e_area area_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_AREA_PART_HPP_
