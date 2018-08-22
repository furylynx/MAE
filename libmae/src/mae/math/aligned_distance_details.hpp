//
// Created on 2018-02-12
//

#ifndef MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP
#define MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP

//custom includes
//...

//global includes
#include <vector>
#include <utility>


namespace mae
{
    namespace math
    {

        class aligned_distance_details {
            public:

                /**
                 * Creates new details for the subsequence distance (start and end point for the subsequence, distance and warping path).
                 *
                 * @param startpos The start position.
                 * @param endpos The end position.
                 * @param distance The distance.
                 * @param warping_path The warping path (sequence of points in path).
                 */
                aligned_distance_details(double startpos, double endpos, double distance, std::vector<std::pair<std::size_t,std::size_t> > warping_path);
                virtual ~aligned_distance_details();

                /**
                 * Returns the start position of the aligned sequence.
                 *
                 * @return The start position.
                 */
                virtual double get_startpos() const;

                /**
                 * Returns the end position of the aligned sequence.
                 *
                 * @return The end position.
                 */
                virtual double get_endpos() const;

                /**
                 * Returns the distance value.
                 *
                 * @return The distance.
                 */
                virtual double get_distance() const;

                /**
                 * Returns the warping path.
                 *
                 * @return The warping path.
                 */
                virtual std::vector<std::pair<std::size_t,std::size_t> > get_warping_path() const;

            private:
                double startpos_;
                double endpos_;
                double distance_;
                std::vector<std::pair<std::size_t,std::size_t> > warping_path_;
        };


    } // namespace math
} // namespace mae

#endif //MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP
