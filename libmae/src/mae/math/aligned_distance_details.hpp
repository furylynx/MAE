//
// Created on 2018-02-12
//

#ifndef MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP
#define MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP


namespace mae
{
    namespace math
    {

        class aligned_distance_details {
            public:

                /**
                 * Creates new details for the subsequence distance (start and end point for the subsequence and distance).
                 *
                 * @param startpos The start position.
                 * @param endpos The end position.
                 * @param distance The distance.
                 */
                aligned_distance_details(double startpos, double endpos, double distance);
                virtual ~aligned_distance_details();

                virtual double get_startpos() const;
                virtual double get_endpos() const;
                virtual double get_distance() const;

            private:
                double startpos_;
                double endpos_;
                double distance_;
        };


    } // namespace math
} // namespace mae

#endif //MAE_MATH_ALIGNED_DISTANCE_DETAILS_HPP
