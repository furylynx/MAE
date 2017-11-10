//
// Created on 2017-11-08
//

#ifndef MAE_MATH_SUBSEQUENCE_SIMILARITY_DETAILS_HPP
#define MAE_MATH_SUBSEQUENCE_SIMILARITY_DETAILS_HPP



namespace mae
{
    namespace math
    {
        class subsequence_similarity_details
        {

        public:

            /**
             * Creates new details for the subsequence similarity (start and end point for the subsequence and similarity).
             *
             * @param startpos The start position.
             * @param endpos The end position.
             * @param similarity The similarity.
             */
            subsequence_similarity_details(double startpos, double endpos, double similarity);
            virtual ~subsequence_similarity_details();

            virtual double get_startpos() const;
            virtual double get_endpos() const;
            virtual double get_similarity() const;

        private:
            double startpos_;
            double endpos_;
            double similarity_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_SUBSEQUENCE_SIMILARITY_DETAILS_HPP
