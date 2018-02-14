//
// Created on 2017-10-17
//

#ifndef MAE_MATH_ALIGNED_DISTANCE_HPP_
#define MAE_MATH_ALIGNED_DISTANCE_HPP_

//custom includes
#include "i_distance_measure.hpp"
#include "i_warping_distance_measure.hpp"
#include "aligned_distance_details.hpp"
#include "aligned_distances_details.hpp"

//global includes
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <limits>

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
                         * Returns the aligned distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         * @return The aligned distance between the two series.
                         */
                        virtual double distance(std::vector<T> element1, std::vector<T> element2) const;

                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual aligned_distance_details distance_details(std::vector<T> element1, std::vector<T> element2) const;


                        /**
                         * Returns the overall aligned distance between the paired time series.
                         *
                         * @param mapped_elements The mapped elements.
                         * @return The aligned overall distance.
                         */
                        virtual double distance(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const;

                        /**
                         * Returns the overall distance between the paired time series.
                         *
                         * @param mapped_elements The mapped elements.
                         * @return The distance details (distance per pair in the same order as the mapped elements).
                         */
                        virtual aligned_distances_details distances_details(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const;

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
                    return distance_details(element1, element2).get_distance();
                }

                template<typename T>
                aligned_distance_details aligned_distance<T>::distance_details(std::vector<T> element1, std::vector<T> element2) const
                {
                    std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements;
                    mapped_elements.push_back(std::make_pair<std::vector<T>, std::vector<T> > (element1, element2));

                    aligned_distances_details details = distances_details(mapped_elements);

                    return aligned_distance_details(details.get_startpos(),details.get_endpos(), details.get_distances().at(0));
                }

                template<typename T>
                double aligned_distance<T>::distance(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const
                {
                    std::vector<double> distances = distance_details(mapped_elements).get_distances();
                    double sum = std::accumulate(distances.begin(), distances.end(), 0.0);
                    return sum / distances.size();
                }

                template<typename T>
                aligned_distances_details aligned_distance<T>::distances_details(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const
                {
                    std::vector<std::vector<std::vector<double> > > matrices;

                    std::size_t n = 0;
                    std::size_t m = 0;

                    for (std::pair<std::vector<T>,std::vector<T> > pair : mapped_elements)
                    {
                        //check size
                        if (0 == n)
                        {
                            n = pair.first.size();
                        }

                        if (0 == m)
                        {
                            m = pair.second.size();
                        }

                        if (n != pair.first.size() || m != pair.second.size())
                        {
                            throw std::invalid_argument("Different sequence lengths found. Sequences must have same length to be aligned.");
                        }

                        std::vector<std::vector<double> > warping_matrix = distance_measure_->warping_matrix(pair.first,pair.second);

                        if (n + 1 != warping_matrix.size() || m + 1 != warping_matrix.at(0).size())
                        {
                            throw std::invalid_argument("Warping matrix size does not match. Warping matrices must have an additional first row and first column.");
                        }

                        matrices.push_back(warping_matrix);
                    }

                    double min_distance = std::numeric_limits<double>::infinity();
                    std::size_t min_startpos = 0;
                    std::size_t min_endpos = m+1;

                    for (std::size_t startpos = 0; startpos <= m; startpos++)
                    {
                        for (std::size_t endpos = startpos + 1; endpos <= m+1; endpos++)
                        {
                            double distance_sum = 0;
                            for (std::vector<std::vector<double> > warping_matrix : matrices)
                            {
                                distance_sum += warping_matrix.at(n+1).at(endpos) - warping_matrix.at(n+1).at(startpos);
                            }

                            if (distance_sum < min_distance)
                            {
                                min_distance = distance_sum;

                                min_startpos = startpos;
                                min_endpos = endpos;
                            }
                        }
                    }

                    std::vector<double> distances;

                    for (std::vector<std::vector<double> > warping_matrix : matrices)
                    {
                        distances.push_back(warping_matrix.at(n+1).at(min_endpos) - warping_matrix.at(n+1).at(min_startpos));
                    }

                    return aligned_distances_details(min_startpos, min_endpos, distances);
                }


        } // namespace math
} // namespace mae

#endif // MAE_MATH_ALIGNED_DISTANCE_HPP_
