/*
 * nite_controller.cpp
 *
 *  Created on: 15.09.2014
 *      Author: keks
 */

#include "nite_controller.hpp"

namespace mae
{
	namespace nite
	{
		bool nite_controller::initialized_ = false;
		std::vector<XnSkeletonJoint> nite_controller::joint_ids_;
		std::vector<int> nite_controller::joint_ids_mae_;

		nite_controller::nite_controller(std::string config_path, unsigned int  max_users, bool debug)
		{
			config_path_ = config_path;
			max_users_ = max_users;
			debug_ = debug;

			b_needpose_ = FALSE;

			initialize();
		}

		nite_controller::~nite_controller()
		{
		}

		void nite_controller::initialize()
		{
			if (!nite_controller::initialized_)
			{
				//----------
				// mae : init
				//----------

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_HIP);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_HIP));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_HIP);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_HIP));

				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TORSO));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_SHOULDER);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_SHOULDER));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_SHOULDER);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_SHOULDER));

				nite_controller::joint_ids_.push_back(XN_SKEL_NECK);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::NECK));

				nite_controller::joint_ids_.push_back(XN_SKEL_HEAD);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::HEAD));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_ELBOW);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_ELBOW));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_HAND);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_HAND));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_ELBOW);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_ELBOW));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_HAND);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_HAND));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_KNEE);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_KNEE));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_FOOT);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::LEFT_FOOT));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_KNEE);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_KNEE));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_FOOT);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::RIGHT_FOOT));

				nite_controller:://dummy joints
				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TLS));

				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TRS));

				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TLH));

				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TRH));

				nite_controller::joint_ids_.push_back(XN_SKEL_TORSO);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::TN));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_HAND);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::END_LH));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_HAND);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::END_RH));

				nite_controller::joint_ids_.push_back(XN_SKEL_LEFT_FOOT);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::END_LF));

				nite_controller::joint_ids_.push_back(XN_SKEL_RIGHT_FOOT);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::END_RF));

				nite_controller::joint_ids_.push_back(XN_SKEL_HEAD);
				nite_controller::joint_ids_mae_.push_back(mae::e_joint_c::to_int(mae::e_joint::END_H));

				nite_controller::initialized_ = true;
			}

			//----------
			//NiTE initialization stuff here
			//----------
			XnStatus nretval = XN_STATUS_OK;
			xn::EnumerationErrors errors;

			//check whether the config exists
			const char *fn = NULL;
			if (file_exists (config_path_.c_str()))
			{
				fn = config_path_.c_str();
			}
			else
			{
				std::stringstream sstr;
				sstr << "Could not find '" << config_path_ << "'. Aborting." << std::endl;

				throw std::invalid_argument(sstr.str());
			}

			if (debug_)
			{
				std::cout << "Reading config from '" << fn << "'." << std::endl;
			}

			//initialize the module using the xml file
			nretval = context_.InitFromXmlFile(fn, script_node_, &errors);

			//check whether the initialization was successful
			if (nretval == XN_STATUS_NO_NODE_PRESENT)
			{
				XnChar str_error[1024];
				errors.ToString(str_error, 1024);

				std::stringstream sstr;
				sstr << str_error << std::endl;

				throw std::invalid_argument(sstr.str());
			}
			else if (nretval != XN_STATUS_OK)
			{
				std::stringstream sstr;
				sstr << "Open failed: " << xnGetStatusString(nretval) << std::endl;

				throw std::invalid_argument(sstr.str());
			}

			nretval = context_.FindExistingNode(XN_NODE_TYPE_USER, user_generator_);
			if (nretval != XN_STATUS_OK)
			{
				nretval = user_generator_.Create(context_);
				check_rc(nretval, "Find user generator");
			}

			XnCallbackHandle husercallbacks, hcalibrationstart, hcalibrationcomplete, hposedetected;
			if (!user_generator_.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
			{
				std::stringstream sstr;
				sstr << "Supplied user generator doesn't support skeleton" << std::endl;

				throw std::invalid_argument(sstr.str());
			}

			//register the callback methods, pass this pointer in order to be able to invoke class methods later
			nretval = user_generator_.RegisterUserCallbacks(scb_user_newuser, scb_user_lostuser, this, husercallbacks);
			nite_controller::check_rc(nretval, "Register to user callbacks");

			nretval = user_generator_.GetSkeletonCap().RegisterToCalibrationStart(scb_usercalibration_calibrationstart, this, hcalibrationstart);
			nite_controller::check_rc(nretval, "Register to calibration start");

			nretval = user_generator_.GetSkeletonCap().RegisterToCalibrationComplete(
					scb_usercalibration_calibrationcomplete,
					this, hcalibrationcomplete);
			nite_controller::check_rc(nretval, "Register to calibration complete");

			if (user_generator_.GetSkeletonCap().NeedPoseForCalibration())
			{
				b_needpose_ = TRUE;
				if (!user_generator_.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
				{
					throw std::invalid_argument("Pose required, but not supported");
				}

				nretval = user_generator_.GetPoseDetectionCap().RegisterToPoseDetected(scb_userpose_posedetected, this,
						hposedetected);
				check_rc(nretval, "Register to Pose Detected");

				user_generator_.GetSkeletonCap().GetCalibrationPose(str_pose_);
			}

			user_generator_.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

			nretval = context_.StartGeneratingAll();
			check_rc(nretval, "StartGenerating");

			//print information
			if (debug_)
			{
				std::cout << "Starting to run" << std::endl;

				if (b_needpose_ && debug_)
				{
					std::cout << "Assume calibration pose" << std::endl;
				}
			}
		}

		bool nite_controller::file_exists(const char * file) const
		{
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

		void nite_controller::check_rc(XnStatus nRetVal, std::string what) const
		{
			if (nRetVal != XN_STATUS_OK)
			{
				std::stringstream sstr;
				sstr << what << " failed: " << xnGetStatusString(nRetVal) << std::endl;

				if (debug_)
				{
					std::cerr << sstr.str() << std::endl;
				}

				throw std::invalid_argument(sstr.str());
			}
		}

		bool nite_controller::was_keyboard_hit()
		{
			return nite_controller::xn_was_keyboard_hit();
		}

		bool nite_controller::xn_was_keyboard_hit()
		{
			return xnOSWasKeyboardHit();
		}

		std::vector<std::shared_ptr<mae::general_skeleton> > nite_controller::wait_for_update(unsigned int each_n_frames)
		{
			if (each_n_frames == 0)
			{
				each_n_frames = 1;
			}

			std::vector<std::shared_ptr<mae::general_skeleton> > result;

			//skip frames if each_n_frames is grater than 1
			for (unsigned int i = 0; i < each_n_frames; i++)
			{
				//wait for next frame
				context_.WaitOneUpdateAll(user_generator_);
			}

			// print the torso information for the first user already tracking
			XnUserID a_users[max_users_];
			XnUInt16 n_users = max_users_;

			user_generator_.GetUsers(a_users, n_users);
			for (XnUInt16 i = 0; i < n_users; i++)
			{
				//provide only data for the user being tracked
				if (user_generator_.GetSkeletonCap().IsTracking(a_users[i]) != FALSE)
				{
					//generate general_skeleton from NiTE joints
					std::shared_ptr<mae::general_skeleton> mae_skeleton = std::shared_ptr<mae::general_skeleton>(new mae::general_skeleton());

					//iterate through all known joints
					for (unsigned int j = 0; j < joint_ids_.size() && j < joint_ids_mae_.size(); j++)
					{
						//temp NiTE joint
						XnSkeletonJointTransformation xn_joint;
						user_generator_.GetSkeletonCap().GetSkeletonJoint(a_users[i], joint_ids_.at(j), xn_joint);

						double confidence = xn_joint.position.fConfidence;
						double rotation = 0;//TODO get rotation

						//create general joint from the NiTE joint
						std::shared_ptr<mae::general_joint> mae_joint = std::shared_ptr<mae::general_joint>(
								new mae::general_joint(xn_joint.position.position.X, xn_joint.position.position.Y,
										xn_joint.position.position.Z, rotation, confidence));

						//add general_joint to the skeleton
						mae_skeleton->set_joint(joint_ids_mae_.at(j), mae_joint);
					}

					//add skeleton to result
					result.push_back(mae_skeleton);
				}
				else
				{
					//user is not tracked therefore fill nullptr to the vector
					result.push_back(nullptr);
				}
			}

			return result;
		}

		//***************
		//NITE Callbacks
		//***************

		void nite_controller::cb_user_newuser(xn::UserGenerator& generator, XnUserID new_id)
		{
			XnUInt32 epoch_time = 0;
			xnOSGetEpochTime(&epoch_time);
			printf("%d New User %d\n", epoch_time, new_id);
			// New user found
			if (b_needpose_)
			{
				user_generator_.GetPoseDetectionCap().StartPoseDetection(str_pose_, new_id);
			}
			else
			{
				user_generator_.GetSkeletonCap().RequestCalibration(new_id, TRUE);
			}
		}

		void nite_controller::cb_user_lostuser(xn::UserGenerator& generator, XnUserID new_id)
		{
			if (debug_)
			{
				XnUInt32 epoch_time = 0;
				xnOSGetEpochTime(&epoch_time);

				std::cout << epoch_time << " Lost user " << new_id << std::endl;
			}
		}

		void nite_controller::cb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* str_pose,
				XnUserID new_id)
		{
			if (debug_)
			{
				XnUInt32 epoch_time = 0;
				xnOSGetEpochTime(&epoch_time);

				std::cout << epoch_time << "  Pose  " << str_pose << " detected for user " << new_id << std::endl;
			}

			user_generator_.GetPoseDetectionCap().StopPoseDetection(new_id);
			user_generator_.GetSkeletonCap().RequestCalibration(new_id, TRUE);
		}

		void nite_controller::cb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID new_id)
		{
			if (debug_)
			{
				XnUInt32 epoch_time = 0;
				xnOSGetEpochTime(&epoch_time);

				std::cout << epoch_time << " Calibration started for user " << new_id << std::endl;
			}
		}

		void nite_controller::cb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability,
				XnUserID new_id, XnCalibrationStatus e_status)
		{
			XnUInt32 epoch_time = 0;
			xnOSGetEpochTime(&epoch_time);
			if (e_status == XN_CALIBRATION_STATUS_OK)
			{
				// Calibration succeeded
				if (debug_)
				{
					std::cout << epoch_time << " Calibration complete, start tracking user " << new_id << std::endl;
				}

				user_generator_.GetSkeletonCap().StartTracking(new_id);
			}
			else
			{
				// Calibration failed
				if (debug_)
				{
					std::cout << epoch_time << " Calibration failed for user " << new_id << std::endl;
				}

				if (e_status == XN_CALIBRATION_STATUS_MANUAL_ABORT)
				{
					if (debug_)
					{
						std::cout << "Manual abort occured, stop attempting to calibrate! " << std::endl;
					}

					return;
				}

				if (b_needpose_)
				{
					user_generator_.GetPoseDetectionCap().StartPoseDetection(str_pose_, new_id);
				}
				else
				{
					user_generator_.GetSkeletonCap().RequestCalibration(new_id, TRUE);
				}
			}
		}

		// Callback: New user was detected
		void nite_controller::scb_user_newuser(xn::UserGenerator& generator, XnUserID new_id, void* p_cookie)
		{
			if (nite_controller* nc = reinterpret_cast<nite_controller*>(p_cookie))
			{
				nc->cb_user_newuser(generator, new_id);
			}
		}

		// Callback: An existing user was lost
		void nite_controller::scb_user_lostuser(xn::UserGenerator& generator, XnUserID new_id, void* p_cookie)
		{
			if (nite_controller* nc = reinterpret_cast<nite_controller*>(p_cookie))
			{
				nc->cb_user_lostuser(generator, new_id);
			}
		}

		// Callback: Detected a pose
		void nite_controller::scb_userpose_posedetected(xn::PoseDetectionCapability& capability, const XnChar* str_pose,
				XnUserID new_id, void* p_cookie)
		{
			if (nite_controller* nc = reinterpret_cast<nite_controller*>(p_cookie))
			{
				nc->cb_userpose_posedetected(capability, str_pose, new_id);
			}
		}

		// Callback: Started calibration
		void nite_controller::scb_usercalibration_calibrationstart(xn::SkeletonCapability& capability, XnUserID new_id,
				void* p_cookie)
		{
			if (nite_controller* nc = reinterpret_cast<nite_controller*>(p_cookie))
			{
				nc->cb_usercalibration_calibrationstart(capability, new_id);
			}
		}

		// Callback: Calibration complete
		void nite_controller::scb_usercalibration_calibrationcomplete(xn::SkeletonCapability& capability,
				XnUserID new_id, XnCalibrationStatus e_status, void* p_cookie)
		{
			if (nite_controller* nc = reinterpret_cast<nite_controller*>(p_cookie))
			{
				nc->cb_usercalibration_calibrationcomplete(capability, new_id, e_status);
			}
		}

	} // namespace eventing
} // namespace mae
