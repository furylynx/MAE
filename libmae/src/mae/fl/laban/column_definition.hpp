/*
 * laban_column.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef MAE_FL_LABAN_COLUMN_DEFINITION_HPP_
#define MAE_FL_LABAN_COLUMN_DEFINITION_HPP_

//custom includes
#include "../../e_bone.hpp"
#include "../../bone.hpp"

#include "../../math/math.hpp"

#include "ps/i_pre_sign.hpp"
#include "ps/area_part.hpp"
#include "ps/default_limb.hpp"
#include "ps/body_part.hpp"
#include "ps/digit_part.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

		class column_definition
		{
			public:
				/**
				 * Creates a new column definition.
				 *
				 * @param column_index The index of the column.
				 * @param pre_sign The pre-sign.
				 */
				column_definition(int column_index, std::shared_ptr<ps::i_pre_sign> pre_sign);

				/**
				 * Creates a new column definition for the given e_bone enum value.
				 *
				 * @param eb The bone enum value.
				 */
				column_definition(mae::e_bone eb);

                /**
                 * Creates a new column definition for the given e_hand_bone enum value.
                 *
                 * @param ehb The hand bone enum value.
                 */
                column_definition(mae::e_hand_bone ehb);

				virtual ~column_definition();

				/**
				 * Returns the column index. This specifies the addressed column in the chart.
				 *
				 * @return
				 */
				int get_column_index() const;

				/**
				 * Returns the pre-sign.
				 *
				 * @return
				 */
				std::shared_ptr<ps::i_pre_sign> get_pre_sign() const;

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
				 * Returns the SVG representation for this element.
				 *
				 * @param posx The x pos.
				 * @param posy The y pos.
				 * @param width The width.
				 * @param height The height.
				 * @return The SVG.
				 */
				virtual std::string svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const;

				/**
				 * Returns true if signs are equal.
				 *
				 * @param a The sign to be compared to.
				 * @return True if equal.
				 */
				virtual bool equals(std::shared_ptr<column_definition> a) const;

				/**
				 * Returns the default column definitions.
				 *
				 * @return The default column definitions.
				 */
				static std::vector<std::shared_ptr<column_definition> > default_definitions();

                /**
                 * Returns the default hand column definitions.
                 *
                 * @param is_left True for left hand. False otherwise.
                 * @return The default column definitions.
                 */
                static std::vector<std::shared_ptr<column_definition> > default_hand_definitions(bool is_left);

			private:
				int column_index_;
				std::shared_ptr<ps::i_pre_sign> pre_sign_;

				static std::vector<std::shared_ptr<column_definition> > default_definitions_;
				static std::vector<std::shared_ptr<column_definition> > default_hand_definitions_;


		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_COLUMN_DEFINITION_HPP_
