//
// Created on 2017-10-17
//

#ifndef MAE_MATH_DTW_HPP_
#define MAE_MATH_DTW_HPP_

//custom includes
#include "i_warping_distance_measure.hpp"
#include "aligned_distance_details.hpp"
#include "warping_path_finder.hpp"

//global includes
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <iostream>

namespace mae
{
    namespace math
    {
        template<typename T>
        class dtw : public i_warping_distance_measure<T>
        {
            public:
                /**
                 * Creates a instance for a dynamic time warping using a windowing parameter.
                 *
                 * @param distance_measure The distance measure for each single element.
                 * @param window The window parameter.
                 * @param activate_s True to activate three dimensional warping matrix (starting positions included).
                 */
                dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window = 0, bool activate_s = false);
                
                virtual ~dtw();
                
                /**
                 * Returns the distance between the two time series.
                 *
                 * @param element1 The first element to compare.
                 * @param element2 The second element to compare.
                 */
                virtual double distance(std::vector<T> element1, std::vector<T> element2) const;
                
                /**
                 * Returns the warping matrix between the two elements.
                 *
                 * @param element1 The first element to compare.
                 * @param element2 The second element to compare.
                 * @return Returns the warping matrix (with warping for startpositions as third dimension). Can be used to find the optimal alignment.
                 */
                virtual std::vector<std::vector<std::vector<double> > > warping_matrix(std::vector<T> element1, std::vector<T> element2) const;
                
                /**
                 * Returns the optimal alignment for the actual sequence within the target sequence.
                 *
                 * @param target_sequence The target sequence in which a subsequence is used for the optimal alignment.
                 * @param actual_sequence The actual sequence which will be aligned to a subsequence of the target sequence.
                 * @return The aligned distance details.
                 */
                virtual aligned_distance_details optimal_alignment(std::vector<T> target_sequence, std::vector<T> actual_sequence) const;
            
            private:
                std::shared_ptr<warping_path_finder> warping_path_finder_;
                std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
                std::size_t window_;
                bool activate_s_;
            
        };
        
    } // namespace math
} // namespace mae


//template implementation
namespace mae
{
    namespace math
    {
        
        template<typename T>
        dtw<T>::dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window, bool activate_s)
        {
            distance_measure_ = distance_measure;
            window_ = window;
            activate_s_ = activate_s;
    
            warping_path_finder_ = std::make_shared<warping_path_finder>();
        }
        
        template<typename T>
        dtw<T>::~dtw()
        {
        }
        
        template<typename T>
        double dtw<T>::distance(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t p = element1.size();
            std::size_t q = element2.size();
            
            std::vector<std::vector<std::vector<double> > > arr = warping_matrix(element1, element2);
            
            return arr.at(p).at(q).at(0);
        }
        
        template<typename T>
        std::vector<std::vector<std::vector<double> > > dtw<T>::warping_matrix(std::vector<T> element1, std::vector<T> element2) const
        {
            
            //set matrix sizes
            std::size_t n = element1.size() + 1;
            std::size_t m = element2.size() + 1;
            
            //activate starting positions
            std::size_t s_max = 1;
            if (activate_s_)
            {
                s_max = m;
            }
            
            std::size_t window = std::max(n, m);
            if (window_ > 0)
            {
                window = std::max(window_, std::size_t(std::abs((long) n - (long) m)));
            }
            
            std::vector<std::vector<std::vector<double> > > arr;
            
            for (std::size_t i = 0; i < n; i++)
            {
                std::vector<std::vector<double> > row;
                
                for (std::size_t j = 0; j < m; j++)
                {
                    std::vector<double> starts;
                    
                    for (std::size_t s = 0; s < std::min(s_max, j + 1); s++)
                    {
                        starts.push_back(std::numeric_limits<double>::infinity());
                    }
                    
                    row.push_back(starts);
                }
                
                arr.push_back(row);
            }
            
            for (std::size_t s = 0; s < std::min(s_max, m); s++)
            {
                arr.at(0).at(s).at(s) = 0;
            }
            
            for (std::size_t i = 1; i < n; i++)
            {
                for (std::size_t j = std::max(1l, ((long) i - (long) window)); j < std::min(m, (i + window)); j++)
                {
                    double cost = distance_measure_->distance(element1.at(i - 1), element2.at(j - 1));
                    
                    for (std::size_t s = 0; s < std::min(s_max, j); s++)
                    {
                        arr.at(i).at(j).at(s) = cost + std::min(std::min(arr.at(i - 1).at(j).at(s), arr.at(i).at(j - 1).at(s)), arr.at(i - 1).at(j - 1).at(s));
                    }
                }
            }
            
            return arr;
        }
        
        template<typename T>
        aligned_distance_details dtw<T>::optimal_alignment(std::vector<T> target_sequence, std::vector<T> actual_sequence) const
        {
            //set matrix sizes
            std::size_t n = target_sequence.size() + 1;
            std::size_t m = actual_sequence.size() + 1;
            
            //set window size
            std::size_t window = std::max(n, m);
            if (window_ > 0)
            {
                window = std::max(window_, std::size_t(std::abs((long) n - (long) m)));
            }
            
            //initiate array and first row/column
            std::vector<std::vector<double> > arr;
            
            for (std::size_t i = 0; i < n; i++)
            {
                std::vector<double> row;
                
                for (std::size_t j = 0; j < m; j++)
                {
                    if (0 == i)
                    {
                        row.push_back(0);
                    }
                    else if (0 == j)
                    {
                        row.push_back(std::numeric_limits<double>::infinity());
                    }
                    else if (1 == i)
                    {
                        row.push_back(distance_measure_->distance(target_sequence.at(0), actual_sequence.at(m - 1)));
                    }
                }
                
                arr.push_back(row);
            }
            
            // build distance matrix
            for (std::size_t i = 2; i < n; i++)
            {
                for (std::size_t j = std::max(1l, ((long) i - (long) window)); j < std::min(m, (i + window)); j++)
                {
                    double cost = distance_measure_->distance(target_sequence.at(i - 1), actual_sequence.at(j - 1));
                    
                    arr.at(i).at(j) = cost + std::min(std::min(arr.at(i - 1).at(j), arr.at(i).at(j - 1)), arr.at(i - 1).at(j - 1));
                    
                }
            }
            
            //TODO remove
            std::cout << "searching for argmin" << std::endl;
            
            //find argmin for b_star
            std::size_t b_star = m;
            double min = std::numeric_limits<double>::infinity();
            for (std::size_t j = 0 ; j < m; j++)
            {
                if (arr.at(n-1).at(j) < min)
                {
                    min = arr.at(n-1).at(j);
                    b_star = j;
                }
            }
            
            //TODO remove
            std::cout << "searching for warping path" << std::endl;
    
            //warping path until i = 1, last element u,v
            std::vector<warping_path_element> warping_path = warping_path_finder_->path(arr, warping_path_selement(1, 1, false, true), warping_path_element(n-1, b_star));
            std::size_t a_star = warping_path.at(0).get_y();
    
    
            //use arr.at(n-1).at(b_star) - arr.at(1).at(a_star) for distance
            double distance = arr.at(n-1).at(b_star) - arr.at(1).at(a_star);
    
    
            //TODO remove
            std::cout << "using distance" << std::endl;
            
            //fill aligned_distance_details
            return aligned_distance_details(a_star, b_star, distance, std::vector<warping_path_element>());
        }
        
    } // namespace math
} // namespace mae

#endif // MAE_MATH_DTW_HPP_
