//
// Created on 2017-10-17
//

#ifndef MAE_MATH_ALIGNED_DISTANCE_HPP_
#define MAE_MATH_ALIGNED_DISTANCE_HPP_

//custom includes
#include "i_distance_measure.hpp"
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
                class aligned_distance : public i_distance_measure<std::vector<T> >
                {
                    public:
                        /**
                         * Creates a instance for an aligned distance using the given warping distance measure.
                         *
                         * @param distance_measure The distance measure for each single element.
                         */
                        aligned_distance(std::shared_ptr<mae::math::i_warping_distance_measure<T> > distance_measure);

                        virtual ~aligned_distance();

                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

                    private:
                        std::shared_ptr<mae::math::i_warping_distance_measure<T> > distance_measure_;

                };

        } // namespace math
} // namespace mae


//template implementation
namespace mae
{
        namespace math
        {

                template<typename T>
                aligned_distance<T>::aligned_distance(std::shared_ptr<mae::math::i_warping_distance_measure<T> > distance_measure)
                {
                    distance_measure_ = distance_measure;
                }

                template<typename T>
                aligned_distance<T>::~aligned_distance()
                {
                }

                template<typename T>
                double aligned_distance<T>::distance(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::vector<std::vector<double> > arr = distance_measure_->warping_matrix(element1,element2);

                    //TODO matrix recurrency

                    return arr.at(arr.size()-1).at(arr.at(0).size()-1);
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_ALIGNED_DISTANCE_HPP_
