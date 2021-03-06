#ifndef MAE_FL_LABAN_PS_JOINT_PART_HPP_
#define MAE_FL_LABAN_PS_JOINT_PART_HPP_

//custom includes
#include "i_endpoint.hpp"
#include "e_joint.hpp"

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
			namespace ps
			{

				class joint_part: public i_endpoint
				{
					public:
						/**
						 * Creates a joint part used for a pre-sign.
						 *
						 * @param joint The addressed joint.
						 */
						joint_part(e_joint joint);
						virtual ~joint_part();

						/**
						 * Returns the addressed joint.
						 * @return
						 */
						e_joint get_joint() const;

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
						 * Returns the predecessor of the current endpoint (which is the default fixed endpoint). If the endpoint is the beginning of the extremity null is returned.
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

					private:
						e_joint joint_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_JOINT_PART_HPP_
