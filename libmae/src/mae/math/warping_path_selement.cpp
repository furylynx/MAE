//
// Created on 2018-09-14
//

#include "warping_path_selement.hpp"

namespace mae
{
    namespace math
    {
    
        warping_path_selement::warping_path_selement(size_t x, size_t y, bool x_npos, bool y_npos) : warping_path_element(x,y)
        {
            x_npos_ = x_npos;
            y_npos_ = y_npos;
        }
    
        warping_path_selement::~warping_path_selement()
        {
        
        }
    
        bool warping_path_selement::is_x_npos() const
        {
            return x_npos_;
        }
    
        void warping_path_selement::set_x_npos(bool x_npos)
        {
            x_npos_ = x_npos;
        }
    
        bool warping_path_selement::is_y_npos() const
        {
            return y_npos_;
        }
    
        void warping_path_selement::set_y_npos(bool y_npos)
        {
            y_npos_ = y_npos;
        }
    } // namespace math
} // namespace mae