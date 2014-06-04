////============================================================================
//// Name        : LabaNiTE.cpp
//// Author      : Børge
//// Version     :
//// Copyright   :
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//
////#include <libXnVNITE_1_5_2>
//
////include openni with -lOpenNi
//#include <ni/XnCppWrapper.h>
//
////#include <XnOpenNI.h>
//
////include openni/nite with -lXnVCNITE_1_5_2
////#include <nite/XnCommon.h>
//
////TODO if you want to include boost use -lboost_* with * for the part used e.g. -lboost_system
////#include <boost/asio/serial_port.hpp>
//
//
//int main(int argc, char* argv[]) {
//
//	//just print startup message
//	std::cout << "LabaNiTE started!" << std::endl;
//
//
//
//
//	//just print exit message
//	std::cout << "LabaNiTE stopped!" << std::endl;
//
//	return 0;
//}

/*****************************************************************************
 * *
 * OpenNI 1.x Alpha *
 * Copyright (C) 2012 PrimeSense Ltd. *
 * *
 * This file is part of OpenNI. *
 * *
 * Licensed under the Apache License, Version 2.0 (the "License"); *
 * you may not use this file except in compliance with the License. *
 * You may obtain a copy of the License at *
 * *
 * http://www.apache.org/licenses/LICENSE-2.0 *
 * *
 * Unless required by applicable law or agreed to in writing, software *
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 * See the License for the specific language governing permissions and *
 * limitations under the License. *
 * *
 *****************************************************************************/
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
//#include <stddef.h>
#include <cstddef>
#include <cstdlib>

#include <XnCppWrapper.h>
#include <XnOpenNI.h>
#include <ni/Linux-x86/XnPlatformLinux-x86.h>
#include <ni/XnOS.h>

//fl : general includes
#include <memory>
#include <fstream>
#include <sstream>

#include <iostream>
#include <iomanip>
#include <ctime>

//fl : mae includes
#include <fl/FLMovementController.hpp>
#include <model/GeneralSkeleton.hpp>
#include <model/GeneralJoint.hpp>
#include <model/MAEJ.hpp>

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define SAMPLE_XML_PATH "../../../../workspace-openni-nite/SamplesConfig.xml"
#define SAMPLE_XML_PATH_LOCAL "SamplesConfig.xml"

#define SKEL_STORE_PATH "../../../../workspace-openni-nite/"

//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
xn::Context g_Context;
xn::ScriptNode g_scriptNode;
xn::UserGenerator g_UserGenerator;

XnBool g_bNeedPose = FALSE;
XnChar g_strPose[20] = "";

#define MAX_NUM_USERS 15

//fl globals
mae::fl::FLMovementController move;

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

XnBool fileExists(const char *fn)
{
	XnBool exists;
	xnOSDoesFileExist(fn, &exists);
	return exists;
}

// Callback: New user was detected
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
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
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Lost user %d\n", epochTime, nId);
}
// Callback: Detected a pose
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
	g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
	g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}
// Callback: Started calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Calibration started for user %d\n", epochTime, nId);
}

void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/)
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

#define CHECK_RC(nRetVal, what) \
if (nRetVal != XN_STATUS_OK) \
{ \
printf("%s failed: %s\n", what, xnGetStatusString(nRetVal)); \
return nRetVal; \
}

int main()
{
	//----------
	// fl : custom init
	//----------
	//fl : setup movement controller
	move = mae::fl::FLMovementController();

	//fl : setup joint ids
	std::vector<XnSkeletonJoint> joint_ids;
	std::vector<int> joint_ids_mae;

	joint_ids.push_back(XN_SKEL_LEFT_HIP);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_HIP);

	joint_ids.push_back(XN_SKEL_RIGHT_HIP);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_HIP);

	joint_ids.push_back(XN_SKEL_TORSO);
	joint_ids_mae.push_back(mae::MAEJ_TORSO);

	joint_ids.push_back(XN_SKEL_LEFT_SHOULDER);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_SHOULDER);

	joint_ids.push_back(XN_SKEL_RIGHT_SHOULDER);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_SHOULDER);

	joint_ids.push_back(XN_SKEL_NECK);
	joint_ids_mae.push_back(mae::MAEJ_NECK);

	joint_ids.push_back(XN_SKEL_HEAD);
	joint_ids_mae.push_back(mae::MAEJ_HEAD);

	joint_ids.push_back(XN_SKEL_LEFT_ELBOW);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_ELBOW);

	joint_ids.push_back(XN_SKEL_LEFT_HAND);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_HAND);

	joint_ids.push_back(XN_SKEL_RIGHT_ELBOW);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_ELBOW);

	joint_ids.push_back(XN_SKEL_RIGHT_HAND);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_HAND);

	joint_ids.push_back(XN_SKEL_LEFT_KNEE);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_KNEE);

	joint_ids.push_back(XN_SKEL_LEFT_FOOT);
	joint_ids_mae.push_back(mae::MAEJ_LEFT_FOOT);

	joint_ids.push_back(XN_SKEL_RIGHT_KNEE);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_KNEE);

	joint_ids.push_back(XN_SKEL_RIGHT_FOOT);
	joint_ids_mae.push_back(mae::MAEJ_RIGHT_FOOT);

	int k = 0;
	const int frame_each_k = 120;
	const int max_k = 60000;
	const bool store_skels = true;

	//----------
	//NiTE initialization stuff here
	//----------
	XnStatus nRetVal = XN_STATUS_OK;
	xn::EnumerationErrors errors;

	const char *fn = NULL;
	if (fileExists(SAMPLE_XML_PATH))
		fn = SAMPLE_XML_PATH;
	else if (fileExists(SAMPLE_XML_PATH_LOCAL))
		fn = SAMPLE_XML_PATH_LOCAL;
	else
	{
		printf("Could not find '%s' nor '%s'. Aborting.\n", SAMPLE_XML_PATH, SAMPLE_XML_PATH_LOCAL);
		return XN_STATUS_ERROR;
	}
	printf("Reading config from: '%s'\n", fn);

	nRetVal = g_Context.InitFromXmlFile(fn, g_scriptNode, &errors);
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (nRetVal);
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
		return (nRetVal);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected;
	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
	{
		printf("Supplied user generator doesn't support skeleton\n");
		return 1;
	}
	nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
	CHECK_RC(nRetVal, "Register to user callbacks");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart, NULL,
			hCalibrationStart);
	CHECK_RC(nRetVal, "Register to calibration start");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(UserCalibration_CalibrationComplete, NULL,
			hCalibrationComplete);
	CHECK_RC(nRetVal, "Register to calibration complete");

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
	{
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
		{
			printf("Pose required, but not supported\n");
			return 1;
		}
		nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseDetected(UserPose_PoseDetected, NULL,
				hPoseDetected);
		CHECK_RC(nRetVal, "Register to Pose Detected");
		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");

	XnUserID aUsers[MAX_NUM_USERS];
	XnUInt16 nUsers;
	XnSkeletonJointTransformation torsoJoint;

	printf("Starting to run\n");
	if (g_bNeedPose)
	{
		printf("Assume calibration pose\n");
	}

	while (!xnOSWasKeyboardHit())
	{
		g_Context.WaitOneUpdateAll(g_UserGenerator);
		// print the torso information for the first user already tracking
		nUsers = MAX_NUM_USERS;
		g_UserGenerator.GetUsers(aUsers, nUsers);
		for (XnUInt16 i = 0; i < nUsers; i++)
		{
			//if user is not tracked continue with next one
			if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]) == FALSE)
				continue;

