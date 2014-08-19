/*
 * i_dynamics_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_DYNAMICS_SIGN_HPP_
#define I_DYNAMICS_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

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
			namespace mv
			{

				class i_dynamics_sign
				{
					public:
						virtual ~i_dynamics_sign(){}

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_dynamics_sign> a);

						/**
						 * Returns the xml string representation for the sign.
						 *
						 * @param indent The applied indent.
						 * @param namesp The namespace if any.
						 * @return The xml string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") = 0;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DYNAMICS_SIGN_HPP_
