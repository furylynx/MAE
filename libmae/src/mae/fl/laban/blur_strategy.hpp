#ifndef MAE_FL_LABAN_BLUR_STRATEGY_HPP_
#define MAE_FL_LABAN_BLUR_STRATEGY_HPP_

//custom includes
#include "e_blur_strategy.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>


namespace mae
{
    namespace fl
    {
        namespace laban
        {
            class blur_strategy {
                public:
                /**
                 * Creates a blur strategy.
                 *
                 * @param blurstrategy The strategy to apply.
                 * @param beats The number of beats to blur. Is ignored if strategy is NONE or HOLD.
                 */
                blur_strategy(e_blur_strategy strategy = e_blur_strategy::NONE_BLUR_STRATEGY, double beats = 0);

                virtual ~blur_strategy();

                /**
                 * Returns the type of the blur strategy.
                 *
                 * @return The strategy.
                 */
                e_blur_strategy get_blur_strategy() const;

                /**
                 * Returns the number of beats to blur. Is ignored if strategy is NONE or HOLD.
                 *
                 * @return The beats.
                 */
                virtual double get_beats() const;

                /**
                 * Returns the string representation for this element.
                 *
                 * @return The string.
                 */
                virtual std::string str() const;

                friend std::ostream& operator<<(std::ostream& os, const blur_strategy& obj)
                {
                    os << obj.str();
                    return os;
                }

                friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<blur_strategy>& obj)
                {
                    os << obj->str();
                    return os;
                }

                private:
                    e_blur_strategy strategy_;
                    double beats_;

            };

        } // namespace laban
    } // namespace fl
} // namespace mae

#endif //MAE_FL_LABAN_BLUR_STRATEGY_HPP_
