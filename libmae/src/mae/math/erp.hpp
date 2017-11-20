//
// Created on 2017-11-20
//

#ifndef MAE_MATH_ERP_HPP
#define MAE_MATH_ERP_HPP

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
        class erp : public i_distance_measure<std::vector<T> >
        {
        public:
            /**
             * Creates a instance for a longest common subsequence using no windowing.
             *
             * @param distance_measure The distance measure for each single element.
             * @param g
             */
            erp(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, T g);

            virtual ~erp();

            /**
             * Returns the distance between the two time series.
             *
             * @param element1 The first element to compare.
             * @param element2 The second element to compare.
             */
            virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

        private:
            std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;
            T g_;

        };

    } // namespace math
} // namespace mae


//template implementation
namespace mae
{
    namespace math
    {

        template<typename T>
        erp<T>::erp(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure, double epsilon)
        {
            distance_measure_ = distance_measure;
            epsilon_ = epsilon;
        }

        template<typename T>
        erp<T>::~erp()
        {
        }

        template<typename T>
        double erp<T>::distance(std::vector<T> element1, std::vector<T> element2) const
        {
            std::size_t n = element1.size()+1;
            std::size_t m = element2.size()+1;

            std::vector<std::vector<double> > arr;

            for (std::size_t i = 0; i < n ; i++)
            {
                std::vector<double> row;

                for (std::size_t j = 0; j < m; j++)
                {
                    row.push_back(0);
                }

                arr.push_back(row);
            }

            //TODO initialize array

            for (int i = 0; i < element1.size(); i++)
            {
                arr.at(i).at(0) = distance_measure_->distance(g_, element1.at(i));
            }

            for (int j = 0; j < element1.size(); j++)
            {
                arr.at(0).at(j) = distance_measure_->distance(g_, element2.at(j));
            }

            for (std::size_t i = 1 ; i < n ; i++)
            {
                for (std::size_t j = 1 ; j < m ; j++)
                {
                    double derp0 = arr.at(i-1).at(j) + distance_measure_->distance(element1.at(i-1), g_);
                    double derp1 = arr.at(i).at(j-1) + distance_measure_->distance(g_, element2.at(j-1));
                    double derp01 = arr.at(i-1).at(j-1) + distance_measure_->distance(element1.at(i-1), element2.at(j-1));

                    arr.at(i).at(j) = std::min(derp0, std::min(derp1, derp01));
                }
            }

            return arr.at(n-1).at(m-1);
        }


    } // namespace math
} // namespace mae


#endif //MAE_MATH_ERP_HPP
