//
// Created by furylynx on 2018-08-26.
//

#include "draw_laban_rect.hpp"

namespace mae
{
    namespace fl
    {
        namespace laban
        {

            draw_laban_rect::draw_laban_rect()
            {

            }

            draw_laban_rect::draw_laban_rect(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure)
            {
                im_width_ = im_width;
                im_height_ = im_height;
                max_column_ = max_column;
                measures_ = measures;
                beats_per_measure_ = beats_per_measure;
            }

            draw_laban_rect::~draw_laban_rect()
            {
            }

            double draw_laban_rect::get_im_width() const
            {
                return im_width_;
            }

            double draw_laban_rect::get_im_height() const
            {
                return im_height_;
            }

            double draw_laban_rect::get_max_column() const
            {
                return max_column_;
            }

            double draw_laban_rect::get_measures() const
            {
                return measures_;
            }

            double draw_laban_rect::get_beats_per_measure() const
            {
                return beats_per_measure_;
            }

            std::string draw_laban_rect::str() const
            {
                std::stringstream sstr;

                sstr << "labanrect [" << im_width_ << "," << im_height_ << "," << max_column_ << "," << measures_ << "," << beats_per_measure_ << "]";

                return sstr.str();
            }

        } // namespace laban
    } // namespace fl
} // namespace mae