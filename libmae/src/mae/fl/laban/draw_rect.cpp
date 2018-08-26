//
// Created by furylynx on 2018-08-26.
//

#include "draw_rect.hpp"


namespace mae
{
    namespace fl
    {
        namespace laban
        {
            draw_rect::draw_rect()
            {

            }

            draw_rect::draw_rect(double posx, double posy, double width, double height)
            {
                posx_ = posx;
                posy_ = posy;
                width_ = width;
                height_ = height;
            }

            draw_rect::~draw_rect()
            {
            }

            double draw_rect::get_posx() const
            {
                return posx_;
            }

            double draw_rect::get_posy() const
            {
                return posy_;
            }

            double draw_rect::get_width() const
            {
                return width_;
            }

            double draw_rect::get_height() const
            {
                return height_;
            }

            std::string draw_rect::str() const
            {
                std::stringstream sstr;

                sstr << "rect [" << posx_ << "," << posy_ << "," << width_ << "," << height_ << "]";

                return sstr.str();
            }

        } // namespace laban
    } // namespace fl
} // namespace mae
