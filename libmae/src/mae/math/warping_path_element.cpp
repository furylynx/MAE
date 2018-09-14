//
// Created on 2018-09-14
//

#include "warping_path_element.hpp"

namespace mae
{
    namespace math
    {
        warping_path_element::warping_path_element(std::size_t x, std::size_t y)
        {
            x_ = x;
            y_ = y;
        }
    
        warping_path_element::~warping_path_element()
        {
        
        }
    
        std::size_t warping_path_element::get_x() const
        {
            return x_;
        }
    
        void warping_path_element::set_x(std::size_t x)
        {
            x_ = x;
        }
    
        std::size_t warping_path_element::get_y() const
        {
            return y_;
        }
    
        void warping_path_element::set_y(std::size_t y)
        {
            y_ = y;
        }
    
    } // namespace math
} // namespace mae