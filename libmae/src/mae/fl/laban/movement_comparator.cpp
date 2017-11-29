#include "movement_comparator.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			movement_comparator::movement_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure, std::shared_ptr<mae::math::i_type_distance_measure> type_distance_measure, double distance_for_nullptr)
			{

				distance_measure_ = distance_measure;
				distance_for_nullptr_ = distance_for_nullptr;
                type_distance_measure_ = type_distance_measure;
			}

			movement_comparator::~movement_comparator()
			{
			}

			double movement_comparator::distance(std::shared_ptr<i_movement> element1, std::shared_ptr<i_movement> element2) const
			{
				if (nullptr == element1 && nullptr == element2)
				{
					//both elements null, hence no distance
					return 0;
				}
				else if (nullptr == element1 || nullptr == element2)
				{
					//one pf the elements is null, the other is not

					//use fixed distance if defined
					if (distance_for_nullptr_ >= 0)
					{
						return distance_for_nullptr_;
					}
					else
					{
						//compare with nullvector of same size
						std::vector<double> feature_vector;

						if (nullptr == element1)
						{
							feature_vector = element2->symbol_feature_vector();
						}
						else
						{
							feature_vector = element1->symbol_feature_vector();
						}

						std::vector<double> zero_vector (feature_vector.size(), 0);
						return distance_measure_->distance(feature_vector, zero_vector);
					}
				}
				else if (element1->equals(element2))
				{
					return 0;
				}
				else if (typeid(element1.get()) == typeid(element2.get()) && element1->all_types_equal(element2))
				{
					return distance_measure_->distance(element1->symbol_feature_vector(), element2->symbol_feature_vector());
				}
				else
				{
					return type_distance_measure_->distance(element1->get_type_path(), element2->get_type_path());
				}
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
