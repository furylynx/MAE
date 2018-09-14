//
// Created on 2018-09-14
//

#include "warping_path_finder.hpp"

namespace mae
{
    namespace math
    {
        warping_path_finder::warping_path_finder()
        {
        
        }
        
        warping_path_finder::~warping_path_finder()
        {
        
        }
        
        std::vector<warping_path_element> warping_path_finder::path(std::vector<std::vector<double> > cost_matrix, warping_path_selement startpos) const
        {
            if (cost_matrix.size() > 0)
            {
                return path(cost_matrix, startpos, warping_path_element(cost_matrix.size()-1, cost_matrix.at(0).size()-1));
            }
            else
            {
                return std::vector<warping_path_element>();
            }
        }
        
        std::vector<warping_path_element>
        warping_path_finder::path(std::vector<std::vector<double> > cost_matrix, warping_path_selement startpos, warping_path_element endpos) const
        {
            std::vector<warping_path_element> warping_path;
            std::size_t wn = endpos.get_x();
            std::size_t wm = endpos.get_y();
            
            while ((startpos.is_x_npos() || wn >= startpos.get_x()) && (startpos.is_y_npos() || wm >= startpos.get_y()))
            {
                warping_path.push_back(warping_path_element(wn, wm));
                
                if (startpos.get_x() == wn)
                {
                    wm--;
                }
                else if (startpos.get_y() == wm)
                {
                    wn--;
                }
                else
                {
                    //argmin of D(n-1,m-1),D(n-1,m),D(n,m-1), lexicographically smalles pair
                    double n1 = cost_matrix.at(wn - 1).at(wm);
                    double m1 = cost_matrix.at(wn).at(wm - 1);
                    double nm1 = cost_matrix.at(wn - 1).at(wm - 1);
                    double min = std::min(n1, std::min(m1, nm1));
                    
                    if (min == nm1)
                    {
                        wn--;
                        wm--;
                    }
                    else if (min == n1)
                    {
                        wn--;
                    }
                    else
                    {
                        wm--;
                    }
                }
            }
            
            std::reverse(warping_path.begin(), warping_path.end());
            
            return warping_path;
        }
        
    }
}
