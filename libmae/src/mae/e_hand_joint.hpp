
#ifndef MAE_E_HAND_JOINT_HPP_
#define MAE_E_HAND_JOINT_HPP_

//custom includes
#include "mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{

	enum class e_hand_joint : int
	{
			INVALID_HAND_JOINT = 0,
			LEFT_WRIST,
			LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT,
			LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT,
			LEFT_THUMB_TIP,
			LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT,
			LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			LEFT_INDEX_FINGER_TIP,
			LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT,
			LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			LEFT_MIDDLE_FINGER_TIP,
			LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT,
			LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			LEFT_RING_FINGER_TIP,
			LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT,
			LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			LEFT_LITTLE_FINGER_TIP,
			RIGHT_WRIST,
			RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT,
			RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT,
			RIGHT_THUMB_TIP,
			RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT,
			RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			RIGHT_INDEX_FINGER_TIP,
			RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT,
			RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			RIGHT_MIDDLE_FINGER_TIP,
			RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT,
			RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			RIGHT_RING_FINGER_TIP,
			RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT,
			RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT,
			RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT,
			RIGHT_LITTLE_FINGER_TIP,
			LPT, 		//dummy joint for palm, this joint is parent of the left thumb
			LPI, 		//dummy joint for palm, this joint is parent of the left index finger
			LPM, 		//dummy joint for palm, this joint is parent of the left middle finger
			LPR, 		//dummy joint for palm, this joint is parent of the left ring finger
			LPL,  		//dummy joint for palm, this joint is parent of the left little finger
			RPT, 		//dummy joint for palm, this joint is parent of the right thumb
			RPI, 		//dummy joint for palm, this joint is parent of the right index finger
			RPM, 		//dummy joint for palm, this joint is parent of the right middle finger
			RPR, 		//dummy joint for palm, this joint is parent of the right ring finger
			RPL,  		//dummy joint for palm, this joint is parent of the right little finger
			END_LT, 	//dummy joint for end site, this joint is child of the left thumb tip
			END_LI, 	//dummy joint for end site, this joint is child of the left index finger tip
			END_LM, 	//dummy joint for end site, this joint is child of the left middle finger tip
			END_LR, 	//dummy joint for end site, this joint is child of the left ring finger tip
			END_LL, 	//dummy joint for end site, this joint is child of the left little finger tip
			END_RT, 	//dummy joint for end site, this joint is child of the right thumb tip
			END_RI, 	//dummy joint for end site, this joint is child of the right index finger tip
			END_RM, 	//dummy joint for end site, this joint is child of the right middle finger tip
			END_RR, 	//dummy joint for end site, this joint is child of the right ring finger tip
			END_RL, 	//dummy joint for end site, this joint is child of the right little finger tip
	};

	class e_hand_joint_c
	{
		public:
			/**
			 * Returns the string representation for this enum value.
			 *
			 * @param joint The element.
			 * @return The string representation.
			 */
			static std::string str(e_hand_joint joint);

			/**
			 * Returns the integer value corresponding to this element.
			 *
			 * @param joint The element.
			 * @return The integer ID.
			 */
			static int to_int(e_hand_joint joint);

			/**
			 * Returns a vector containing all possible enum values.
			 *
			 * @return A vector.
			 */
			static std::vector<e_hand_joint> vec();

			/**
			 * Returns true if the joint ID represents a dummy joint.
			 *
			 * @param joint The element.
			 * @return True if dummy element.
			 */
			static bool is_dummy(e_hand_joint joint);

			/**
			 * Returns true if the joint ID represents a palm joint.
			 *
			 * @param joint The element.
			 * @return True if torso element.
			 */
			static bool is_palm(e_hand_joint joint);

			/**
			 * Parses the string and returns the corresponding element.
			 *
			 * @param str The string to be parsed.
			 * @return The element.
			 */
			static e_hand_joint parse(std::string str);

	};

} // namespace mae

#endif // MAE_E_HAND_JOINT_HPP_
