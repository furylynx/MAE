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
//...

namespace mae
{
	namespace fl
	{

		enum class area_sign {HEAD, CHEST, WAIST, PELVIS, TORSO};
		enum class joint_sign {SHOULDER, ELBOW, WRIST, HAND, FINGERS, HIP, KNEE, ANKLE, FOOT, TOES};
		enum class digit_sign {THUMB, INDEXFINGER, MIDDLEFINGER, RINGFINGER, LITTLEFINGER, BIGTOE, LONGTOE, MIDDLETOE, RINGTOE, LITTLETOE};
		enum class limb_sign {ARM, LEG, NECK, UPPER_ARM, LOWER_ARM, THIGH, LOWER_LEG };
		enum class surface_sign {OUTER, LITTLEFINGER, THUMB, OUTERLITTLEFINGER, INNERLITTLEFINGER, OUTERTHUMB, INNERTHUMB};


		class laban_column
		{
			public:
				laban_column();
				virtual ~laban_column();

			private:
				int column_index_;

		};

	} // namespace fl
} // namespace mae

#endif // LABAN_COLUMN_HPP_
