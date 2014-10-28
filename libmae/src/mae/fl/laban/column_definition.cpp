/*
 * laban_column.cpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#include "column_definition.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			column_definition::column_definition(int column_index, std::shared_ptr<ps::i_pre_sign> pre_sign)
			{
				column_index_ = column_index;
				pre_sign_ = pre_sign;

				if (column_index == -4 || column_index == -2 || column_index == -1 || column_index == 1
						|| column_index == 2 || column_index == 4)
				{
					throw std::invalid_argument("Default columns must not be overridden.");
				}

				if (column_index == 0)
				{
					throw std::invalid_argument("Column index must not be zero.");
				}

				if (pre_sign == nullptr)
				{
					throw std::invalid_argument("Pre-sign must not be null.");
				}
			}

			column_definition::column_definition(mae::e_bone eb)
			{
				bone b = bone(eb);
				column_index_ = b.get_id();

				ps::e_side side = ps::e_side::NONE_SIDE;

				if (
						eb == mae::e_bone::LEFT_UPPER_ARM 	||
						eb == mae::e_bone::LEFT_FOREARM 	||
						eb == mae::e_bone::LEFT_WHOLE_ARM   ||
						eb == mae::e_bone::LEFT_THIGH 		||
						eb == mae::e_bone::LEFT_SHANK 		||
						eb == mae::e_bone::LEFT_WHOLE_LEG
					)
				{
					side = ps::e_side::LEFT;
				}
				else if (
						eb == mae::e_bone::RIGHT_UPPER_ARM 	||
						eb == mae::e_bone::RIGHT_FOREARM 	||
						eb == mae::e_bone::RIGHT_WHOLE_ARM   ||
						eb == mae::e_bone::RIGHT_THIGH 		||
						eb == mae::e_bone::RIGHT_SHANK 		||
						eb == mae::e_bone::RIGHT_WHOLE_LEG)
				{
					side = ps::e_side::RIGHT;
				}

				//find the part
				std::shared_ptr<ps::i_part> part;

				if (eb == e_bone::HEAD)
				{
					part = std::shared_ptr<ps::i_part>(new ps::area_part(ps::e_area::HEAD));
				}
				else
				{
					ps::e_limb limb;
					if (eb == e_bone::LEFT_WHOLE_ARM || eb == e_bone::RIGHT_WHOLE_ARM)
					{
						limb = ps::e_limb::ARM;
					}
					else if (eb == e_bone::LEFT_WHOLE_LEG || eb == e_bone::RIGHT_WHOLE_LEG)
					{
						limb = ps::e_limb::LEG;
					}
					else if (eb == e_bone::LEFT_UPPER_ARM || eb == e_bone::RIGHT_UPPER_ARM)
					{
						limb = ps::e_limb::UPPER_ARM;
					}
					else if (eb == e_bone::LEFT_FOREARM || eb == e_bone::RIGHT_FOREARM)
					{
						limb = ps::e_limb::LOWER_ARM;
					}
					else if (eb == e_bone::LEFT_THIGH || eb == e_bone::RIGHT_THIGH)
					{
						limb = ps::e_limb::THIGH;
					}
					else if (eb == e_bone::LEFT_SHANK || eb == e_bone::RIGHT_SHANK)
					{
						limb = ps::e_limb::LOWER_LEG;
					}
					else
					{
						throw std::invalid_argument("The given e_bone value is unknown.");
					}

					part = std::shared_ptr<ps::i_part>(new ps::default_limb(limb));
				}

				pre_sign_ = std::shared_ptr<ps::body_part>(new ps::body_part(side, part));
			}

			column_definition::~column_definition()
			{

			}

			int column_definition::get_column_index() const
			{
				return column_index_;
			}

			std::shared_ptr<ps::i_pre_sign> column_definition::get_pre_sign() const
			{
				return pre_sign_;
			}

			std::string column_definition::xml(unsigned int indent, std::string namesp) const
			{
				std::stringstream indent_stream;

				for (unsigned int i = 0; i < indent; i++)
				{
					indent_stream << "\t";
				}

				std::string ns = namesp;
				if (ns.size() > 0 && ns.at(ns.size() - 1) != ':')
				{
					ns.push_back(':');
				}

				std::stringstream sstr;

				//print definition
				sstr << indent_stream.str() << "<" << ns << "columnDefinition>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "index>" << column_index_ << "</" << ns << "index>"
						<< std::endl;

				//print pre sign
				sstr << pre_sign_->xml(indent + 1, namesp);

				sstr << indent_stream.str() << "</" << ns << "columnDefinition>" << std::endl;

				return sstr.str();
			}

			std::string column_definition::svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const
			{
				std::stringstream sstr;

				double column_width = (im_width)/(max_column * 2.0);

				double draw_w = column_width / 2.0;
				double draw_x_pos = (im_width / 2.0) + ((column_index_ - (mae::math::math::sign(column_index_)*0.5) - 0.25)*column_width);

				double draw_y_pos = im_height*0.9;
				double draw_h = im_height*0.1;

				std::stringstream id_sstr;
				id_sstr << "column-definition-" << column_index_;
				std::string identifier = id_sstr.str();

				sstr << pre_sign_->svg(identifier, draw_x_pos, draw_y_pos, draw_w, draw_h, (column_index_ < 0));

				return sstr.str();
			}

			bool column_definition::equals(std::shared_ptr<column_definition> a) const
			{
				return (column_index_ == a->get_column_index() && pre_sign_->equals(a->get_pre_sign()));
			}

			std::vector<std::shared_ptr<column_definition> > column_definition::default_definitions()
			{
				std::vector<std::shared_ptr<column_definition> > result;

				std::vector<mae::e_bone> ebones = mae::e_bone_c::vec();

				for (unsigned int i = 0; i < ebones.size(); i++)
				{
					if (std::abs(mae::e_bone_c::to_int(ebones.at(i))) > 2 && std::abs(mae::e_bone_c::to_int(ebones.at(i))) != 4)
					{
						result.push_back(std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(ebones.at(i))));
					}
				}

				return result;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
