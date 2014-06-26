/*
 * nitecontroller.cpp
 *
 *  Created on: 25.06.2014
 *      Author: keks
 */

#include "nitecontroller.hpp"

namespace lni
{
	//member declaration
	xn::Context nite_controller::g_Context;
	xn::ScriptNode nite_controller::g_scriptNode;
	xn::UserGenerator nite_controller::g_UserGenerator;

	XnBool nite_controller::g_bNeedPose = FALSE;
	XnChar nite_controller::xn_g_strPose[20] = "";

	std::vector<XnSkeletonJoint> nite_controller::joint_ids;
	std::vector<int> nite_controller::joint_ids_mae;

	unsigned int nite_controller::frame_counter = 0;

	bool nite_controller::initialized = false;

	//methods

	// Callback: New user was detected
	void nite_controller::User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d New User %d\n", epochTime, nId);
		// New user found
		if (nite_controller::nite_controller::g_bNeedPose)
		{
			g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(xn_g_strPose, nId);
		}
		else
		{
			g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}

	// Callback: An existing user was lost
	void nite_controller::User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Lost user %d\n", epochTime, nId);
	}
	// Callback: Detected a pose
	void nite_controller::UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose,
			XnUserID nId, void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
		g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
		g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
	// Callback: Started calibration
	void nite_controller::UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId,
			void* /*pCookie*/)
	{
		XnUInt32 epochTime = 0;
		xnOSGetEpochTime(&epochTime);
		printf("%d Calibration started for user %d\n", epochTime, nId);
	}

	void nite_controller::UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId,
			XnCalibrationStatus eStatus, void* /*pCookie*/)
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
			if (eStatus == XN_CALIBRATION_STATUS_MANUAL_ABORT)
			{
				printf("Manual abort occured, stop attempting to calibrate!");
				return;
			}
			if (nite_controller::g_bNeedPose)
			{
				g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(xn_g_strPose, nId);
			}
			else
			{
				g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
			}
		}
	}

	bool nite_controller::file_exists(const char * file)
	{
//		XnBool exists;
//		xnOSDoesFileExist(file, &exists);
//		return exists;

		std::ifstream f(file);
		if (f.good())
		{
			f.close();
			return true;
		}
		else
		{
			f.close();
			return false;
		}
	}

	void nite_controller::check_rc(XnStatus nRetVal, const char * what)
	{
		if (nRetVal != XN_STATUS_OK)
		{
			printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));
			//return nRetVal;

			throw std::invalid_argument("failed - check_rc");
		}
	}

	std::vector<std::shared_ptr<mae::general_skeleton> > nite_controller::wait_for_update(unsigned int each_n_frames)
	{
		if (!initialized)
		{
			nite_controller::initialize();
		}

		XnUserID aUsers[max_users];
		XnUInt16 nUsers;

		std::vector<std::shared_ptr<mae::general_skeleton> > result;

		for (unsigned int i = 0; i < each_n_frames; i++)
		{
			g_Context.WaitOneUpdateAll(g_UserGenerator);
		}

		// print the torso information for the first user already tracking
		nUsers = max_users;
		g_UserGenerator.GetUsers(aUsers, nUsers);
		for (XnUInt16 i = 0; i < nUsers; i++)
		{
			//if user is not tracked continue with next one
			if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]) == FALSE)
			{
				continue;
			}

			//TODO use for testing
//			  XnSkeletonJointTransformation torsoJoint;
//            g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],XN_SKEL_TORSO,torsoJoint);
//                printf("user %d: head at (%6.2f,%6.2f,%6.2f)\n",aUsers[i],
//                                                                torsoJoint.position.position.X,
//                                                                torsoJoint.position.position.Y,
//                                                                torsoJoint.position.position.Z);

