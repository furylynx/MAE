//
// Created on 2017-10-17
//

#ifndef MAE_MATH_DTW_HPP_
#define MAE_MATH_DTW_HPP_

//custom includes
#include "i_warping_distance_measure.hpp"

//global includes
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

namespace mae
{
        namespace math
        {
                template<typename T>
                class dtw: public i_warping_distance_measure<T>
                {
                    public:
                        /**
                         * Creates a instance for a dynamic time warping using no windowing.
                         *
                         * @param distance_measure The distance measure for each single element.
                         */
                        dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure);


                        /**
                         * Creates a instance for a dynamic time warping using a windowing parameter.
                         *
                         * @param distance_measure The distance measure for each single element.
                         * @param window The window parameter.
                         */
                        dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window);

                        /**
                         * Creates a instance for a dynamic time warping using a windowing parameter.
                         *
                         * @param distance_measure The distance measure for each single element.
                         * @param window The window parameter.
                         * @param activate_s True to activate three dimensional warping matrix (starting positions included).
                         */
                        dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window, bool activate_s);

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

                    private:
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
                dtw<T>::dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure)
                {
                    distance_measure_ = distance_measure;
                    window_ = 0;
                    activate_s_ = true;
                }

                template<typename T>
                dtw<T>::dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window)
                {
                    distance_measure_ = distance_measure;
                    window_ = window;
                    activate_s_ = true;
                }

                template<typename T>
                dtw<T>::dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window, bool activate_s)
                {
                    distance_measure_ = distance_measure;
                    window_ = window;
                    activate_s_ = activate_s;
                }

                template<typename T>
                dtw<T>::~dtw()
                {
                }

                template<typename T>
                double dtw<T>::distance(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::size_t n = element1.size()+1;
                    std::size_t m = element2.size()+1;

                    std::vector<std::vector<std::vector<double> > > arr = warping_matrix(element1,element2);

                    return arr.at(n-1).at(m-1).at(0);
                }

                template<typename T>
                std::vector<std::vector<std::vector<double> > > dtw<T>::warping_matrix(std::vector<T> element1, std::vector<T> element2) const
                {
                    //set matrix sizes
                    std::size_t n = element1.size()+1;
                    std::size_t m = element2.size()+1;

                    //activate starting positions
                    std::size_t s_max = 1;
                    if (activate_s_)
                    {
                        s_max = m;
                    }

                    std::size_t window = std::max(n,m);
                    if (window_ > 0)
                    {
                        window = std::max(window_, std::size_t(std::abs((long)n-(long)m)));
                    }

                    std::vector<std::vector<std::vector<double> > > arr;

                    for (std::size_t i = 0; i < n ; i++)
                    {
                        std::vector<std::vector<double> > row;

                        for (std::size_t j = 0; j < m; j++)
                        {
                            std::vector<double> starts;

                            for (std::size_t s = 0; s < std::min(s_max,j+1); s++)
                            {
                                starts.push_back(std::numeric_limits<double>::infinity());
                            }

                            row.push_back(starts);
                        }

                        arr.push_back(row);
                    }

                    for (std::size_t s = 0; s < std::min(s_max,m) ; s++)
                    {
                        arr.at(0).at(s).at(s) = 0;
                    }

                    for (std::size_t i = 1 ; i < n ; i++)
                    {
                        for (std::size_t j = std::max(1l, ((long)i-(long)window)) ; j < std::min(m, (i+window)) ; j++)
                        {
                            double cost = distance_measure_->distance(element1.at(i-1), element2.at(j-1));

                            for (std::size_t s = 0; s < std::min(s_max,j); s++)
                            {
                                arr.at(i).at(j).at(s) = cost + std::min( std::min(arr.at(i-1).at(j).at(s), arr.at(i).at(j-1).at(s)),arr.at(i-1).at(j-1).at(s) );
                            }
                        }
                    }

                    return arr;
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_DTW_HPP_
