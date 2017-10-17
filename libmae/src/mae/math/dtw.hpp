//
// Created on 17.10.17.
//

#ifndef MAE_MATH_DTW_HPP_
#define MAE_MATH_DTW_HPP_

//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <memory>
#include <string>
#include <vector>

namespace mae
{
        namespace math
        {
                template<typename T>
                class dtw: public i_distance_measure<std::vector<T> >
                {
                    public:
                        /**
                         * Creates a new basis with no vectors set.
                         */
                        dtw(std::shared_ptr<i_distance_measure<T> > distance_measure);

                        virtual ~dtw();
                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

                    private:
                        std::shared_ptr<i_distance_measure<T> > distance_measure_;

                };

        } // namespace math
} // namespace mae


//template implementation
namespace mae
{
        namespace math
        {
                template<typename T>
                dtw<T>::dtw(std::shared_ptr<i_distance_measure<T> > distance_measure)
                {
                    distance_measure_ = distance_measure;
                }

                template<typename T>
                dtw<T>::~dtw()
                {
                }

                template<typename T>
                double dtw<T>::distance(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::size_t n = element1.size();
                    std::size_t m = element2.size();

                    std::array<std::array<double, element2.size()>, element1.size()> arr;


                    for (std::size_t i = 1 ; i <= n ; i++)
                    {
                        arr.at(i).at(0) = std::numeric_limits<double>::infinity();
                    }

                    for (std::size_t i = 1 ; i <= m ; i++)
                    {
                        arr.at(0).at(i) = std::numeric_limits<double>::infinity();
                    }

                    arr.at(0).at(0) = 0;


                    for (std::size_t i = 1 ; i <= n ; i++)
                    {
                        for (std::size_t j = 1 ; j <= m ; j++)
                        {
                            double cost = distance_measure_->distance(element1.at(i), element2.at(j));

                            arr.at(i).at(j) = cost + std::min( std::min(arr.at(i-1).at(j), arr.at(i).at(j-1)),arr.at(i-1).at(j-1) );
                        }
                    }

                    return arr.at(n).at(m);
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_DTW_HPP_
