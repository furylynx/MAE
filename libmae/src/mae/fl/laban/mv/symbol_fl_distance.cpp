#include "symbol_fl_distance.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				symbol_fl_distance::symbol_fl_distance(std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure)
				{

                    distance_measure_ = distance_measure;
				}

				symbol_fl_distance::~symbol_fl_distance()
				{
				}

				double symbol_fl_distance::distance(std::shared_ptr<i_symbol> element1, std::shared_ptr<i_symbol> element2) const
				{
                    if (element1->equals(element2))
                    {
                        return 0;
                    }

                    if (typeid(element1.get()) == typeid(element2.get()))
                    {
                        double distance = distance_measure_->distance(element1->feature_vector(), element2->feature_vector());

                        return distance;
                    }
                    else
                    {
                        return 10000;
                    }
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
