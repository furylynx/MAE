/*
 * joint_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef JOINT_PART_HPP_
#define JOINT_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_endpoint.hpp"
#include "e_joint.hpp"

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
						e_joint get_joint();

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_joint joint_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // JOINT_PART_HPP_
