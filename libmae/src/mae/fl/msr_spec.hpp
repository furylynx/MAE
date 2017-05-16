#ifndef MAE_FL_MSR_SPEC_HPP_
#define MAE_FL_MSR_SPEC_HPP_

//custom includes
#include "../hierarchy.hpp"
#include "../hierarchy_element.hpp"

//global includes
#include <map>
#include <memory>
#include <exception>

namespace mae
{
	namespace fl
	{

		class msr_spec
		{
			public:
				/**
				 * Creates a new specification for the msr import. The specification defines
				 * the IDs that are assigned to the rows in whicht the joint positions are
				 * given.
				 *
				 * @param string_id_map The map for the row number and the joint id.
				 * @param hierarchy The skeleton hierarchy to be used.
				 */
				msr_spec(std::map<unsigned int, int> id_map, std::shared_ptr<hierarchy> hierarchy, std::size_t lines_per_joint, std::size_t pos_line_index);
				virtual ~msr_spec();


				/**
				 * Returns the map that maps row number to joint id of the hierarchy.
				 *
				 * @return The map.
				 */
				virtual std::map<unsigned int, int> get_id_map() const;

				/**
				 * Returns the skeleton hierarchy.
				 *
				 * @return The hierarchy.
				 */
				virtual std::shared_ptr<hierarchy> get_hierarchy() const;


				/**
				 * Returns the number of lines which are used to provide information on one joint.
				 *
				 * @return The number of lines per joint used.
				 */
				virtual std::size_t get_lines_per_joint() const;

				/**
				 * Returns the line index of the line providing the 3D position information. This
				 * value is zero if only one line is used for each joint or when the position info
				 * line is the first of the amount of lines per joint.
				 *
				 * @return The line index.
				 */
				virtual std::size_t get_pos_line_index() const;

				/**
				 * Creates a default specification that fits the default hierarchy definition (OpenNI/NiTE skeleton).
				 *
				 * @return The default specification.
				 */
				static std::shared_ptr<msr_spec> default_spec();

				/**
				 * Creates a default specification that fits the default msr hierarchy definition (Kinect skeleton).
				 *
				 * @return The specification.
				 */
				static std::shared_ptr<msr_spec> default_msr_spec();



			private:
				std::map<unsigned int, int> id_map_;
				std::shared_ptr<hierarchy> hierarchy_;

				std::size_t lines_per_joint_;
				std::size_t pos_line_index_;

		};

	} // namespace fl
} // namespace mae

#endif // MAE_FL_MSR_SPEC_HPP_
