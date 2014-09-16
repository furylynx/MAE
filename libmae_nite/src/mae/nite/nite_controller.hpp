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
				nite_controller(std::string config_path, int max_users = 15, bool debug = false);
				virtual ~nite_controller();

				virtual bool was_keyboard_hit();

				virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(unsigned int each_n_frames = 1);

			protected:
				virtual void initialize();

				virtual bool file_exists(const char * file) const;
				virtual void check_rc(XnStatus nRetVal, std::string what) const;

				//********************
				//protected callback methods
				//********************
				virtual void cb_user_newuser(xn::UserGenerator& generator, XnUserID nId);
				virtual void cb_user_lostuser(xn::UserGenerator& generator, XnUserID nId);
				virtual void cb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId);
				virtual void cb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID nId);
				virtual void cb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability, XnUserID nId, XnCalibrationStatus eStatus);

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
				static void XN_CALLBACK_TYPE scb_user_newuser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
				static void XN_CALLBACK_TYPE scb_user_lostuser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
				static void XN_CALLBACK_TYPE scb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie);
				static void XN_CALLBACK_TYPE scb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie);
				static void XN_CALLBACK_TYPE scb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability, XnUserID nId, XnCalibrationStatus eStatus, void* pCookie);

		};

	} // namespace eventing
} // namespace mae

#endif // NITE_CONTROLLER_HPP_
