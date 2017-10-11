#include "decision_maker.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			decision_maker::decision_maker(int beats_per_measure, double tolerance, double start_pose_tolerance)
			{
				beats_per_measure_ = beats_per_measure;
				tolerance_ = tolerance;
				start_pose_tolerance_ = start_pose_tolerance;
			}

			decision_maker::~decision_maker()
			{
			}

			void decision_maker::set_recognition_tolerance(double tolerance)
			{
				tolerance_ = tolerance;
			}

			double decision_maker::get_recognition_tolerance()
			{
				return tolerance_;
			}

			void decision_maker::set_start_pose_tolerance(double start_pose_tolerance)
			{
				start_pose_tolerance_ = start_pose_tolerance;
			}

			double decision_maker::get_start_pose_tolerance()
			{
				return start_pose_tolerance_;
			}

			bool decision_maker::decide_match(std::shared_ptr<i_movement> stream_item,
					std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item,
					std::shared_ptr<i_movement> tree_item_predecessor)
			{

				//stream's element is start pose, but stored one's element is not => no match
				if (stream_item->get_measure() == 0 && tree_item->get_measure() != 0)
				{
					return false;
				}

				if (stream_item->get_measure() != 0 && tree_item->get_measure() == 0)
				{
					//tree item is start pose, thus look in stream whether symbol that matches the criteria
					if (!distance_okay(stream_item_predecessor, stream_item, tree_item_predecessor))
					{
						return false;
					}
				}
				else
				{
					//either both items are start poses or none; check position and duration
					if (!check_position_duration(stream_item, stream_item_predecessor, tree_item,
							tree_item_predecessor))
					{
						return false;
					}
				}

				return check_type(stream_item, tree_item);
			}

			bool decision_maker::decide_insertion(std::shared_ptr<i_movement> add_item,
					std::shared_ptr<i_movement> add_item_predecessor, std::shared_ptr<i_movement> tree_item,
					std::shared_ptr<i_movement> tree_item_predecessor)
			{

				//not both start pose or both movement
				if ((add_item->get_measure() == 0 && tree_item->get_measure() != 0) || (add_item->get_measure() != 0 && tree_item->get_measure() == 0))
				{
					return false;
				}

				//either both items are start poses or none; check position and duration
				if (!check_position_duration(add_item, add_item_predecessor, tree_item,
						tree_item_predecessor))
				{
					return false;
				}

				return check_type(add_item, tree_item);
			}

			bool decision_maker::check_position_duration(std::shared_ptr<i_movement> stream_item,
					std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item,
					std::shared_ptr<i_movement> tree_item_predecessor)
			{
				//check position - only if predecessor not null, otherwise outside check will do this for us
				double pos_deviation = 0;

				//don't check position of predecessors are unknown or one of the elements is a starting pose
				if (stream_item_predecessor != nullptr && tree_item_predecessor != nullptr
						&& stream_item->get_measure() != 0 && tree_item->get_measure() != 0)
				{
					//check position approx. equal if predecessors defined
					double pos_a = (stream_item_predecessor->get_measure() - stream_item->get_measure())
							* beats_per_measure_ + (stream_item_predecessor->get_beat() - stream_item->get_beat());
					double pos_b = (tree_item_predecessor->get_measure() - tree_item->get_measure())
							* beats_per_measure_ + (tree_item_predecessor->get_beat() - tree_item->get_beat());
					pos_deviation = std::abs(pos_a - pos_b);
				}

				//check duration
				double dur_deviation = std::abs(stream_item->get_duration() - tree_item->get_duration());

				if (pos_deviation > tolerance_ || dur_deviation > tolerance_)
				{
					return false;
				}

				return true;
			}

			bool decision_maker::distance_okay(std::shared_ptr<i_movement> dist_from,
					std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check)
			{
				if (check == nullptr || dist_from == nullptr)
				{
					return true;
				}

				//distance between from and to (distance to potential start pose big enough, so that it actually is the start pose)
				double beat_dist = (dist_from->get_measure() * beats_per_measure_ + dist_from->get_beat())
						- (dist_to->get_measure() * beats_per_measure_ + dist_to->get_beat() + dist_to->get_duration());

				//use beat pos to check distance of the first movement to the start pose
				double beat_pos = (check->get_measure() - 1) * beats_per_measure_ + check->get_beat();

				//check whether position of check is less than the distance to potential start pose
				//if distance is less, the start pose is okay
				if ((beat_pos - beat_dist) < start_pose_tolerance_)
				{
					return true;
				}

				return false;
			}

			bool decision_maker::check_type(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b)
			{
				return a->symbol_equals(b);
			}

			bool decision_maker::position_okay(double dist_to_last, double set_value, bool check_startpose)
			{
				if (!check_startpose)
				{
					return (std::abs(set_value - dist_to_last) < tolerance_);
				}
				else
				{
					//check whether position of check is less than the distance to potential start pose
					//if distance is less, the start pose is okay
					return ((set_value - dist_to_last) < start_pose_tolerance_);

				}
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
