#ifndef MAE_FL_LABAN_DECISION_MAKER_HPP_
#define MAE_FL_LABAN_DECISION_MAKER_HPP_

//custom includes
#include "i_decision_maker.hpp"
#include "i_movement.hpp"
#include "movement.hpp"
#include "path.hpp"
#include "room_direction.hpp"
#include "relationship_bow.hpp"

//global includes
#include <iostream>
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_maker: public i_decision_maker<i_movement>
			{
				public:
					/**
					 * Creates a new decision maker.
					 *
					 * @param beats_per_measure The number of beats per measure for the present sequence of which movements are compared.
					 * @param tolerance The tolerance to be applied. It is given in beats and defines how many beats are accepted in deviance.
					 */
					decision_maker(int beats_per_measure, double tolerance = 0.5, double start_pose_tolerance = 0.5);
					virtual ~decision_maker();

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance);

					/**
					 * Returns the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @return The tolerance.
					 */
					virtual double get_recognition_tolerance();

					/**
					 * Sets the tolerance for the recognition for one sided start poses (set value is start pose but actual movement is not).
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_start_pose_tolerance(double start_pose_tolerance);

					/**
					 * Returns the tolerance for the recognition for one sided start poses (set value is start pose but actual movement is not).
					 *
					 *  @return The tolerance to be accepted.
					 */
					virtual double get_start_pose_tolerance();

					/**
					 * Checks whether the two elements match in order to provide the decision result for a match. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param stream_item The element for the sequence to be matched.
					 * @param stream_item_predecessor The predecessor element for the sequence to be matched.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return True if elements match.
					 */
					virtual bool decide_match(std::shared_ptr<i_movement> stream_item,
							std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item,
							std::shared_ptr<i_movement> tree_item_predecessor);

					/**
					 * Checks whether the two elements match in order to provide the decision result for an insertion. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param stream_item The element for the sequence to be added.
					 * @param stream_item_predecessor The predecessor element for the sequence to be added.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return
					 */
					virtual bool decide_insertion(std::shared_ptr<i_movement> add_item,
							std::shared_ptr<i_movement> add_item_predecessor, std::shared_ptr<i_movement> tree_item,
							std::shared_ptr<i_movement> tree_item_predecessor);

					/**
					 * Checks the distances of the last element in this column to the last element of all columns. The method takes
					 * care of start poses on the set value side, so that only minimum distance must match and not an interval.
					 *
					 * @param dist_to_last The distance to the last element of all columns.
					 * @param set_value The set value for the distance.
					 * @param check_startpose True if set value is to start pose but dist is not.
					 * @return True if accepted.
					 */
					virtual bool position_okay(double dist_to_last, double set_value, bool check_startpose);

				protected:
					/**
					 * Checks whether position and duration match.
					 *
					 * @param stream_item The element for the sequence to be matched.
					 * @param stream_item_predecessor The predecessor element for the sequence to be matched.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return True if positions and durations match.
					 */
					virtual bool check_position_duration(std::shared_ptr<i_movement> stream_item,
							std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item,
							std::shared_ptr<i_movement> tree_item_predecessor);

					/**
					 * Checks the distance between the first to parameters and then examines whether the third parameter is matching.
					 * This is used to check whether the start pose does also match. Therefore distance between the two elements of
					 * the streamed sequence (potential first movement dist_from and potential start pose dist_to) are compared to
					 * the position of the first movement in the registered sequence (set value).
					 *
					 * @param dist_from The distance from.
					 * @param dist_to The distance to.
					 * @param check The element to be checked to have enough distance.
					 * @return True if distance is okay.
					 */
					virtual bool distance_okay(std::shared_ptr<i_movement> dist_from,
							std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check);

					/**
					 * Checks whether the two movements are of the same type.
					 *
					 * @param a The first movement.
					 * @param b The second movement.
					 * @return True if matching.
					 */
					virtual bool check_type(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b);

				private:
					int beats_per_measure_;

					double tolerance_;
					double start_pose_tolerance_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_DECISION_MAKER_HPP_
