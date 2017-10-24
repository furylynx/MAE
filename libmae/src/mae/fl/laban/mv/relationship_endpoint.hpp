#ifndef MAE_FL_LABAN_MV_RELATIONSHIP_ENDPOINT_HPP_
#define MAE_FL_LABAN_MV_RELATIONSHIP_ENDPOINT_HPP_

//custom includes
#include "../ps/i_pre_sign.hpp"
#include "i_dynamics_sign.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <map>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class relationship_endpoint
				{
					public:
						/**
						 * Creates a new relationship end point.
						 *
						 * @param column The column to which this point is attached.
						 * @param active True for active.
						 * @param pre_sign The pre sign for this end point.
						 * @param dynamics The dynamics sign.
						 */
						relationship_endpoint(int column, bool active, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~relationship_endpoint();

						/**
						 * Returns the column to which this end point is attached.
						 *
						 * @return The column.
						 */
						int get_column() const;

						/**
						 * Returns the pre sign for this symbol.
						 *
						 * @return The pre sign.
						 */
						std::shared_ptr<ps::i_pre_sign> get_pre_sign() const;

						/**
						 * Returns the dynamics sign for this symbol.
						 *
						 * @return The dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						/**
						 * Returns true if this end point is active. False otherwise.
						 *
						 * @return True for active.
						 */
						bool get_active() const;

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
						 * Recreates the element using the column mapping for the new columns.
						 *
						 * @param column_mapping
						 * @return The new endpoint.
						 */
						virtual std::shared_ptr<relationship_endpoint> recreate(std::map<int, int> column_mapping) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<relationship_endpoint> a) const;

						/**
						 * Returns the feature vector for the endpoint.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const;

					private:
						int column_;
						std::shared_ptr<ps::i_pre_sign> pre_sign_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						bool active_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_RELATIONSHIP_ENDPOINT_HPP_
