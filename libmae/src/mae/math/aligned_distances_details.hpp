//
// Created on 2018-02-12
//

#ifndef MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP
#define MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP

//custom includes
#include "warping_path_element.hpp"

//global includes
#include <vector>
#include <utility>

namespace mae
{
    namespace math
    {

        class aligned_distances_details {
            public:

                /**
                 * Creates new details for multiple subsequences distances (start and end point for the subsequences, distances and warping paths).
                 *
                 * @param startpos The start position.
                 * @param endpos The end position.
                 * @param distances The distances.
                 * @param warping_paths The warping paths.
                 */
                aligned_distances_details(double startpos, double endpos, std::vector<double> distances, std::vector<std::vector<warping_path_element> > warping_paths);
                virtual ~aligned_distances_details();

                /**
                 * Returns the start position for the alignment.
                 *
                 * @return The start position.
                 */
                virtual double get_startpos() const;
                
                /**
                 * Returns the end position for the alignment.
                 * @return
                 */
                virtual double get_endpos() const;

                /**
                 * Returns the vector of distances in the same order the sequences were given.
                 *
                 * @return The distances.
                 */
                virtual std::vector<double> get_distances() const;

                /**
                 * Returns the warping paths in the same order the sequences were given.
                 *
                 * @return The warping paths.
                 */
                virtual std::vector<std::vector<warping_path_element> > get_warping_paths() const;

            private:
                double startpos_;
                double endpos_;
                std::vector<double> distances_;
                std::vector<std::vector<warping_path_element> > warping_paths_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP

