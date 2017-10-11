#ifndef MAE_E_HAND_BONE_HPP_
#define MAE_E_HAND_BONE_HPP_

//custom includes
#include "mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{

	enum class e_hand_bone : int
	{
			INVALID_HAND_BONE = 	0,
			LEFT_THUMB = -12,
			LEFT_INDEX_FINGER = -13,
			LEFT_MIDDLE_FINGER = -14,
			LEFT_RING_FINGER = -15,
			LEFT_LITTLE_FINGER = -16,

			LEFT_THUMB_PROXIMAL_PHALANX = -17,
			LEFT_THUMB_INTERMEDIATE_PHALANX = -18,
			LEFT_THUMB_DISTAL_PHALANX = -19,

			LEFT_INDEX_FINGER_PROXIMAL_PHALANX = -20,
			LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX = -21,
			LEFT_INDEX_FINGER_DISTAL_PHALANX = -22,

			LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX = -23,
			LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX = -24,
			LEFT_MIDDLE_FINGER_DISTAL_PHALANX = -25,

			LEFT_RING_FINGER_PROXIMAL_PHALANX = -26,
			LEFT_RING_FINGER_INTERMEDIATE_PHALANX = -27,
			LEFT_RING_FINGER_DISTAL_PHALANX = -28,

			LEFT_LITTLE_FINGER_PROXIMAL_PHALANX = -29,
			LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX = -30,
			LEFT_LITTLE_FINGER_DISTAL_PHALANX = -31,

			RIGHT_THUMB = 12,
			RIGHT_INDEX_FINGER = 13,
			RIGHT_MIDDLE_FINGER = 14,
			RIGHT_RING_FINGER = 15,
			RIGHT_LITTLE_FINGER = 16,

			RIGHT_THUMB_PROXIMAL_PHALANX = 17,
			RIGHT_THUMB_INTERMEDIATE_PHALANX = 18,
			RIGHT_THUMB_DISTAL_PHALANX = 19,

			RIGHT_INDEX_FINGER_PROXIMAL_PHALANX = 20,
			RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX = 21,
			RIGHT_INDEX_FINGER_DISTAL_PHALANX = 22,

			RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX = 23,
			RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX = 24,
			RIGHT_MIDDLE_FINGER_DISTAL_PHALANX = 25,

			RIGHT_RING_FINGER_PROXIMAL_PHALANX = 26,
			RIGHT_RING_FINGER_INTERMEDIATE_PHALANX = 27,
			RIGHT_RING_FINGER_DISTAL_PHALANX = 28,

			RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX = 29,
			RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX = 30,
			RIGHT_LITTLE_FINGER_DISTAL_PHALANX = 31,

	};

	class e_hand_bone_c
	{
		public:
			/**
			 * Returns the string representation for this enum value.
			 *
			 * @param bone The element.
			 * @return The string representation.
			 */
			static std::string str(e_hand_bone bone);

			/**
			 * Returns the integer value corresponding to this element.
			 *
			 * @param bone The element.
			 * @return The integer ID.
			 */
			static int to_int(e_hand_bone bone);

			/**
			 * Returns a vector containing all possible enum values.
			 *
			 * @return A vector.
			 */
			static std::vector<e_hand_bone> vec();

			/**
			 * Returns a vector containing all possible enum values for one hand.
			 *
			 * @return A vector.
			 */
			static std::vector<e_hand_bone> vec_side(bool is_left);

			/**
			 * Parses the string and returns the corresponding element.
			 *
			 * @param str The string to be parsed.
			 * @return The element.
			 */
			static e_hand_bone parse(std::string str);

			/**
			 * Returns true if the bone is part of the left hand.
			 *
			 * @param bone The bone.
			 * @return True if part of the left hand. false otherwise
			 */
			static bool is_left(e_hand_bone bone);

			/**
			 * Returns true if the bone is part of the right hand.
			 *
			 * @param bone The bone.
			 * @return True if part of the right hand. false otherwise
			 */
			static bool is_right(e_hand_bone bone);

	};

} // namespace mae

#endif // MAE_E_HAND_BONE_HPP_
