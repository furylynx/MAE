/*
 * nitecontroller.cpp
 *
 *  Created on: 25.06.2014
 *      Author: keks
 */

#include "nitecontroller.hpp"

namespace lni
{

	nite_controller::nite_controller()
	{
		// TODO Auto-generated constructor stub

	}

	nite_controller::~nite_controller()
	{
		// TODO Auto-generated destructor stub
	}

	// Callback: New user was detected
	void nite_controller::User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d New User %d\n", epochTime, nId);
		// New user found
		if (g_bNeedPose)
		{
			g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
		}
		else
		{
			g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}
	// Callback: An existing user was lost
	void XN_CALLBACK_TYPE nite_controller::User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Lost user %d\n", epochTime, nId);
	}
	// Callback: Detected a pose
	void XN_CALLBACK_TYPE nite_controller::UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
		g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
		g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
	// Callback: Started calibration
	void XN_CALLBACK_TYPE nite_controller::UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Calibration started for user %d\n", epochTime, nId);
	}

	void XN_CALLBACK_TYPE nite_controller::UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		if (eStatus == XN_CALIBRATION_STATUS_OK)
		{
			// Calibration succeeded
			printf("%d Calibration complete, start tracking user %d\n", epochTime, nId);
			g_UserGenerator.GetSkeletonCap().StartTracking(nId);
		}
		else
		{
			// Calibration failed
			printf("%d Calibration failed for user %d\n", epochTime, nId);
			if(eStatus==XN_CALIBRATION_STATUS_MANUAL_ABORT)
			{
				printf("Manual abort occured, stop attempting to calibrate!");
				return;
			}
			if (g_bNeedPose)
			{
				g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
			}
			else
			{
				g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
			}
		}
	}

} // namespace lni