//            g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],XN_SKEL_TORSO,torsoJoint);
//                printf("user %d: head at (%6.2f,%6.2f,%6.2f)\n",aUsers[i],
//                                                                torsoJoint.position.position.X,
//                                                                torsoJoint.position.position.Y,
//                                                                torsoJoint.position.position.Z);

			//limit to every frame_each_k seconds
			if (k % frame_each_k == 0)
			{
				//fl : generate GeneralSkeleton from NiTE joint
				std::shared_ptr<mae::model::GeneralSkeleton> skeleton = std::shared_ptr<mae::model::GeneralSkeleton>(
						new mae::model::GeneralSkeleton());

				// ofstream def
				std::ofstream* a_file;

				if (store_skels)
				{
					// filename string
					std::ostringstream filename;
					filename << SKEL_STORE_PATH << "skeleton" << k << ".txt";

					// create file
					a_file = new std::ofstream(filename.str());

					// print header to file
					*a_file << "// OpenNi/NiTE Skeleton and MAE General Skeleton" << std::endl;

					//print date to file
					std::time_t now = std::time(nullptr);
					std::tm now_local = *std::localtime(&now);
					*a_file << "// " << (now_local.tm_year + 1900) << '-' << (now_local.tm_mon + 1) << '-'
							<< now_local.tm_mday << " " << now_local.tm_hour << ":" << now_local.tm_min << ":"
							<< now_local.tm_sec << std::endl << std::endl;

					//print skeleton initialization to file
					*a_file
							<< "std::shared_ptr<mae::model::GeneralSkeleton> skeleton = std::shared_ptr<mae::model::GeneralSkeleton>(new mae::model::GeneralSkeleton());"
							<< std::endl << std::endl;
				}

				//iterate through all known joints
				for (unsigned int j = 0; j < joint_ids.size() && j < joint_ids_mae.size(); j++)
				{
					//temp NiTE joint
					XnSkeletonJointTransformation xn_joint;
					g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i], joint_ids[j], xn_joint);

					//setup mae joint and set skeleton up
					std::shared_ptr<mae::model::GeneralJoint> g_joint = std::shared_ptr<mae::model::GeneralJoint>(
							new mae::model::GeneralJoint(xn_joint.position.position.X, xn_joint.position.position.Y,
									xn_joint.position.position.Z));
					skeleton->setJoint((int) joint_ids_mae[j], g_joint);

					if (store_skels)
					{
						//print joint assignment to file (for later use)
						*a_file << "// " << mae::maej_str[joint_ids_mae[j]] << " (" << xn_joint.position.position.X << ", " << xn_joint.position.position.Y << ", "
								<< xn_joint.position.position.Z << ")" << std::endl;
						*a_file << "skeleton->setJoint(" << (int) joint_ids_mae[j]
								<< ", std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint("
								<< (double) xn_joint.position.position.X << ", "
								<< (double) xn_joint.position.position.Y << ", "
								<< (double) xn_joint.position.position.Z << ")));" << std::endl;
					}
				}

				if (store_skels)
				{
					// Close the file stream explicitly
					a_file->close();
					delete a_file;
				}

				move.nextFrame(0, skeleton);

			}
		}

		k++;

		if (k > max_k)
		{
			k = 0;
		}

	}
	g_scriptNode.Release();
	g_UserGenerator.Release();
	g_Context.Release();

}
