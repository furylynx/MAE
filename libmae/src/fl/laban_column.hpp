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
		     				 };

		enum class side {
				NONE,
				LEFT,
				RIGHT,
				SURFACE_OUTER,
				SURFACE_LITTLEFINGER,
				SURFACE_THUMB,
				SURFACE_OUTERLITTLEFINGER,
				SURFACE_INNERLITTLEFINGER,
				SURFACE_OUTERTHUMB,
				SURFACE_INNERTHUMB
		};

		class laban_column
		{
			public:
				laban_column();
				virtual ~laban_column();

			private:
				int column_index_;
				pre_sign pre_sign_;
				side side_;
				unsigned int digit_joint;//0-4 for a digit pre-sign

				//TODO custom limb

		};

	} // namespace fl
} // namespace mae

#endif // LABAN_COLUMN_HPP_
