//
// Created by furylynx on 2018-08-26.
//

#ifndef MAE_FL_LABAN_SVG_STYLE_HPP
#define MAE_FL_LABAN_SVG_STYLE_HPP

//custom includes
//...

//global includes
#include <string>

namespace mae
{
    namespace fl
    {
        namespace laban
        {
            class svg_style {
                public:
                    /**
                     * Creates a new rect.
                     */
                    svg_style();

                    virtual ~svg_style();

                    /**
                     * Returns the stroke width.
                     *
                     * @return The stroke width.
                     */
                    virtual double get_stroke_width() const;

                    /**
                     * Sets the stroke width.
                     *
                     * @param stroke_width The stroke width.
                     */
                    virtual void set_stroke_width(double stroke_width);

                    /**
                     * Returns the reduced stroke width.
                     *
                     * @return The reduced stroke width.
                     */
                    virtual double get_reduced_stroke_width() const;

                    /**
                     * Sets the reduced stroke width.
                     *
                     * @param reduced_stroke_width The reduced stroke width.
                     */
                    virtual void set_reduced_stroke_width(double reduced_stroke_width);

                    /**
                     * Returns the draw color.
                     *
                     * @return The draw color.
                     */
                    virtual std::string get_draw_color() const;

                    /**
                     * Sets the stroke width.
                     *
                     * @param stroke_width The stroke width.
                     */
                    virtual void set_draw_color(std::string draw_color);

                    /**
                     * Returns the fill color.
                     *
                     * @return The fill color.
                     */
                    virtual std::string get_fill_color() const;

                    /**
                     * Sets the fill color.
                     *
                     * @param stroke_width The fill color.
                     */
                    virtual void set_fill_color(std::string fill_color);

                private:
                    double stroke_width_;
                    double reduced_stroke_width_;
                    std::string draw_color_;
                    std::string fill_color_;

            };
        } // namespace laban
    } // namespace fl
} // namespace mae

#endif //MAE_FL_LABAN_SVG_STYLE_HPP
