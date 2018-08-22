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
#include "../mos.hpp"

//global includes
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <limits>
#include <utility>

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
                         * @param target_sequence The first element to compare.
                         * @param actual_sequence The second element to compare.
                         * @return The aligned distance between the two series.
                         */
                        virtual double distance(std::vector<T> target_sequence, std::vector<T> actual_sequence) const;

                        /**
                         * Returns the distance between the two time series.
                         *
                         * @param target_sequence The first element to compare.
                         * @param actual_sequence The second element to compare.
                         */
                        virtual aligned_distance_details distance_details(std::vector<T> target_sequence, std::vector<T> actual_sequence) const;


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
                double aligned_distance<T>::distance(std::vector<T> target_sequence, std::vector<T> actual_sequence) const
                {
                    return distance_details(target_sequence, actual_sequence).get_distance();
                }

                template<typename T>
                aligned_distance_details aligned_distance<T>::distance_details(std::vector<T> target_sequence, std::vector<T> actual_sequence) const
                {
                    std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements;
                    mapped_elements.push_back(std::make_pair(target_sequence, actual_sequence));

                    aligned_distances_details details = distances_details(mapped_elements);

                    return aligned_distance_details(details.get_startpos(),details.get_endpos(), details.get_distances().at(0), details.get_warping_paths().at(0));
                }

                template<typename T>
                double aligned_distance<T>::distance(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const
                {
                    std::vector<double> distances = distances_details(mapped_elements).get_distances();
                    double sum = std::accumulate(distances.begin(), distances.end(), 0.0);
                    return sum / distances.size();
                }

                template<typename T>
                aligned_distances_details aligned_distance<T>::distances_details(std::vector<std::pair<std::vector<T>,std::vector<T> > > mapped_elements) const
                {
                    std::vector<std::vector<std::vector<std::vector<double> > > > matrices;

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

                        std::vector<std::vector<std::vector<double> > > warping_matrix = distance_measure_->warping_matrix(pair.first,pair.second);

                        if (n + 1 != warping_matrix.size() || m + 1 != warping_matrix.at(0).size() || m + 1 != warping_matrix.at(n).at(m).size())
                        {
                            throw std::invalid_argument("Warping matrix size does not match. Warping matrices must have an additional first row and first column and the last element must contain all possible starting positions.");
                        }

                        matrices.push_back(warping_matrix);
                    }

                    double min_distance = std::numeric_limits<double>::infinity();
                    std::size_t min_startpos = 0;
                    std::size_t min_endpos = m;

                    for (std::size_t startpos = 0; startpos <= m; startpos++)
                    {
                        for (std::size_t endpos = startpos; endpos <= m; endpos++)
                        {

                            double distance_sum = 0;
                            for (std::size_t mat = 0; mat < matrices.size(); mat++)
                            {
                                distance_sum += matrices.at(mat).at(n).at(endpos).at(startpos);
                            }

                            if (distance_sum < min_distance || (distance_sum <= min_distance && (endpos - startpos < min_endpos - min_startpos)))
                            {
                                min_distance = distance_sum;

                                min_startpos = startpos;
                                min_endpos = endpos;
                            }
                        }
                    }

                    // set the distances
                    std::vector<double> distances;
                    for (std::size_t mat = 0; mat < matrices.size(); mat++)
                    {
                        distances.push_back(matrices.at(mat).at(n).at(min_endpos).at(min_startpos));
                    }

                    // set the warping paths
                    std::vector<std::vector<std::pair<std::size_t,std::size_t> > > warping_paths;
                    for (std::size_t mat = 0; mat < matrices.size(); mat++)
                    {
                        std::vector<std::pair<std::size_t,std::size_t> > warping_path;
                        std::size_t wn = n;
                        std::size_t wm = min_endpos;

                        while (wn >= 1 && wm >= min_startpos+1 && (1 != wn || min_startpos+1 != wm))
                        {
                            warping_path.push_back(std::make_pair(wn,wm));

                            if (1 == wn)
                            {
                                wm--;
                            }
                            else if (min_startpos == wm)
                            {
                                wn--;
                            }
                            else
                            {
                                //argmin of D(n-1,m-1),D(n-1,m),D(n,m-1), lexicographically smalles pair
                                double n1 = matrices.at(mat).at(wn-1).at(wm).at(min_startpos);
                                double m1 = matrices.at(mat).at(wn).at(wm-1).at(min_startpos);
                                double nm1 = matrices.at(mat).at(wn-1).at(wm-1).at(min_startpos);
                                double min = std::min(n1, std::min(m1, nm1));

                                if (min == nm1)
                                {
                                    wn--;
                                    wm--;
                                }
                                else if (min == n1)
                                {
                                    wn--;
                                }
                                else
                                {
                                    wm--;
                                }
                            }
                        }

                        warping_path.push_back(std::make_pair(1, min_startpos+1));

                        std::reverse(warping_path.begin(), warping_path.end());

                        warping_paths.push_back(warping_path);
                    }

                    return aligned_distances_details(min_startpos, min_endpos, distances, warping_paths);
                }

        } // namespace math
} // namespace mae

#endif // MAE_MATH_ALIGNED_DISTANCE_HPP_
