//
// Created by furylynx on 2018-08-26
//

#include "svg_style.hpp"

namespace mae
{
    namespace fl
    {
        namespace laban
        {

            svg_style::svg_style()
            {
                stroke_width_ = 2.0;
                reduced_stroke_width_ = 1.0;
                draw_color_ = "000000";
                fill_color_ = "ffffff";
            }

            svg_style::~svg_style()
            {
            }

            double svg_style::get_stroke_width() const
            {
                return stroke_width_;
            }

            void svg_style::set_stroke_width(double stroke_width)
            {
                stroke_width_ = stroke_width;
            }

            double svg_style::get_reduced_stroke_width() const
            {
                return reduced_stroke_width_;
            }

            void svg_style::set_reduced_stroke_width(double reduced_stroke_width)
            {
                reduced_stroke_width_ = reduced_stroke_width;
            }

            std::string svg_style::get_draw_color() const
            {
                return draw_color_;
            }

            void svg_style::set_draw_color(std::string draw_color)
            {
                draw_color_ = draw_color;
            }

            std::string svg_style::get_fill_color() const
            {
                return fill_color_;
            }

            void svg_style::set_fill_color(std::string fill_color)
            {
                fill_color_ = fill_color;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae