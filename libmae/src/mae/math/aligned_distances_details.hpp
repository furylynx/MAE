//
// Created on 2018-02-12
//

#ifndef MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP
#define MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP

//custom includes
//...

//global includes
#include <vector>

namespace mae
{
    namespace math
    {

        class aligned_distances_details {
            public:

                /**
                 * Creates new details for multiple subsequences distances (start and end point for the subsequences and distances).
                 *
                 * @param startpos The start position.
                 * @param endpos The end position.
                 * @param distances The distances.
                 */
                aligned_distances_details(double startpos, double endpos, std::vector<double> distances);
                virtual ~aligned_distances_details();

                virtual double get_startpos() const;
                virtual double get_endpos() const;

                /**
                 * Returns the vector of distances in the same order the sequences were given.
                 * @return
                 */
                virtual std::vector<double> get_distances() const;

            private:
                double startpos_;
                double endpos_;
                std::vector<double> distances_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_ALIGNED_DISTANCES_DETAILS_HPP

