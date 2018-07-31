//
// Created on 2017-11-14
//

#ifndef MAE_MATH_LCS_DISTANCE_HPP_
#define MAE_MATH_LCS_DISTANCE_HPP_

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
        class lcs_distance: public i_warping_distance_measure<T>
        {
        public:
            /**
             * Creates an instance for a longest common subsequence using no windowing.
             *
             * @param distance_measure The distance measure for each single element.
             * @param target_value True for having the first sequence for the {@link distance(element1,element2)} as the target value to compare to. False for simply comparing the two sequences.
             */
            lcs_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool target_value = false, bool activate_s = false);

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
            virtual std::vector<std::vector<std::vector<double> > > warping_matrix(std::vector<T> element1, std::vector<T> element2) const;


        private:
            std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
            bool target_value_;
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
        lcs_distance<T>::lcs_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, bool target_value, bool activate_s)
        {
            distance_measure_ = distance_measure;
            target_value_ = target_value;
            activate_s_ = activate_s;
        }

        template<typename T>
        lcs_distance<T>::~lcs_distance()
        {
        }

        template<typename T>
        double lcs_distance<T>::distance(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t p = element1.size();
            std::size_t q = element2.size();

            std::vector<std::vector<std::vector<double> > > arr = warping_matrix(element1, element2);

            return arr.at(p).at(q).at(0);
        }

        template<typename T>
        std::vector<std::vector<std::vector<double> > > lcs_distance<T>::warping_matrix(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t n = element1.size()+1;
            std::size_t m = element2.size()+1;

            double target_size = element1.size();

            if (!target_value_)
            {
                target_size = std::max(element1.size(), element2.size());
            }

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
                        starts.push_back(target_size);
                    }

                    row.push_back(starts);
                }

                arr.push_back(row);
            }

            for (std::size_t i = 1 ; i < n ; i++)
            {
                for (std::size_t j = 1 ; j < m ; j++)
                {
                    bool dist_zero = (0 == distance_measure_->distance(element1.at(i-1), element2.at(j-1)));

                    for (std::size_t s = 0; s < std::min(s_max,j); s++)
                    {
                        if (dist_zero)
                        {
                            arr.at(i).at(j).at(s) = arr.at(i - 1).at(j - 1).at(s) - 1;
                        }
                        else
                        {
                            arr.at(i).at(j).at(s) = std::min(arr.at(i).at(j - 1).at(s), arr.at(i - 1).at(j).at(s));
                        }
                    }
                }
            }

            return arr;
        }


    } // namespace math
} // namespace mae

#endif // MAE_MATH_LCS_DISTANCE_HPP_
