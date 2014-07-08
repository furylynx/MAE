/*
 * laban_column.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef LABAN_COLUMN_HPP_
#define LABAN_COLUMN_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <sstream>
#include <type_traits>
#include <stdexcept>

namespace mae
{
	namespace fl
	{

		enum class pre_sign {AREA_HEAD,
		                     AREA_CHEST,
		                     AREA_WAIST,
		                     AREA_PELVIS,
		                     AREA_TORSO,
		                     JOINT_SHOULDER,
                             JOINT_ELBOW,
                             JOINT_WRIST,
                             JOINT_HAND,
                             JOINT_FINGERS,
                             JOINT_HIP,
                             JOINT_KNEE,
		                     JOINT_ANKLE,
		                     JOINT_FOOT,
		                     JOINT_TOES,
		                     DIGIT_THUMB,
		                     DIGIT_INDEXFINGER,
		                     DIGIT_MIDDLEFINGER,
		                     DIGIT_RINGFINGER,
		                     DIGIT_LITTLEFINGER,
		                     DIGIT_BIGTOE,
		                     DIGIT_LONGTOE,
		                     DIGIT_MIDDLETOE,
		                     DIGIT_RINGTOE,
		                     DIGIT_LITTLETOE,
		                     LIMB_ARM,
		     				 LIMB_LEG,
		     				 LIMB_NECK,
		     				 LIMB_UPPER_ARM,
		     				 LIMB_LOWER_ARM,
		     				 LIMB_THIGH,
		     				 LIMB_LOWER_LEG,
		     				 SIZE
		     				 };
		static const char* pre_sign_str[(int) pre_sign::SIZE] = {
				"head",
				"chest",
				"waist",
				"pelvis",
				"torso",
				"shoulder",
				"elbow",
				"wrist",
				"hand",
				"fingers",
				"hip",
				"knee",
				"ankle",
				"foot",
				"toes",
				"thumb",
				"indexFinger",
				"middleFinger",
				"ringFinger",
				"littleFinger",
				"bigToe",
				"longToe",
				"middleToe",
				"ringToe",
				"littleToe",
				"arm",
				"leg",
				"neck",
				"upper_arm",
				"lower_arm",
				"thigh",
				"lower_leg",
		};

		enum class body_side {
				NONE,
				LEFT,
				RIGHT,
				SIZE
		};
		static const char* body_side_str[(int) body_side::SIZE] = {
				"none",
				"left",
				"right",
		};

		enum class limb_side {
				NONE,
				INNER,
				OUTER,
				LITTLEFINGER,
				THUMB,
				OUTERLITTLEFINGER,
				INNERLITTLEFINGER,
				OUTERTHUMB,
				INNERTHUMB,
				SIZE
		};
		static const char* limb_side_str[(int) limb_side::SIZE] = {
						"none",
						"inner",
						"outer",
						"littleFinger",
						"thumb",
						"outer-littleFinger",
						"inner-littleFinger",
						"outer-thumb",
						"inner-thumb"
		};

		class laban_column
		{
			public:

				/**
				 * Creates a new columns definition for either an area, a joint or a (default) limb.
				 * @param column_index
				 * @param sign
				 * @param side
				 */
				laban_column(int column_index, pre_sign sign, body_side side);

				/**
				 * Creates a new column definition for a digit pre-sign.
				 *
				 * @param column_index The column index.
				 * @param sign The sign.
				 * @param side The body side.
				 * @param digit_joint The digit joint number.
				 * 				0 represents the digit as a whole.
				 *				1 represents the base knuckle.
				 *				2 represents the first knuckle following the base.
				 *				3 represents the second knuckle for fingers and the tip for toes.
				 *				4 represents the tip for fingers.
				 */
				laban_column(int column_index, pre_sign sign, body_side side, unsigned int digit_joint);

				/**
				 * Creates a new column definition for a (default) surface pre-sign.
				 *
				 * @param column_index The column index.
				 * @param sign The sign.
				 * @param side The body side.
				 * @param lside The limb side.
				 */
				laban_column(int column_index, pre_sign sign, body_side side, limb_side lside);

				virtual ~laban_column();

				/**
				 * Returns the column index. This specifies the addressed column in the chart.
				 *
				 * @return
				 */
				int get_column_index();

				/**
				 * Returns the pre-sign.
				 *
				 * @return
				 */
				pre_sign get_pre_sign();

				/**
				 * Returns the addressed side. The side depends on the pre sign and can
				 * either specify the left or the right body side or it denotes the surface
				 * side.
				 *
				 * @return The side.
				 */
				body_side get_side();

				/**
				 * Returns the number identifying the addressed knuckle of the digit.
				 *
				 * @return The knuckle of the digit.
				 */
				unsigned int get_digit_joint();


				/**
				 * Returns true if the column has an area pre-sign.
				 *
				 * @return
				 */
				bool is_area_sign();

				/**
				 * Returns true if the column has a joint pre-sign.
				 * @return
				 */
				bool is_joint_sign();

				/**
				 * Returns true if the column has a digit pre-sign.
				 *
				 * @return
				 */
				bool is_digit_sign();

				/**
				 * Returns true if the column has a (default) limb pre-sign.
				 *
				 * @return
				 */
				bool is_default_limb_sign();

				/**
				 * Returns true if the column has a (default) surface pre-sign.
				 *
				 * @return
				 */
				bool is_default_surface_sign();

				/**
				 * Prints the xml representation for this element to a string.
				 *
				 * @param indent The number of tab indent.
				 * @return The xml string.
				 */
				virtual std::string xml(unsigned int indent = 3);

			private:
				int column_index_;
				pre_sign pre_sign_;
				body_side side_;
				unsigned int digit_joint_;//0-4 for a digit pre-sign
				limb_side limb_side_;


				//TODO custom limb
				//TODO custom surface

				//TODO prop pre-sign

		};

	} // namespace fl
} // namespace mae

#endif // LABAN_COLUMN_HPP_
