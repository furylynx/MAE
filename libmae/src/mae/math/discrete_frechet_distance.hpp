//
// Created on 2017-11-10
//

#ifndef MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_
#define MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_

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
                class discrete_frechet_distance: public i_distance_measure<std::vector<T> >
                {
                    public:
                        /**
                         * Creates a instance for a frechet distance measure.
                         *
                         * @param distance_measure The distance measure for each single element.
                         */
                        discrete_frechet_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure);

                        virtual ~discrete_frechet_distance();

                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

                    private:
                        std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure_;

                        virtual double c(int i, int j, std::vector<T> &element1, std::vector<T> &element2, std::vector<std::vector<double> > &mem) const;

                        virtual double recursive(std::vector<T> element1, std::vector<T> element2) const;

                        virtual double iterative(std::vector<T> element1, std::vector<T> element2) const;

                };

        } // namespace math
} // namespace mae


//template implementation
namespace mae
{
        namespace math
        {

                template<typename T>
                discrete_frechet_distance<T>::discrete_frechet_distance(std::shared_ptr<mae::math::i_distance_measure<T> > distance_measure)
                {
                    distance_measure_ = distance_measure;
                }

                template<typename T>
                discrete_frechet_distance<T>::~discrete_frechet_distance()
                {
                }

                template<typename T>
                double discrete_frechet_distance<T>::distance(std::vector<T> element1, std::vector<T> element2) const
                {
                    return iterative(element1, element2);
                }

                template<typename T>
                double discrete_frechet_distance<T>::iterative(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::size_t p = element1.size();
                    std::size_t q = element2.size();

                    std::vector<std::vector<double> > arr;

                    for (std::size_t i = 0; i < p ; i++)
                    {
                        std::vector<double> row;

                        for (std::size_t j = 0; j < q; j++)
                        {
                            row.push_back(std::numeric_limits<double>::infinity());
                        }

                        arr.push_back(row);
                    }

                    for (std::size_t i = 0 ; i < p ; i++)
                    {
                        for (std::size_t j = 0 ; j < q ; j++)
                        {
                            if (i == 0 && j == 0)
                            {
                                arr.at(i).at(j) = distance_measure_->distance(element1.at(i), element2.at(j));
                            }
                            else if (i > 0 && j == 0)
                            {
                                // can either be the actual distance or distance pulled from above
                                arr.at(i).at(j) = std::max(arr.at(i-1).at(j),
                                                           distance_measure_->distance(element1.at(i), element2.at(j)));
                            }
                            else if (i == 0 && j > 0)
                            {
                                // can either be the distance pulled from the left or the actual distance
                                arr.at(i).at(j) = std::max(arr.at(i).at(j-1),
                                                           distance_measure_->distance(element1.at(i), element2.at(j)));
                            }
                            else if (i > 0 && j > 0)
                            {
                                // can be the actual distance, or distance from above or from the left
                                arr.at(i).at(j) = std::max(std::min(arr.at(i-1).at(j), std::min(arr.at(i-1).at(j-1), arr.at(i).at(j-1))),
                                                           distance_measure_->distance(element1.at(i), element2.at(j)));
                            }
                        }
                    }

                    return arr.at(p-1).at(q-1);
                }

                template<typename T>
                double discrete_frechet_distance<T>::recursive(std::vector<T> element1, std::vector<T> element2) const
                {

                    //initialize the matrix (dynamic programming)
                    std::vector<std::vector<double> > mem;
                    for (int i = 0; i < element1.size(); i++)
                    {
                        std::vector<double> mem_row;

                        for (int j = 0; j < element2.size(); j++)
                        {
                            mem_row.push_back(-1);
                        }

                        mem.push_back(mem_row);
                    }

                    return c(element1.size()-1,element2.size()-1, element1, element2, mem);
                }

                template<typename T>
                double discrete_frechet_distance<T>::c(int i, int j, std::vector<T> &element1, std::vector<T> &element2, std::vector<std::vector<double> > &mem) const
                {
                    if (mem.at(i).at(j) < 0)
                    {
                        // if the value has not yet been solved

                        if (i == 0 && j == 0)
                        {
                            // if top left column, just compute the distance
                            mem.at(i).at(j) = distance_measure_->distance(element1.at(i), element2.at(j));
                        }
                        else if (i > 0 && j == 0)
                        {
                            // can either be the actual distance or distance pulled from above
                            mem.at(i).at(j) = std::max(c(i - 1, 0, element1, element2, mem),
                                                       distance_measure_->distance(element1.at(i), element2.at(j)));
                        }
                        else if (i == 0 && j > 0)
                        {
                            // can either be the distance pulled from the left or the actual distance
                            mem.at(i).at(j) = std::max(c(0, j - 1, element1, element2, mem),
                                                       distance_measure_->distance(element1.at(i), element2.at(j)));
                        }
                        else if (i > 0 && j > 0)
                        {
                            // can be the actual distance, or distance from above or from the left
                            mem.at(i).at(j) = std::max(std::min(c(i - 1, j, element1, element2, mem),
                                                                std::min(c(i - 1, j - 1, element1, element2, mem),
                                                                         c(i, j - 1, element1, element2, mem))),
                                                       distance_measure_->distance(element1.at(i), element2.at(j)));
                        }
                    }

                    // return the DFD
                    return mem.at(i).at(j);

                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_DISCRETE_FRECHET_DISTANCE_HPP_
