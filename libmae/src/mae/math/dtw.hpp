//
// Created on 2017-10-17
//

#ifndef MAE_MATH_DTW_HPP_
#define MAE_MATH_DTW_HPP_

//custom includes
#include "i_distance_measure.hpp"

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
                class dtw: public i_distance_measure<std::vector<T> >
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

                        virtual ~dtw();

                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

                    private:
                        std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
                        std::size_t window_;

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
                }

                template<typename T>
                dtw<T>::dtw(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, std::size_t window)
                {
                    distance_measure_ = distance_measure;
                    window_ = window;
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

                    std::size_t window = std::max(n,m);
                    if (window_ > 0)
                    {
                        window = std::max(window_, std::size_t(std::abs((long)n-(long)m)));
                    }

                    std::vector<std::vector<double>> arr;

                    for (std::size_t i = 0; i < n ; i++)
                    {
                        std::vector<double> row;

                        for (std::size_t j = 0; j < m; j++)
                        {
                            row.push_back(std::numeric_limits<double>::infinity());
                        }

                        arr.push_back(row);
                    }

                    arr.at(0).at(0) = 0;

                    for (std::size_t i = 1 ; i < n ; i++)
                    {
                        for (std::size_t j = std::max(1l, ((long)i-(long)window)) ; j < std::min(m, (i+window)) ; j++)
                        {
                            double cost = distance_measure_->distance(element1.at(i-1), element2.at(j-1));

                            arr.at(i).at(j) = cost + std::min( std::min(arr.at(i-1).at(j), arr.at(i).at(j-1)),arr.at(i-1).at(j-1) );
                        }
                    }

                    return arr.at(n-1).at(m-1);
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_DTW_HPP_
