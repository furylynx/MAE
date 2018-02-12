//
// Created on 2017-11-14
//

#ifndef MAE_MATH_LCS_DISTANCE_HPP_
#define MAE_MATH_LCS_DISTANCE_HPP_

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
        class lcs_distance: public i_distance_measure<std::vector<T> >
        {
        public:
            /**
             * Creates a instance for a longest common subsequence using no windowing.
             *
             * @param distance_measure The distance measure for each single element.
             * @param target_value True for having the first sequence for the {@link distance(element1,element2)} as the target value to compare to. False for simply comparing the two sequences.
             */
            lcs_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool target_value = false);

            virtual ~lcs_distance();

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
            virtual std::vector<std::vector<std::size_t> > subsequence_matrix(std::vector<T> element1, std::vector<T> element2) const;


        private:
            std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
            bool target_value_;

        };

    } // namespace math
} // namespace mae


//template implementation
namespace mae
{
    namespace math
    {

        template<typename T>
        lcs_distance<T>::lcs_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool target_value)
        {
            distance_measure_ = distance_measure;
            target_value_ = target_value;
        }

        template<typename T>
        lcs_distance<T>::~lcs_distance()
        {
        }

        template<typename T>
        double lcs_distance<T>::distance(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t n = element1.size()+1;
            std::size_t m = element2.size()+1;

            std::vector<std::vector<std::size_t> > arr = warping_matrix(element1, element2);

            // longest common subsequence
            std::size_t lcs = arr.at(n-1).at(m-1);

            if (0 != lcs)
            {
                if (target_value_)
                {
                    return (element1.size()/(double) lcs)-1;
                }
                else
                {
                    return (std::max(element1.size(), element2.size())/(double) lcs)-1;
                }
            }
            else
            {
                return std::numeric_limits<double>::infinity();
            }
        }

        template<typename T>
        std::vector<std::vector<std::size_t> > lcs_distance<T>::subsequence_matrix(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t n = element1.size()+1;
            std::size_t m = element2.size()+1;

            std::vector<std::vector<std::size_t> > arr;

            for (std::size_t i = 0; i < n ; i++)
            {
                std::vector<std::size_t> row;

                for (std::size_t j = 0; j < m; j++)
                {
                    row.push_back(0);
                }

                arr.push_back(row);
            }

            for (std::size_t i = 1 ; i < n ; i++)
            {
                for (std::size_t j = 1 ; j < m ; j++)
                {
                    if (0 == distance_measure_->distance(element1.at(i-1), element2.at(j-1)))
                    {
                        arr.at(i).at(j) = arr.at(i - 1).at(j - 1) - 1;
                    }
                    else
                    {
                        arr.at(i).at(j) = std::max(arr.at(i).at(j - 1), arr.at(i -1 ).at(j));
                    }
                }
            }

            return arr;
        }


    } // namespace math
} // namespace mae

#endif // MAE_MATH_LCS_DISTANCE_HPP_
