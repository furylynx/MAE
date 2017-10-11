#include "column_definition.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			std::vector<std::shared_ptr<column_definition> > column_definition::default_definitions_ = std::vector<std::shared_ptr<column_definition> >();
			std::vector<std::shared_ptr<column_definition> > column_definition::default_hand_definitions_ = std::vector<std::shared_ptr<column_definition> >();

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

            column_definition::column_definition(mae::e_hand_bone ehb)
            {
                bone b = bone(ehb);
                column_index_ = b.get_id();

                ps::e_side side = ps::e_side::NONE_SIDE;

                if (mae::e_hand_bone_c::is_left(ehb))
                {
                    side = ps::e_side::LEFT;
                }
                else if (mae::e_hand_bone_c::is_right(ehb))
                {
                    side = ps::e_side::RIGHT;
                }

                //find the part
                std::shared_ptr<ps::i_part> part;

                ps::e_digit digit;
                int knuckle = 0;

                //find digit
                if (ehb == e_hand_bone::LEFT_THUMB || ehb == e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_THUMB_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_THUMB || ehb == e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX)
                {
                    digit = ps::e_digit::THUMB;
                }
                else if (ehb == e_hand_bone::LEFT_INDEX_FINGER  || ehb == e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER  || ehb == e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX)
                {
                    digit = ps::e_digit::INDEXFINGER;
                }
                else if (ehb == e_hand_bone::LEFT_MIDDLE_FINGER  || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER  || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX)
                {
                    digit = ps::e_digit::MIDDLEFINGER;
                }
                else if (ehb == e_hand_bone::LEFT_RING_FINGER  || ehb == e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER  || ehb == e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX)
                {
                    digit = ps::e_digit::RINGFINGER;
                }
                else if (ehb == e_hand_bone::LEFT_LITTLE_FINGER  || ehb == e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_LITTLE_FINGER  || ehb == e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX)
                {
                    digit = ps::e_digit::LITTLEFINGER;
                }
                else
                {
                    throw std::invalid_argument("The given e_bone value is unknown.");
                }

                //find knuckle
                if (ehb == e_hand_bone::LEFT_THUMB || ehb == e_hand_bone::LEFT_INDEX_FINGER || ehb == e_hand_bone::LEFT_MIDDLE_FINGER || ehb == e_hand_bone::LEFT_RING_FINGER || ehb == e_hand_bone::LEFT_LITTLE_FINGER || ehb == e_hand_bone::RIGHT_THUMB || ehb == e_hand_bone::RIGHT_INDEX_FINGER || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER || ehb == e_hand_bone::RIGHT_RING_FINGER || ehb == e_hand_bone::RIGHT_LITTLE_FINGER)
                {
                    knuckle = 0;
                }
                else if (ehb == e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX|| ehb == e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX|| ehb == e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX)
                {
                    knuckle = 2;
                }
                else if (ehb == e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX|| ehb == e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX|| ehb == e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX)
                {
                    knuckle = 3;
                }
                else if (ehb == e_hand_bone::LEFT_THUMB_DISTAL_PHALANX || ehb == e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX|| ehb == e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX || ehb == e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX|| ehb == e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX)
                {
                    knuckle = 4;
                }
                else
                {
                    throw std::invalid_argument("The given e_bone value is unknown.");
                }

                part = std::shared_ptr<ps::i_part>(new ps::digit_part(digit, knuckle));


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
				if (0 == default_definitions_.size())
				{
					std::vector<std::shared_ptr<column_definition> > result;

					std::vector<mae::e_bone> ebones = mae::e_bone_c::vec();

					for (unsigned int i = 0; i < ebones.size(); i++)
					{
						if (std::abs(mae::e_bone_c::to_int(ebones.at(i))) > 2 && std::abs(mae::e_bone_c::to_int(ebones.at(i))) != 4 && std::abs(mae::e_bone_c::to_int(ebones.at(i))) < 10)
						{
							result.push_back(std::make_shared<mae::fl::laban::column_definition>(ebones.at(i)));
						}
					}

					default_definitions_ = result;
				}

				return default_definitions_;
			}

            std::vector<std::shared_ptr<column_definition> > column_definition::default_hand_definitions(bool is_left)
            {
				if (0 == default_hand_definitions_.size())
				{
					std::vector<std::shared_ptr<column_definition> > result;

					std::vector<mae::e_hand_bone> ehandbones = mae::e_hand_bone_c::vec_side(is_left);

					for (unsigned int i = 0; i < ehandbones.size(); i++)
					{
						if (e_hand_bone::INVALID_HAND_BONE != ehandbones.at(i))
						{
							result.push_back(std::make_shared<mae::fl::laban::column_definition>(
									ehandbones.at(i)));
						}
					}

					default_hand_definitions_ = result;
				}

                return default_hand_definitions_;
            }

		} // namespace laban
	} // namespace fl
} // namespace mae
