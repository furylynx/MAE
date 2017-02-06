/*
 * i_degree_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_DEGREE_SIGN_HPP_
#define I_DEGREE_SIGN_HPP_

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

				class i_degree_sign
				{
					public:
						virtual ~i_degree_sign(){}

						/**
						 * Returns true if the signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_degree_sign> a) const = 0;

						/**
						 * Returns the XML representation for this sign.
						 *
						 * @param indent The indent to be applied.
						 * @param namesp The namespace to be applied.
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "", bool print_type = false) const = 0;

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
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DEGREE_SIGN_HPP_
