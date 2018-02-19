//
// Created on 2017-11-20
//

#ifndef MAE_MATH_EDR_HPP
#define MAE_MATH_EDR_HPP

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
        class edr : public i_warping_distance_measure<T>
        {
        public:
            /**
             * Creates a instance for a longest common subsequence using no windowing.
             *
             * @param distance_measure The distance measure for each single element.
             * @param epsilon The threshold for distance comparison for subcosts. Epsilon defines a maximum distance between two elements still seen as matching. If epsilon is zero, elements are only seen as matching when their distance is zero.
             * @param activate_s True to activate three dimensional warping matrix (starting positions included).
             */
            edr(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, double epsilon = 0, bool activate_s = false);

            virtual ~edr();

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
            double epsilon_;
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
        edr<T>::edr(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, double epsilon, bool activate_s)
        {
            distance_measure_ = distance_measure;
            epsilon_ = epsilon;
            activate_s_ = activate_s;
        }

        template<typename T>
        edr<T>::~edr()
        {
        }

        template<typename T>
        double edr<T>::distance(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t n = element1.size()+1;
            std::size_t m = element2.size()+1;

            std::vector<std::vector<std::vector<double> > > arr = warping_matrix(element1, element2);

            return arr.at(n-1).at(m-1).at(0);
        }

        template<typename T>
        std::vector<std::vector<std::vector<double> > > edr<T>::warping_matrix(std::vector<T> element1, std::vector<T> element2) const
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

            for (std::size_t i = 1; i < n; i++)
            {
                arr.at(i).at(0).at(0) = i;
            }

            for (std::size_t j = 1; j < m; j++)
            {
                for (std::size_t s = 0; s < std::min(s_max,j) ; s++)
                {
                    arr.at(0).at(j).at(s) = j;
                }
            }

            for (std::size_t i = 1 ; i < n ; i++)
            {
                for (std::size_t j = 1 ; j < m ; j++)
                {
                    int subcost = 0;

                    if (distance_measure_->distance(element1.at(i-1), element2.at(j-1)) > epsilon_)
                    {
                        subcost = 1;
                    }

                    for (std::size_t s = 0; s < std::min(s_max,j); s++)
                    {
                        arr.at(i).at(j).at(s) = std::min(arr.at(i).at(j-1).at(s) + 1, std::min(arr.at(i-1).at(j).at(s) + 1, arr.at(i-1).at(j-1).at(s) + subcost));;
                    }
                }
            }

            return arr;
        }

    } // namespace math
} // namespace mae


#endif //MAE_MATH_EDR_HPP
