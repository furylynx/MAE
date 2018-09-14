//
// Created on 2018-09-14
//

#ifndef MAE_MATH_WARPING_PATH_ELEMENT_HPP
#define MAE_MATH_WARPING_PATH_ELEMENT_HPP


#include <cstdio>

namespace mae
{
    namespace math
    {
        
        class warping_path_element
        {
            public:
                /**
                 * Creates a new warping path element defining the position in the cost matrix.
                 *
                 * @param x The x position.
                 * @param y The y position.
                 */
                warping_path_element(std::size_t x = 0, std::size_t y = 0);
                
                virtual ~warping_path_element();
        
                /**
                 * Returns the x position.
                 *
                 * @return The x pos.
                 */
                virtual std::size_t get_x() const;
        
                /**
                 * Sets the x position.
                 *
                 * @param x The x pos.
                 */
                virtual void set_x(std::size_t x);
        
                /**
                 * Returns the y position.
                 *
                 * @return The y pos.
                 */
                virtual std::size_t get_y() const;
        
                /**
                 * Sets the y position.
                 *
                 * @param y The y pos.
                 */
                virtual void set_y(std::size_t y);
    
            private:
                std::size_t x_;
                std::size_t y_;
                
        };
        
    } // namespace math
} // namespace mae

#endif //MAE_MATH_WARPING_PATH_ELEMENT_HPP
