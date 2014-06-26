/*
 * nitecontroller.hpp
 *
 *  Created on: 25.06.2014
 *      Author: keks
 */

#ifndef NITECONTROLLER_HPP_
#define NITECONTROLLER_HPP_

//eclipse indexer fix

//custom includes
#include <model/general_skeleton.hpp>

//global includes
#include <fstream>
#include <vector>
#include <memory>

#include <XnCppWrapper.h>
//#include <XnOpenNI.h>
#include <ni/Linux-x86/XnPlatformLinux-x86.h>
//#include <ni/XnOS.h>

//typedefs
//typedef	unsigned int		XnUInt32;
//typedef	char				XnChar;
//#define MAX_NUM_USERS 15

#define SAMPLE_XML_PATH "../../../../workspace-openni-nite/SamplesConfig.xml"
#define SAMPLE_XML_PATH_LOCAL "SamplesConfig.xml"

#define SKEL_STORE_PATH "../../../../workspace-openni-nite/"



namespace lni
{

	class nite_controller
	{
		public:
			static void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
			static void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/);
			static void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/);
			static void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/);
			static void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/);


			//static
			static bool file_exists(const char * file);
			static void check_rc(XnStatus nRetVal, const char * what);

			static std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(unsigned int each_n_frames = 1);

			static void close();

		private:
			static xn::Context g_Context;
			static xn::ScriptNode g_scriptNode;
			static xn::UserGenerator g_UserGenerator;

			static XnBool g_bNeedPose;
			static XnChar xn_g_strPose[20];

			static const unsigned int max_users = 15;


			//fl stuff
			static std::vector<XnSkeletonJoint> joint_ids;
			static std::vector<int> joint_ids_mae;

			static unsigned int frame_counter;

			static bool initialized;



			static void initialize();

	};

} // namespace lni

#endif // NITECONTROLLER_HPP_
