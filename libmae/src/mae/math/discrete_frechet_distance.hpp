//
// Created on 2017-11-10
//

#ifndef MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_
#define MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_

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
                class discrete_frechet_distance: public i_warping_distance_measure<T>
                {
                    public:
                        /**
                         * Creates a instance for a frechet distance measure.
                         *
                         * @param distance_measure The distance measure for each single element.
                         * @param activate_s True to activate three dimensional warping matrix (starting positions included).
                         */
                        discrete_frechet_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool activate_s = false);

                        virtual ~discrete_frechet_distance();

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
                         * @return Returns the warping matrix. Can be used to find the optimal alignment.
                         */
                        virtual std::vector<std::vector<std::vector<double> > > warping_matrix(std::vector<T> element1, std::vector<T> element2) const;

                    private:
                        std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
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
                discrete_frechet_distance<T>::discrete_frechet_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool activate_s)
                {
                    distance_measure_ = distance_measure;
                    activate_s_ = activate_s;
                }

                template<typename T>
                discrete_frechet_distance<T>::~discrete_frechet_distance()
                {
                }

                template<typename T>
                double discrete_frechet_distance<T>::distance(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::size_t p = element1.size();
                    std::size_t q = element2.size();

                    std::vector<std::vector<std::vector<double> > > arr = warping_matrix(element1, element2);

                    return arr.at(p).at(q).at(0);
                }

                template<typename T>
                std::vector<std::vector<std::vector<double> > > discrete_frechet_distance<T>::warping_matrix(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::size_t n = element1.size()+1;
                    std::size_t m = element2.size()+1;

                    //activate starting positions
                    std::size_t s_max = 1;
                    if (activate_s_)
                    {
                        s_max = m;
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
                        for (std::size_t j = 1 ; j < m ; j++)
                        {
                            double dist = distance_measure_->distance(element1.at(i-1), element2.at(j-1));

                            for (std::size_t s = 0; s < std::min(s_max,j); s++)
                            {
                                // can be the actual distance, or distance from above or from the left
                                arr.at(i).at(j).at(s) = std::max(std::min(arr.at(i-1).at(j).at(s), std::min(arr.at(i-1).at(j-1).at(s), arr.at(i).at(j-1).at(s))),dist);
                            }
                        }
                    }

                    return arr;
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_
