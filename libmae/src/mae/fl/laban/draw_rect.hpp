//
// Created by furylynx on 2018-08-26.
//

#ifndef MAE_FL_LABAN_DRAW_RECT_HPP
#define MAE_FL_LABAN_DRAW_RECT_HPP

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

            class draw_rect {

                public:
                    /**
                     * Creates a new rect.
                     */
                    draw_rect();

                    /**
                     * Creates a new three dimensional vector.
                     *
                     * @param posx The posx value.
                     * @param posy The posy value.
                     * @param width The width value.
                     * @param height The height value.
                     */
                    draw_rect(double posx, double posy, double width, double height);

                    virtual ~draw_rect();

                    /**
                     * Returns the posx.
                     *
                     * @return posx.
                     */
                    virtual double get_posx() const;

                    /**
                     * Returns the posy.
                     *
                     * @return posy.
                     */
                    virtual double get_posy() const;

                    /**
                     * Returns the width.
                     *
                     * @return width.
                     */
                    virtual double get_width() const;

                    /**
                     * Returns the height.
                     *
                     * @return height.
                     */
                    virtual double get_height() const;

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
                    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<draw_rect>& obj)
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
                    friend std::ostream& operator<<(std::ostream& os, const draw_rect& obj)
                    {
                        os << obj.str();

                        return os;
                    }

                private:
                    double posx_;
                    double posy_;
                    double width_;
                    double height_;
            };

        } // namespace laban
    } // namespace fl
} // namespace mae


#endif //MAE_FL_LABAN_DRAW_RECT_HPP
