//
// Created by furylynx on 2018-08-26.
//

#ifndef MAE_FL_LABAN_DRAW_LABAN_RECT_HPP
#define MAE_FL_LABAN_DRAW_LABAN_RECT_HPP

//custom includes
//...

//global includes
#include <memory>
#include <string>
#include <sstream>

namespace mae
{
    namespace fl
    {
        namespace laban
        {
            class draw_laban_rect
            {
                public:
                    /**
                    * Creates a new laban rect.
                    */
                    draw_laban_rect();

                    /**
                     * Creates a new three dimensional vector.
                     *
                     * @param posx The posx value.
                     * @param posy The posy value.
                     * @param width The width value.
                     * @param height The height value.
                     */
                    draw_laban_rect(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure);

                    virtual ~draw_laban_rect();

                    /**
                     * Returns the im_width.
                     *
                     * @return im_width.
                     */
                    virtual double get_im_width() const;

                    /**
                     * Returns the im_height.
                     *
                     * @return im_height.
                     */
                    virtual double get_im_height() const;

                    /**
                     * Returns the max_column.
                     *
                     * @return max_column.
                     */
                    virtual double get_max_column() const;

                    /**
                     * Returns the measures.
                     *
                     * @return measures.
                     */
                    virtual double get_measures() const;

                    /**
                     * Returns the beats_per_measure.
                     *
                     * @return beats_per_measure.
                     */
                    virtual double get_beats_per_measure() const;

                    /**
                    * Returns the string representation for this object.
                    *
                    * @return The string.
                    */
                    virtual std::string str() const;

                    /**
                     * Prints the object to the stream.
                     *
                     * @param os
                     * @param obj The object to be printed.
                     * @return
                     */
                    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<draw_laban_rect>& obj)
                    {
                        os << obj->str();

                        return os;
                    }

                    /**
                     * Prints the object to the stream.
                     *
                     * @param os
                     * @param obj The object to be printed.
                     * @return
                     */
                    friend std::ostream& operator<<(std::ostream& os, const draw_laban_rect& obj)
                    {
                        os << obj.str();

                        return os;
                    }

                private:
                    unsigned int im_width_;
                    unsigned int im_height_;
                    unsigned int max_column_;
                    unsigned int measures_;
                    unsigned int beats_per_measure_;
            };
        } // namespace laban
    } // namespace fl
} // namespace mae



#endif //MAE_FL_LABAN_DRAW_LABAN_RECT_HPP
