//
// Created on 2018-09-14
//

#ifndef MAE_MATH_WARPING_PATH_FINDER_HPP
#define MAE_MATH_WARPING_PATH_FINDER_HPP

//custom includes
#include "warping_path_selement.hpp"


//global includes
#include <memory>
#include <vector>
#include <limits>
#include <cmath>

namespace mae
{
    namespace math
    {
        
        class warping_path_finder
        {
            public:
                warping_path_finder();
                virtual ~warping_path_finder();
                
                
                virtual std::vector<warping_path_element> path(std::vector<std::vector<double> > cost_matrix, warping_path_selement startpos, warping_path_element endpos) const;
        
                virtual std::vector<warping_path_element> path(std::vector<std::vector<double> > cost_matrix, warping_path_selement startpos = warping_path_selement(0,0)) const;
    
            private:
        };
        
        
    } // namespace math
} // namespace mae

#endif //MAE_MATH_WARPING_PATH_FINDER_HPP
