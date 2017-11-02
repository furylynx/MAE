#include "movement_comparator.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			movement_comparator::movement_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure)
			{

				distance_measure_ = distance_measure;
			}

			movement_comparator::~movement_comparator()
			{
			}

			double movement_comparator::distance(std::shared_ptr<i_movement> element1, std::shared_ptr<i_movement> element2) const
			{
				if (element1->equals(element2))
				{
					return 0;
				}

				if (typeid(element1.get()) == typeid(element2.get()) && element1->all_types_equal(element2))
				{
					return distance_measure_->distance(element1->symbol_feature_vector(), element2->symbol_feature_vector());
				}
				else
				{
					return std::numeric_limits<double>::infinity();
				}
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
