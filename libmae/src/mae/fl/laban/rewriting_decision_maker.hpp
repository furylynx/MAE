#ifndef MAE_FL_LABAN_REWRITING_DECISION_MAKER_HPP_
#define MAE_FL_LABAN_REWRITING_DECISION_MAKER_HPP_

//custom includes
#include "i_decision_maker.hpp"

#include "i_movement.hpp"
#include "movement.hpp"
#include "path.hpp"
#include "room_direction.hpp"
#include "relationship_bow.hpp"

//global includes
//...


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_decision_maker: public i_decision_maker<i_movement>
			{
				public:
					/**
					 * Creates a new rewriting decision maker which is used to decide whether two movements are equal
					 * for sequences that are meant to be replaced. Therefore the timing does not matter but only the symbols.
					 */
					rewriting_decision_maker();
					virtual ~rewriting_decision_maker();

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
					 * Checks whether the two elements match in order to provide the decision result for a match. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param stream_item The element for the sequence to be matched.
					 * @param stream_item_predecessor The predecessor element for the sequence to be matched.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return True if elements match.
					 */
					virtual bool decide_match(std::shared_ptr<i_movement> stream_item, std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item, std::shared_ptr<i_movement> tree_item_predecessor);

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
					virtual bool decide_insertion(std::shared_ptr<i_movement> add_item, std::shared_ptr<i_movement> add_item_predecessor, std::shared_ptr<i_movement> tree_item, std::shared_ptr<i_movement> tree_item_predecessor);

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
					 * Checks whether the two movements are of the same type.
					 *
					 * @param a The first movement.
					 * @param b The second movement.
					 * @return True if matching.
					 */
					virtual bool check_type(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_REWRITING_DECISION_MAKER_HPP_
