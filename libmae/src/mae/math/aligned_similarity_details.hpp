//
// Created on 2017-11-08
//

#ifndef MAE_MATH_ALIGNED_SIMILARITY_DETAILS_HPP
#define MAE_MATH_ALIGNED_SIMILARITY_DETAILS_HPP

//custom includes
//...

//global includes
#include <vector>
#include <utility>

namespace mae
{
    namespace math
    {
        class aligned_similarity_details
        {

        public:

            /**
             * Creates new details for the subsequence similarity (start and end point for the subsequence and similarity).
             *
             * @param startpos The start position.
             * @param endpos The end position.
             * @param similarity The similarity.
             */
            aligned_similarity_details(double startpos, double endpos, double similarity);
            virtual ~aligned_similarity_details();

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
             * Returns the similarity.
             *
             * @return The similarity.
             */
            virtual double get_similarity() const;

        private:
            double startpos_;
            double endpos_;
            double similarity_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_ALIGNED_SIMILARITY_DETAILS_HPP
