#ifndef MAE_FL_LABAN_RELATIONSHIP_BOW_HPP_
#define MAE_FL_LABAN_RELATIONSHIP_BOW_HPP_

//custom includes
#include "i_movement.hpp"
#include "e_relationship_type.hpp"
#include "mv/relationship_endpoint.hpp"

#include "../../math/math.hpp"

//global includes
#include <string>
#include <memory>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class relationship_bow : public i_movement
			{
				public:
					/**
					 * Creates a new relationship bow.
					 *
					 * @param type The realationship type.
					 * @param grasping True if grasping.
					 * @param passing True if passing.
					 * @param hold True if hold.
					 * @param measure The measure in which the bow lies.
					 * @param beat The beat pos where the bow lies.
					 * @param left_endpoint The bow's left endpoint.
					 * @param right_endpoint The bow's right endpoint.
					 */
					relationship_bow(e_relationship_type type, bool grasping, bool passing, bool hold, unsigned int measure, double beat, std::shared_ptr<mv::relationship_endpoint> left_endpoint, std::shared_ptr<mv::relationship_endpoint> right_endpoint);
					virtual ~relationship_bow();


					/**
					 * Returns the relationship type.
					 *
					 * @return The type.
 					 */
					e_relationship_type get_type() const;

					/**
					 * Returns the grasping flag.
					 *
					 * @return True if grasping. False otherwise.
					 */
					bool get_grasping() const;

					/**
					 * Returns the passing flag.
					 *
					 * @return True if passing. False otherwise.
					 */
					bool get_passing() const;

					/**
					 * Returns the hold flag.
					 *
					 * @return True if hold. False otherwise.
					 */
					bool get_hold() const;

					/**
					 * Returns the right endpoint.
					 *
					 * @return The right entpoint.
					 */
					std::shared_ptr<mv::relationship_endpoint> get_left_endpoint() const;

					/**
					 * Returns the left endpoint.
					 *
					 * @return The left entpoint.
					 */
					std::shared_ptr<mv::relationship_endpoint> get_right_endpoint() const;

					/**
					 * Returns the column this movement is attached to. Room direction
					 * and path sign have their own specific column only for those signs
					 * and therefore return 0.
					 *
					 * @return The column id.
					 */
					virtual int get_column() const;

					/**
					 * Returns the measure in which this symbols begins.
					 * @return
					 */
					virtual unsigned int get_measure() const;

					/**
					 * Returns the beat in which this symbol begins.
					 *
					 * @return
					 */
					virtual double get_beat() const;

					/**
					 * Returns the duration of the symbol. Room direction symbols do not have a duration and will return 0.
					 *
					 * @return
					 */
					virtual double get_duration() const;

					/**
					 * Returns true if the i_movement elements are equal.
					 *
					 * @param a The movement to be compared to.
					 * @return True if equal.
					 */
					virtual bool equals(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns true if the symbols are equal. The position and duration are not regarded.
					 *
					 * @param a The movement to be compared to.
					 * @return True if types equal.
					 */
					virtual bool symbol_equals(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
					 *
					 * @param a The movement to be compared to.
					 * @return True if symbols equal.
					 */
					virtual bool all_types_equal(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns the symbol's feature vector without the length and position information.
					 *
					 * @param hierarchy_factor The factor for subelements.
					 * @return The feature vector.
					 */
					virtual std::vector<double> symbol_feature_vector(double hierarchy_factor = 0.5) const;

					/**
					 * Returns the XML representation for this element.
					 *
					 * @param indent The applied indent.
					 * @param namesp The prefixed XML namespace.
					 *
					 * @return The XML string.
					 */
					virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

					/**
					 * Returns the SVG representation for this element.
					 *
					 * @param posx The x pos.
					 * @param posy The y pos.
					 * @param width The width.
					 * @param height The height.
					 * @return The SVG.
					 */
					virtual std::string svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const;

					/**
					 * Recreates the movement by copying its members but changing the position in the staff.
					 *
					 * @param column The new column.
					 * @param measure The new measure.
					 * @param beat The new beat.
					 * @param duration The new duration.
					 * @return The new, recreated movement.
					 */
					virtual std::shared_ptr<i_movement> recreate(std::map<int, int> column_mapping, unsigned int measure, double beat, double duration) const;


					/**
					 * Returns the string representation for this element.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;

					friend std::ostream& operator<<(std::ostream& os, const relationship_bow& obj)
					{
						os << obj.str();
						return os;
					}

					friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<relationship_bow>& obj)
					{
						os << obj->str();
						return os;
					}


				private:
					e_relationship_type type_;
					bool grasping_;
					bool passing_;
					bool hold_;
					unsigned int measure_;
					double beat_;

					std::shared_ptr<mv::relationship_endpoint> left_endpoint_;
					std::shared_ptr<mv::relationship_endpoint> right_endpoint_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_RELATIONSHIP_BOW_HPP_
