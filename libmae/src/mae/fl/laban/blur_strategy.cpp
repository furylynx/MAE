#include "blur_strategy.hpp"

namespace mae
{
    namespace fl
    {
        namespace laban
        {

            blur_strategy::blur_strategy(e_blur_strategy strategy, double beats)
            {
                strategy_ = strategy;
                beats_ = beats;
            }

            blur_strategy::~blur_strategy()
            {
            }

            e_blur_strategy blur_strategy::get_blur_strategy() const
            {
                return strategy_;
            }

            double blur_strategy::get_beats() const
            {
                return beats_;
            }

            std::string blur_strategy::str() const
            {
                std::stringstream sstr;

                if (e_blur_strategy::BLUR == strategy_)
                {
                    sstr << "blur_strategy: [" << e_blur_strategy_c::str(strategy_) << ", " << beats_ << "]";
                }
                else
                {
                    sstr << "blur_strategy: [" << e_blur_strategy_c::str(strategy_) << "]";
                }

                return sstr.str();
            }

        } // namespace laban
    } // namespace fl
} // namespace mae