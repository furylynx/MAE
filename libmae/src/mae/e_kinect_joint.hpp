#ifndef MAE_E_KINECT_JOINT_HPP_
#define MAE_E_KINECT_JOINT_HPP_

//custom includes
#include "mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{

	enum class e_kinect_joint : int
	{
			INVALID_KINECTJOINT = 0,
			WAIST,
			TORSO,
			NECK,
			HEAD,
			LEFT_SHOULDER,
			LEFT_ELBOW,
			LEFT_WRIST,
			LEFT_HAND,
			RIGHT_SHOULDER,
			RIGHT_ELBOW,
			RIGHT_WRIST,
			RIGHT_HAND,
			LEFT_HIP,
			LEFT_KNEE,
			LEFT_ANKLE,
			LEFT_FOOT,
			RIGHT_HIP,
			RIGHT_KNEE,
			RIGHT_ANKLE,
			RIGHT_FOOT,

			WRH, 		//dummy joint for waist, this joint is parent of the right hip
			WLH, 		//dummy joint for waist, this joint is parent of the left hip
			WT, 		//dummy joint for waist, this joint is parent of the torso

			NLS, 		//dummy joint for neck, this joint is parent of the left shoulder
			NRS, 		//dummy joint for neck, this joint is parent of the right shoulder
			NH, 		//dummy joint for neck, this joint is parent of the neck

			END_LH, 	//dummy joint for end site, this joint is child of the left hand
			END_RH, 	//dummy joint for end site, this joint is child of the right hand
			END_LF, 	//dummy joint for end site, this joint is child of the left foot
			END_RF, 	//dummy joint for end site, this joint is child of the right foot
			END_H,  	//dummy joint for end site, this joint is child of the head
	};

	class e_kinect_joint_c
	{
		public:
			/**
			 * Returns the string representation for this enum value.
			 *
			 * @param unit The element.
			 * @return The string representation.
			 */
			static std::string str(e_kinect_joint joint);

			/**
			 * Returns the integer value corresponding to this element.
			 *
			 * @param joint The element.
			 * @return The integer ID.
			 */
			static int to_int(e_kinect_joint joint);

			/**
			 * Returns a vector containing all possible enum values.
			 *
			 * @return A vector.
			 */
			static std::vector<e_kinect_joint> vec();

			/**
			 * Returns true if the joint ID represents a dummy joint.
			 *
			 * @param joint The element.
			 * @return True if dummy element.
			 */
			static bool is_dummy(e_kinect_joint joint);

			/**
			 * Returns true if the joint ID represents a torso joint.
			 *
			 * @param joint The element.
			 * @return True if torso element.
			 */
			static bool is_torso(e_kinect_joint joint);

			/**
			 * Parses the string and returns the corresponding element.
			 *
			 * @param str The string to be parsed.
			 * @return The element.
			 */
			static e_kinect_joint parse(std::string str);

	};

} // namespace mae

#endif // MAE_E_KINECT_JOINT_HPP_
