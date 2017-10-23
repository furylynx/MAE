#include "fl_pose_detector.hpp"

namespace mae
{
	namespace fl
	{

		fl_pose_detector::fl_pose_detector(double hysteresis_val, bool debug)
		{
			if (debug)
			{
				std::cout << "creating pose detector." << std::endl;
			}

			debug_ = debug;
			hysteresis_val_ = hysteresis_val;

			fl_direction_map_ = std::make_shared<mae::fl::fl_direction_map>();
		}

		fl_pose_detector::~fl_pose_detector()
		{
		}

		void fl_pose_detector::set_hysteresis_val(double hysteresis_val)
		{
			hysteresis_val_ = hysteresis_val;
		}

		double fl_pose_detector::get_hysteresis_val() const
		{
			return hysteresis_val_;
		}

		std::shared_ptr<general_pose> fl_pose_detector::pose(double framerate, std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts, std::shared_ptr<general_pose> previous_pose)
		{
			if (debug_)
			{
				std::cout << "fl_pose_detector: detect pose" << std::endl;
			}

			return vector_pose(skeleton, body_parts, previous_pose);
		}

		std::shared_ptr<mae::general_pose> fl_pose_detector::vector_pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts, std::shared_ptr<general_pose> previous_pose)
		{
			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			//calculated distances for all bones
			for (unsigned int bone_index = 0; bone_index < body_parts.size(); bone_index++)
			{
				int bone_id = body_parts.at(bone_index).get_id();

				for (e_fl_direction dir : e_fl_direction_c::vec())
				{
					if (dir == e_fl_direction::INVALID_FL_DIRECTION)
					{
						continue;
					}

					if (dir == e_fl_direction::P_M)
					{
						if (body_parts.at(bone_index).has_middle_joint())
						{
							//calculate angle between two extremity bones
							//set value should is 180 degrees
							std::shared_ptr<mae::math::vec3d> v = skeleton->get_orig_skeleton()->get_joint(
											body_parts.at(bone_index).get_middle_joint())->vec()->subtract(skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_from())->vec());

							std::shared_ptr<mae::math::vec3d> w = skeleton->get_orig_skeleton()->get_joint(body_parts.at(bone_index).get_to())->vec()->subtract(skeleton->get_orig_skeleton()->get_joint(
									body_parts.at(bone_index).get_middle_joint())->vec());

							double angle = 180 - mae::math::math::calc_angle_half_deg(v, w);

							result->set_distance(bone_id, e_fl_direction_c::to_int(dir), angle);
						}
						else
						{
							//no joint bone therefore place middle does not exist for this body part
							//set distance to the maximum
							result->set_distance(bone_id, e_fl_direction_c::to_int(dir), 180);
						}
					}
					else
					{
						//set value for the direction
						std::shared_ptr<mae::math::vec3d> set_dir = fl_direction_map_->get_vec(dir);

						//real value for the direction
						std::shared_ptr<mae::math::vec3d> real_dir;
						if (skeleton->get_hierarchy()->at(body_parts.at(bone_index).get_to())->get_parent()->get_id()
								== body_parts.at(bone_index).get_from())
						{
							real_dir = skeleton->get_joint(body_parts.at(bone_index).get_to())->vec();
						}
						else
						{
							//get bone vector in {u,r,t}
							std::shared_ptr<mae::math::basis> torso_basis = skeleton->get_basis();

							real_dir =
									mae::math::math::project_to_basis(
											skeleton->get_orig_skeleton()->get_joint(body_parts.at(bone_index).get_to())->vec(),
											torso_basis,
											skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_from())->vec());
						}

						//angle between the vectors is the distance
						double angle = mae::math::math::calc_angle_half_deg(set_dir, real_dir);

						result->set_distance(bone_id, e_fl_direction_c::to_int(dir), angle);
					}
				}

				//determine the direction
				if (previous_pose != nullptr && hysteresis_val_ > PM_ACCEPT_DIST
						&& result->get_distance(bone_id, previous_pose->get_direction(bone_id)) >= 0
						&& result->get_distance(bone_id, previous_pose->get_direction(bone_id)) < hysteresis_val_
						&& result->get_distance(bone_id, e_fl_direction_c::to_int(e_fl_direction::P_M))
								> ((2 * PM_ACCEPT_DIST) - hysteresis_val_))
				{
					//std::cout << bone_id << " : dist to prev direction (" << previous_pose->get_direction(bone_id) << "): " << result->get_distance(bone_id, previous_pose->get_direction(bone_id)) << std::endl;

					//last value's distance is less than hysteresis threshold so keep direction
					//the PLACE_MID direction is still favoured if hysteresis value is reached
					result->set_direction(bone_id, previous_pose->get_direction(bone_id));
				}
				else
				{
					if (result->get_distance(bone_id, e_fl_direction_c::to_int(e_fl_direction::P_M)) < PM_ACCEPT_DIST)
					{
						//favor place mid since the distance is less than the defined PM_ACCEPT_DIST distance
						result->set_direction(bone_id, e_fl_direction_c::to_int(e_fl_direction::P_M));
					}
					else
					{
						//find minimum distance to set direction
						e_fl_direction min_dist_dir = e_fl_direction::INVALID_FL_DIRECTION;
						for (e_fl_direction dir : e_fl_direction_c::vec())
						{
							if (dir == e_fl_direction::INVALID_FL_DIRECTION)
							{
								continue;
							}

							if ((min_dist_dir == e_fl_direction::INVALID_FL_DIRECTION
									&& result->get_distance(bone_id, e_fl_direction_c::to_int(dir)) >= 0)
									|| (result->get_distance(bone_id, e_fl_direction_c::to_int(dir))
											< result->get_distance(bone_id, e_fl_direction_c::to_int(min_dist_dir))
											&& result->get_distance(bone_id, e_fl_direction_c::to_int(dir)) >= 0))
							{
								min_dist_dir = dir;
							}
						}
						result->set_direction(bone_id, e_fl_direction_c::to_int(min_dist_dir));
					}
				}

				//add rotation values to the pose
				result->set_rotation(bone_id, skeleton->get_joint(body_parts.at(bone_index).get_to())->get_rotation());

			}

			return result;
		}

		double fl_pose_detector::default_hysteresis_val()
		{
			return 25;
		}

		void fl_pose_detector::clear_buffer()
		{

		}

	} // namespace fl
} // namespace mae
