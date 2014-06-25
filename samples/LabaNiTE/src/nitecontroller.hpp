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
//...

//global includes
#include <XnCppWrapper.h>
#include <XnOpenNI.h>
#include <ni/Linux-x86/XnPlatformLinux-x86.h>
#include <ni/XnOS.h>

//typedefs
typedef	unsigned int		XnUInt32;
typedef	char				XnChar;
#define MAX_NUM_USERS 15

namespace lni
{

	class nite_controller
	{
		public:
			nite_controller();
			virtual ~nite_controller();

			void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
			void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/);
			void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/);
			void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/);
			void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/);


			//static
			static bool file_exists(const char * file);
			static XnStatus check_rc(XnStatus nRetVal, const char * what);

		private:
			xn::Context g_Context;
			xn::ScriptNode g_scriptNode;
			xn::UserGenerator g_UserGenerator;

			XnBool g_bNeedPose = FALSE;
			XnChar g_strPose[20] = "";

	};

} // namespace lni

#endif // NITECONTROLLER_HPP_