//mae : generate GeneralSkeleton from NiTE joint
			std::shared_ptr<mae::general_skeleton> skeleton = std::shared_ptr<mae::general_skeleton>(
					new mae::general_skeleton());

			//iterate through all known joints
			for (unsigned int j = 0; j < joint_ids.size() && j < joint_ids_mae.size(); j++)
			{
				//temp NiTE joint
				XnSkeletonJointTransformation xn_joint;
				g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i], joint_ids[j], xn_joint);

				//setup mae joint and set skeleton up
				std::shared_ptr<mae::general_joint> g_joint = std::shared_ptr<mae::general_joint>(
						new mae::general_joint(xn_joint.position.position.X, xn_joint.position.position.Y,
								xn_joint.position.position.Z));
				skeleton->set_joint((int) joint_ids_mae[j], g_joint);

			}

			result.push_back(skeleton);
		}

		return result;
	}

	void nite_controller::initialize()
	{
		if (!nite_controller::initialized)
		{

			//----------
			// mae : init
			//----------

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

			//----------
			//NiTE initialization stuff here
			//----------
			XnStatus nRetVal = XN_STATUS_OK;
			xn::EnumerationErrors errors;

			const char *fn = NULL;
			if (file_exists(SAMPLE_XML_PATH))
			{
				fn = SAMPLE_XML_PATH;
			}
			else if (file_exists(SAMPLE_XML_PATH_LOCAL))
			{
				fn = SAMPLE_XML_PATH_LOCAL;
			}
			else
			{
				printf("Could not find '%s' nor '%s'. Aborting.\n", SAMPLE_XML_PATH, SAMPLE_XML_PATH_LOCAL);
				throw std::invalid_argument("file not found.");
				//return XN_STATUS_ERROR;
			}
			printf("Reading config from: '%s'\n", fn);

			nRetVal = g_Context.InitFromXmlFile(fn, g_scriptNode, &errors);
			if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
			{
				XnChar strError[1024];
				errors.ToString(strError, 1024);
				printf("%s\n", strError);
				throw std::invalid_argument("no node present.");
				//return (nRetVal);
			}
			else if (nRetVal != XN_STATUS_OK)
			{
				printf("Open failed: %s\n", xnGetStatusString(nRetVal));
				throw std::invalid_argument("failed opening.");
				//return (nRetVal);
			}

			nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
			if (nRetVal != XN_STATUS_OK)
			{
				nRetVal = g_UserGenerator.Create(g_Context);
				nite_controller::check_rc(nRetVal, "Find user generator");
			}

			XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected;
			if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
			{
				printf("Supplied user generator doesn't support skeleton\n");
				//return 1;
				throw std::invalid_argument("user generator doesn't support skeleton");
			}
			nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
			nite_controller::check_rc(nRetVal, "Register to user callbacks");
			nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart,
					NULL, hCalibrationStart);
			nite_controller::check_rc(nRetVal, "Register to calibration start");
			nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(
					UserCalibration_CalibrationComplete,
					NULL, hCalibrationComplete);
			nite_controller::check_rc(nRetVal, "Register to calibration complete");

			if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
			{
				nite_controller::g_bNeedPose = TRUE;
				if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
				{
					printf("Pose required, but not supported\n");
					//return 1;
					throw std::invalid_argument("pose required but not supported");
				}
				nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseDetected(UserPose_PoseDetected, NULL,
						hPoseDetected);
				nite_controller::check_rc(nRetVal, "Register to Pose Detected");
				g_UserGenerator.GetSkeletonCap().GetCalibrationPose(xn_g_strPose);
			}

			g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

			nRetVal = g_Context.StartGeneratingAll();
			nite_controller::check_rc(nRetVal, "StartGenerating");

			printf("Starting to run\n");
			if (nite_controller::g_bNeedPose)
			{
				printf("Assume calibration pose\n");
			}

			nite_controller::initialized = true;
		}
	}

	void nite_controller::close()
	{
		if (initialized)
		{
			g_scriptNode.Release();
			g_UserGenerator.Release();
			g_Context.Release();
		}
	}

} // namespace lni
