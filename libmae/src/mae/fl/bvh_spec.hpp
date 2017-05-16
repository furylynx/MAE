#ifndef MAE_FL_BVHSPEC_HPP_
#define MAE_FL_BVHSPEC_HPP_

//custom includes
#include "../e_joint.hpp"
#include "../e_hand_joint.hpp"
#include "../mstr.hpp"

//global includes
#include <map>
#include <string>
#include <memory>

namespace mae
{
	namespace fl
	{

		class bvh_spec
		{
		public:
			/**
             * Creates a new specification for the bvh import. The specification defines
             * the IDs that are assigned to the read string values of the joints. If the
             * id map is empty the position of occurrence in the bvh file is used by the
             * reader. Additionally the base joints (as a system of reference, e.g. the
             * torso or the palm) can be defined by the basis map. If the basis map is
             * empty a suffix sharp '#' after the joint name is used to denote base
             * joints.
             *
             * The four anchor names are the names of the joints used for the left-right
             * top-down direction.
             *
             * All strings should be present in lowercase!
             *
             * @param left_anchor
             * @param right_anchor
             * @param top_anchor
             * @param bottom_anchor
             * @param string_id_map
             * @param string_basis_map A map the determine base joints for the system of reference (e.g. the torso or the palm).
             */
			bvh_spec(std::string left_anchor, std::string right_anchor, std::string top_anchor, std::string bottom_anchor, std::map<std::string, int> string_id_map, std::map<std::string, bool> string_basis_map);
			virtual ~bvh_spec();

			/**
             * Returns the string to id map.
             *
             * @return The string to id map.
             */
			virtual std::map<std::string, int> get_id_map() const;

			/**
             * Returns the string to base joint map.
             *
             * @return
             */
			//[[deprecated("Replaced by get_basis_map().")]]
			virtual std::map<std::string, bool> get_torso_map() const;

			/**
			 * Returns the string to base joint map.
			 *
			 * @return
			 */
			virtual std::map<std::string, bool> get_basis_map() const;

			/**
             * Returns the anchor's joint name.
             *
             * @return The name.
             */
			virtual std::string get_left_anchor();

			/**
             * Returns the anchor's joint name.
             *
             * @return The name.
             */
			virtual std::string get_right_anchor();

			/**
             * Returns the anchor's joint name.
             *
             * @return The name.
             */
			virtual std::string get_top_anchor();

			/**
             * Returns the anchor's joint name.
             *
             * @return The name.
             */
			virtual std::string get_bottom_anchor();

			/**
             * Creates a default specification that suits the default hierarchy definition.
             *
             * @return The default specification.
             */
			static std::shared_ptr<bvh_spec> default_spec();

			/**
			 * Creates a default specification that suits the default hand hierarchy definition.
			 *
			 * @param is_left True for the left hand. False otherwise.
			 * @return The default hand specification.
			 */
			static std::shared_ptr<bvh_spec> default_hand_spec(bool is_left);

		private:
			std::map<std::string, int> string_id_map_;
			std::map<std::string, bool> string_basis_map_;

			std::string left_anchor_;
			std::string right_anchor_;
			std::string top_anchor_;
			std::string bottom_anchor_;

		};

	} // namespace fl
} // namespace mae

#endif // MAE_FL_BVHSPEC_HPP_
