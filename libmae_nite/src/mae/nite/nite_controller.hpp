/*
 * nite_controller.hpp
 *
 *  Created on: 15.09.2014
 *      Author: keks
 */

#ifndef NITE_CONTROLLER_HPP_
#define NITE_CONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <fstream>
#include <vector>
#include <memory>

//NiTE includes
#include <Linux-x86/XnPlatformLinux-x86.h>
#include <XnOS.h>
#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnStatus.h>
#include <Linux-x86/XnPlatformLinux-x86.h>
#include <XnCppWrapper.h>



//mae includes
#include <mae/general_skeleton.hpp>

namespace mae
{
	namespace nite
	{

		class nite_controller
		{
			public:
				/**
				 * Creates a new controller for an OpenNI/NiTE camera.
				 *
				 * @param config_path The configuration for the camera.
				 * @param max_users The maximal number of users.
				 * @param debug The debug flag.
				 */
				nite_controller(std::string config_path, unsigned int max_users = 15, bool debug = false);
				virtual ~nite_controller();


				/**
				 * Waits until the next (n-th) frame is processed and returns the skeleton data on that frame.
				 * This is a blocking method.
				 *
				 * @param each_n_frames The n-th frame to be processed.
				 * @return The skeleton data.
				 */
				virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(unsigned int each_n_frames = 1);

				/**
				 * Returns true if the keyboard was hit since the start of the program.
				 *
				 * @return True if keyboard was hit.
				 */
				virtual bool was_keyboard_hit();

				/**
				 * Returns true if the keyboard was hit since the start of the program.
				 *
				 * @return True if keyboard was hit.
				 */
				static bool xn_was_keyboard_hit();

			protected:
				/**
				 * Initializes the controller.
				 */
				virtual void initialize();

				/**
				 * Checks for existence of the file.
				 *
				 * @param file The path to the file.
				 * @return True if existing.
				 */
				virtual bool file_exists(const char * file) const;

				/**
				 * Checks the returned status for errors and throws an exception if any.
				 *
				 * @param nRetVal The status to be checked.
				 * @param what The exception message to be sent.
				 */
				virtual void check_rc(XnStatus nRetVal, std::string what) const;

				//********************
				//protected callback methods
				//********************

				/**
				 * Is invoked whenever a new user is detected.
				 *
				 * @param generator The user generator.
				 * @param new_id The user's id.
				 */
				virtual void cb_user_newuser(xn::UserGenerator& generator, XnUserID new_id);

				/**
				 * Is invoked whenever a user is lost.
				 *
				 * @param generator The user generator.
				 * @param new_id The user's id.
				 */
				virtual void cb_user_lostuser(xn::UserGenerator& generator, XnUserID new_id);

				/**
				 *	Is invoked whenever a pose is detected.
				 *
				 * @param capability The detection capability.
				 * @param str_pose The pose char array.
				 * @param new_id The user's id.
				 */
				virtual void cb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* str_pose, XnUserID new_id);

				/**
				 * Is invoked whenever the calibration for a user is started.
				 *
				 * @param capability The detection capability.
				 * @param new_id The user's id.
				 */
				virtual void cb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID new_id);

				/**
				 * Is invoked whenever the calibration for a user is complete.
				 *
				 * @param capability The detection capability.
				 * @param new_id The user's id.
				 * @param e_status The calibration status.
				 */
				virtual void cb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability, XnUserID new_id, XnCalibrationStatus e_status);

			private:
				//members
				bool debug_;

				xn::Context context_;
				xn::ScriptNode script_node_;
				xn::UserGenerator user_generator_;

				XnBool b_needpose_;
				XnChar str_pose_[20];

				//configuration
				std::string config_path_;
				unsigned int max_users_;

				//fl stuff
				static bool initialized_;
				static std::vector<XnSkeletonJoint> joint_ids_;
				static std::vector<int> joint_ids_mae_;

				//********************
				//static callback methods
				//********************

				/**
				 * Is invoked whenever a new user is detected. Invokes the callback of the object in order to
				 * be overridable and being processed by the object.
				 *
				 * @param generator The user generator.
				 * @param new_id The user's id.
				 * @param p_cookie A user defined cookie. Here it is the pointer to the nite_controller object.
				 */
				static void XN_CALLBACK_TYPE scb_user_newuser(xn::UserGenerator& generator, XnUserID new_id, void* p_cookie);

				/**
				 * Is invoked whenever a user is lost. Invokes the callback of the object in order to be
				 * overridable and being processed by the object.
				 *
				 * @param generator The user generator.
				 * @param new_id The user's id.
				 * @param p_cookie A user defined cookie. Here it is the pointer to the nite_controller object.
				 */
				static void XN_CALLBACK_TYPE scb_user_lostuser(xn::UserGenerator& generator, XnUserID new_id, void* p_cookie);

				/**
				 *	Is invoked whenever a pose is detected. Invokes the callback of the object in order to be
				 *	overridable and being processed by the object.
				 *
				 * @param capability The detection capability.
				 * @param str_pose The pose char array.
				 * @param new_id The user's id.
				 * @param p_cookie A user defined cookie. Here it is the pointer to the nite_controller object.
				 */
				static void XN_CALLBACK_TYPE scb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* str_pose, XnUserID new_id, void* p_cookie);

				/**
				 * Is invoked whenever the calibration for a user is started. Invokes the callback of the object
				 * in order to be overridable and being processed by the object.
				 *
				 * @param capability The detection capability.
				 * @param new_id The user's id.
				 * @param p_cookie A user defined cookie. Here it is the pointer to the nite_controller object.
				 */
				static void XN_CALLBACK_TYPE scb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID new_id, void* p_cookie);

				/**
				 * Is invoked whenever the calibration for a user is complete. Invokes the callback of the object
				 * in order to be overridable and being processed by the object.
				 *
				 * @param capability The detection capability.
				 * @param new_id The user's id.
				 * @param e_status The calibration status.
				 * @param p_cookie A user defined cookie. Here it is the pointer to the nite_controller object.
				 */
				static void XN_CALLBACK_TYPE scb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability, XnUserID new_id, XnCalibrationStatus e_status, void* p_cookie);

		};

	} // namespace eventing
} // namespace mae

#endif // NITE_CONTROLLER_HPP_
