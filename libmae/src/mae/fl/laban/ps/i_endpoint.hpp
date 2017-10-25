#ifndef MAE_FL_LABAN_PS_I_ENDPOINT_HPP_
#define MAE_FL_LABAN_PS_I_ENDPOINT_HPP_

//custom includes
#include "i_part.hpp"

//global includes
#include <string>
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

				class i_endpoint: public i_part
				{
					public:
						virtual ~i_endpoint(){}

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
						 * Returns the predecessor of the current endpoint (which is the default fixed endpoint). If the endpoint is the beginning of the extremity null is returned.
						 *
						 * @return The successor element.
						 */
						virtual std::shared_ptr<i_endpoint> get_fixed_end() const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_endpoint> a) const  = 0;

						/**
						 * Returns the feature vector for the part.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_I_ENDPOINT_HPP_
