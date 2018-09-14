//
// Created on 2018-09-14
//

#ifndef MAE_MATH_WARPING_PATH_SELEMENT_HPP
#define MAE_MATH_WARPING_PATH_SELEMENT_HPP

//custom includes
#include "warping_path_element.hpp"

//global includes
//..

namespace mae
{
    namespace math
    {
        
        
        class warping_path_selement : public warping_path_element
        {
            public:
                /**
                 * Creates a new warping path start element defining the position in the cost matrix.
                 *
                 * @param x The x position.
                 * @param y The y position.
                 * @param x_npos True if x is set to npos (first match for y is end)
                 * @param y_npos True if y is set to npos (first match for x is end)
                 */
                warping_path_selement(std::size_t x = 0, std::size_t y = 0, bool x_npos = false, bool y_npos = false);
                
                virtual ~warping_path_selement();
                
                /**
                 * Returns the x npos setting (first match for y is end).
                 *
                 * @return True if x is npos.
                 */
                virtual bool is_x_npos() const;
                
                /**
                 * Sets the x position to npos (first match for y is end).
                 *
                 * @param x_npos True if x is npos.
                 */
                virtual void set_x_npos(bool x_npos);
                
                /**
                 * Returns the y npos setting (first match for x is end).
                 *
                 * @return True if y is npos.
                 */
                virtual bool is_y_npos() const;
                
                /**
                 * Sets the y position to npos (first match for x is end).
                 *
                 * @param x_npos True if y is npos.
                 */
                virtual void set_y_npos(bool y_npos);
            
            private:
                bool x_npos_;
                bool y_npos_;
        };
        
    } // namespace math
} // namespace mae

#endif //MAE_MATH_WARPING_PATH_SELEMENT_HPP
