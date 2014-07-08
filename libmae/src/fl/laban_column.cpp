/*
 * laban_column.cpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#include "laban_column.hpp"

namespace mae
{
	namespace fl
	{

		laban_column::laban_column(int column_index, pre_sign sign, body_side side)
		{
			column_index_ = column_index;
			pre_sign_ = sign;
			side_ = side;
			digit_joint_ = 99;
			limb_side_ = limb_side::NONE;

			if (!is_area_sign() && !is_joint_sign() && !is_default_limb_sign())
			{
				throw std::invalid_argument("Pre-sign does not identify this column as an area, a joint or a limb but their constructor was chosen.");
			}
		}

		laban_column::laban_column(int column_index, pre_sign sign, body_side side, unsigned int digit_joint)
		{
			column_index_ = column_index;
			pre_sign_ = sign;
			side_ = side;
			digit_joint_ = digit_joint;
			limb_side_ = limb_side::NONE;

			if (! is_digit_sign())
			{
				throw std::invalid_argument("Pre-sign does not identify this column as a digit but digit constructor was chosen.");
			}
		}

		laban_column::laban_column(int column_index, pre_sign sign, body_side side, limb_side lside)
		{
			column_index_ = column_index;
			pre_sign_ = sign;
			side_ = side;
			digit_joint_ = 99;
			limb_side_ = lside;

			if (! is_default_surface_sign())
			{
				throw std::invalid_argument("Pre-sign does not identify this column as a surface but surface constructor was chosen.");
			}
		}

		laban_column::~laban_column()
		{

		}

		int laban_column::get_column_index()
		{
			return column_index_;
		}

		pre_sign laban_column::get_pre_sign()
		{
			return pre_sign_;
		}

		body_side laban_column::get_side()
		{
			return side_;
		}

		unsigned int laban_column::get_digit_joint()
		{
			return digit_joint_;
		}

		bool laban_column::is_area_sign()
		{
			if (pre_sign_ == pre_sign::AREA_HEAD || pre_sign_ == pre_sign::AREA_CHEST
					|| pre_sign_ == pre_sign::AREA_WAIST || pre_sign_ == pre_sign::AREA_PELVIS
					|| pre_sign_ == pre_sign::AREA_TORSO)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool laban_column::is_joint_sign()
		{
			if (pre_sign_ == pre_sign::JOINT_SHOULDER || pre_sign_ == pre_sign::JOINT_ELBOW
					|| pre_sign_ == pre_sign::JOINT_WRIST || pre_sign_ == pre_sign::JOINT_HAND
					|| pre_sign_ == pre_sign::JOINT_FINGERS || pre_sign_ == pre_sign::JOINT_HIP
					|| pre_sign_ == pre_sign::JOINT_KNEE || pre_sign_ == pre_sign::JOINT_ANKLE
					|| pre_sign_ == pre_sign::JOINT_FOOT || pre_sign_ == pre_sign::JOINT_TOES)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool laban_column::is_digit_sign()
		{
			if (pre_sign_ == pre_sign::DIGIT_THUMB || pre_sign_ == pre_sign::DIGIT_INDEXFINGER
					|| pre_sign_ == pre_sign::DIGIT_MIDDLEFINGER || pre_sign_ == pre_sign::DIGIT_RINGFINGER
					|| pre_sign_ == pre_sign::DIGIT_LITTLEFINGER || pre_sign_ == pre_sign::DIGIT_BIGTOE
					|| pre_sign_ == pre_sign::DIGIT_LONGTOE || pre_sign_ == pre_sign::DIGIT_MIDDLETOE
					|| pre_sign_ == pre_sign::DIGIT_RINGTOE || pre_sign_ == pre_sign::DIGIT_LITTLETOE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool laban_column::is_default_limb_sign()
		{
			if (pre_sign_ == pre_sign::LIMB_ARM || pre_sign_ == pre_sign::LIMB_LEG || pre_sign_ == pre_sign::LIMB_NECK
					|| pre_sign_ == pre_sign::LIMB_UPPER_ARM || pre_sign_ == pre_sign::LIMB_LOWER_ARM
					|| pre_sign_ == pre_sign::LIMB_THIGH || pre_sign_ == pre_sign::LIMB_LOWER_LEG)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool laban_column::is_default_surface_sign()
		{

			if (limb_side_ == limb_side::OUTER || limb_side_ == limb_side::LITTLEFINGER
					|| limb_side_ == limb_side::THUMB || limb_side_ == limb_side::OUTERLITTLEFINGER
					|| limb_side_ == limb_side::INNERLITTLEFINGER || limb_side_ == limb_side::OUTERTHUMB
					|| limb_side_ == limb_side::INNERTHUMB)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		std::string laban_column::xml(unsigned int indent)
		{
			std::stringstream indent_stream;

			for (unsigned int i = 0; i < indent; i++)
			{
				indent_stream << "\t";
			}

			std::stringstream sstr;

			//print definition
			sstr << indent_stream.str() << "<columnDefinition>" << std::endl;

			sstr << indent_stream.str() << "\t" << "<index>" << column_index_ << "</index>" << std::endl;

			//print pre sign
			sstr << indent_stream.str() << "\t" << "<preSign>" << std::endl;

			if (is_area_sign())
			{
				//print area sign
				sstr << indent_stream.str() << "\t\t" << "<bodyPart>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<part>" << pre_sign_str[(int)pre_sign_] << "</part>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<side>" << body_side_str[(int)side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "</bodyPart>" << std::endl;
			}
			else if (is_joint_sign())
			{
				//print joint sign
				sstr << indent_stream.str() << "\t\t" << "<bodyPart>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<joint>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<joint>" << pre_sign_str[(int)pre_sign_] << "</joint>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<side>" << body_side_str[(int)side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "</joint>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "</bodyPart>" << std::endl;
			}
			else if (is_digit_sign())
			{
				//print digit sign
				sstr << indent_stream.str() << "\t\t" << "<bodyPart>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<digit>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<digit>" << pre_sign_str[(int)pre_sign_] << "</digit>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<joint>" << digit_joint_ << "</joint>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "</digit>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<side>" << body_side_str[(int)side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "</bodyPart>" << std::endl;
			}
			else if (is_default_limb_sign())
			{
				//print digit sign
				sstr << indent_stream.str() << "\t\t" << "<bodyPart>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<default>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t\t" << "<limb>" << pre_sign_str[(int)pre_sign_] << "</limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "</default>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "</limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<side>" << body_side_str[(int)side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "</bodyPart>" << std::endl;
			}
			else if (is_default_surface_sign())
			{
				//print digit sign
				sstr << indent_stream.str() << "\t\t" << "<bodyPart>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<surface>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t\t" << "<default>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t\t\t" << "<limb>" << pre_sign_str[(int)pre_sign_] << "</limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t\t" << "</default>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "</limb>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t\t" << "<side>" << limb_side_str[(int)limb_side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "</surface>" << std::endl;
				sstr << indent_stream.str() << "\t\t\t" << "<side>" << body_side_str[(int)side_] << "</side>" << std::endl;
				sstr << indent_stream.str() << "\t\t" << "</bodyPart>" << std::endl;
			}

			sstr << indent_stream.str() << "\t" << "</preSign>" << std::endl;

			sstr << indent_stream.str() << "</columnDefinition>" << std::endl;

			return sstr.str();
		}

	} // namespace fl
} // namespace mae
