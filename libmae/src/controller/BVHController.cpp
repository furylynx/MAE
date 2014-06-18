/*
 * BVHController.cpp
 *
 *  Created on: 11.06.2014
 *      Author: keks
 */

#include "BVHController.hpp"

namespace mae
{

	BVHController::BVHController()
	{
		// fill ext vector
		std::vector<int> tmp;

		//left arm
		tmp.push_back(MAEJ_TORSO);
		tmp.push_back(MAEJ_LEFT_SHOULDER);
		tmp.push_back(MAEJ_LEFT_ELBOW);
		tmp.push_back(MAEJ_LEFT_HAND);

		ext.push_back(tmp);
		tmp.clear();

		//right arm
		tmp.push_back(MAEJ_TORSO);
		tmp.push_back(MAEJ_RIGHT_SHOULDER);
		tmp.push_back(MAEJ_RIGHT_ELBOW);
		tmp.push_back(MAEJ_RIGHT_HAND);

		ext.push_back(tmp);
		tmp.clear();

		//left leg
		tmp.push_back(MAEJ_TORSO);
		tmp.push_back(MAEJ_LEFT_HIP);
		tmp.push_back(MAEJ_LEFT_KNEE);
		tmp.push_back(MAEJ_LEFT_FOOT);

		ext.push_back(tmp);
		tmp.clear();

		//right leg
		tmp.push_back(MAEJ_TORSO);
		tmp.push_back(MAEJ_RIGHT_HIP);
		tmp.push_back(MAEJ_RIGHT_KNEE);
		tmp.push_back(MAEJ_RIGHT_FOOT);

		ext.push_back(tmp);
		tmp.clear();

		//head
		tmp.push_back(MAEJ_TORSO);
		tmp.push_back(MAEJ_NECK);
		tmp.push_back(MAEJ_HEAD);

		ext.push_back(tmp);
		tmp.clear();

		//fill joint_str map
		std::locale loc;
		for (int i = MAEJ_INVALID + 1; i < MAEJ_SIZE; i++)
		{
			std::string str(maej_str[i]);

			for (unsigned int k = 0; k < str.length(); k++)
			{
				str[k] = std::tolower((char) str[k], loc);
			}

			joint_str[str] = i;
		}

		//helpers needed although not used in skeleton
		joint_str["torso0"] = MAEJ_SIZE + 1;
		joint_str["torso1"] = MAEJ_SIZE + 2;
		joint_str["torso2"] = MAEJ_SIZE + 3;
		joint_str["torso3"] = MAEJ_SIZE + 4;
		joint_str["torso4"] = MAEJ_SIZE + 5;

		//set end effectors
		end_effectors.insert(std::make_pair(MAEJ_LEFT_ELBOW, MAEJ_LEFT_HAND));
		end_effectors.insert(std::make_pair(MAEJ_RIGHT_ELBOW, MAEJ_RIGHT_HAND));
		end_effectors.insert(std::make_pair(MAEJ_LEFT_KNEE, MAEJ_LEFT_FOOT));
		end_effectors.insert(std::make_pair(MAEJ_RIGHT_KNEE, MAEJ_RIGHT_FOOT));
		end_effectors.insert(std::make_pair(MAEJ_NECK, MAEJ_HEAD));
	}

	BVHController::~BVHController()
	{
		// TODO Auto-generated destructor stub
	}

	std::string BVHController::bvh_str(std::vector<std::shared_ptr<general_skeleton> > data,
			double framerate)
	{
		if (data.size() <= 0)
		{
			return "";
		}

		std::stringstream sstr;

		//set fixed floating point representation
		sstr << std::fixed;

		//------------------------------
		//print header
		//------------------------------
		sstr << "HIERARCHY" << std::endl;

		//root element is torso
		sstr << "ROOT " << maej_str[MAEJ_TORSO] << std::endl;
		sstr << "{" << std::endl;

		//offset of root element (torso)
		double torso_offset_x = ((std::shared_ptr<general_skeleton>) data[0])->get_joint(MAEJ_TORSO)->get_x();
		double torso_offset_y = ((std::shared_ptr<general_skeleton>) data[0])->get_joint(MAEJ_TORSO)->get_y();
		double torso_offset_z = ((std::shared_ptr<general_skeleton>) data[0])->get_joint(MAEJ_TORSO)->get_z();

		sstr << "\t" << "OFFSET" << " " << std::setprecision(2) << torso_offset_x << " " << std::setprecision(2)
				<< torso_offset_y << " " << std::setprecision(2) << torso_offset_z << std::endl;

		//channels for the root (torso)
		sstr << "\t" << "CHANNELS" << " " << 6 << " " << "Xposition" << " " << "Yposition" << " " << "Zposition" << " "
				<< "Zrotation" << " " << "Xrotation" << " " << "Yrotation" << std::endl;

		for (unsigned int i = 0; i < ext.size(); i++)
		{
			for (unsigned int j = 0; j < ((std::vector<int>) ext[i]).size(); j++)
			{
				//indicate new joint
				//tab space
				std::stringstream indent;
				for (unsigned int k = 0; k < j + 1; k++)
				{
					indent << "\t";
				}

				if (j != ((std::vector<int>) ext[i]).size() - 1)
				{
					if (j != 0)
					{
						sstr << indent.str() << "JOINT" << " " << maej_str[(int) ext[i][j]] << std::endl;
					}
					else
					{
						sstr << indent.str() << "JOINT" << " " << maej_str[(int) ext[i][j]] << i << std::endl;
					}
				}
				else
				{
					sstr << indent.str() << "End Site" << std::endl;
				}
				sstr << indent.str() << "{" << std::endl;

				//tab space
				indent << "\t";

				//offset for each joint
				double p_x = 0;
				double p_y = 0;
				double p_z = 0;

				if (j == 0)
				{
					//parent is torso
					p_x = data.at(0)->get_joint(MAEJ_TORSO)->get_x();
					p_y = data.at(0)->get_joint(MAEJ_TORSO)->get_y();
					p_z = data.at(0)->get_joint(MAEJ_TORSO)->get_z();
				}
				else
				{
					//parent is joint before
					p_x = data.at(0)->get_joint(ext.at(i).at(j - 1))->get_x();
					p_y = data.at(0)->get_joint(ext.at(i).at(j - 1))->get_y();
					p_z = data.at(0)->get_joint(ext.at(i).at(j - 1))->get_z();
				}

				sstr << indent.str() << "OFFSET" << " " << std::setprecision(2)
						<< ((std::shared_ptr<general_skeleton>) data[0])->get_joint((int) ext[i][j])->get_x()
								- p_x << " " << std::setprecision(2)
						<< ((std::shared_ptr<general_skeleton>) data[0])->get_joint((int) ext[i][j])->get_y()
								- p_y << " " << std::setprecision(2)
						<< ((std::shared_ptr<general_skeleton>) data[0])->get_joint((int) ext[i][j])->get_z()
								- p_z << std::endl;

				//channels for the joint (if not end site)
				if (j != ((std::vector<int>) ext[i]).size() - 1)
				{
					sstr << indent.str() << "CHANNELS" << " " << 3 << " " << "Zrotation" << " " << "Xrotation" << " "
							<< "Yrotation" << std::endl;
				}
			}

			//closing brackets
			for (int j = ((std::vector<int>) ext[i]).size() - 1; j >= 0; j--)
			{
				for (int k = 0; k < j + 1; k++)
				{
					sstr << "\t";
				}
				sstr << "}" << std::endl;
			}
		}

		//close root element (Hips)
		sstr << "}" << std::endl;

		//------------------------------
		// PRINT MOTION
		//------------------------------
		sstr << "MOTION" << std::endl;
		sstr << "Frames: " << (int) data.size() << std::endl;
		sstr << "Frame Time: " << std::setprecision(6) << framerate << std::endl;

		//------------------------------
		// 	> empty motion data for first frame
		//------------------------------

		//torso location
		sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0
				<< " ";
		//torso rotation
		sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0
				<< " ";

		for (unsigned int i = 0; i < ext.size(); i++)
		{
			for (unsigned int j = 1; j < ((std::vector<int>) ext[i]).size(); j++)
			{
				//rotation for any other joint
				sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2)
						<< 0.0 << " ";
			}
		}

		sstr << std::endl;

		//------------------------------
		// 	> motion data for other frames
		//------------------------------

		//TODO fill motion data for all other frames

		for (unsigned int skel_id = 1; skel_id < data.size(); skel_id++)
		{
			//torso location
			sstr << std::setprecision(2)
					<< ((std::shared_ptr<general_skeleton>) data[skel_id])->get_joint(MAEJ_TORSO)->get_x()
							- torso_offset_x << " " << std::setprecision(2)
					<< ((std::shared_ptr<general_skeleton>) data[skel_id])->get_joint(MAEJ_TORSO)->get_y()
							- torso_offset_y << " " << std::setprecision(2)
					<< ((std::shared_ptr<general_skeleton>) data[skel_id])->get_joint(MAEJ_TORSO)->get_z()
							- torso_offset_z << " ";
			//torso hold unrotated state
			sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2)
					<< 0.0 << " ";

			for (unsigned int i = 0; i < ext.size(); i++)
			{
				//offset for each joint
				cv::Vec3d p_vec = fl::FLMath::jointToVec(
						((std::shared_ptr<general_skeleton>) data[skel_id])->get_joint(MAEJ_TORSO));

				cv::Mat rot_mat = cv::Mat::eye(3, 3, CV_64F);

				for (unsigned int j = 1; j < ((std::vector<int>) ext[i]).size(); j++)
				{

					cv::Vec3d cur_vec = fl::FLMath::jointToVec(
							((std::shared_ptr<general_skeleton>) data[skel_id])->get_joint((int) ext[i][j]));

					int old_vec_ref = MAEJ_TORSO;
					if (j > 1)
					{
						old_vec_ref = (int) ext[i][j - 1];
					}
					cv::Vec3d old_vec = fl::FLMath::jointToVec(
							((std::shared_ptr<general_skeleton>) data[0])->get_joint((int) ext[i][j]))
							- fl::FLMath::jointToVec(
									((std::shared_ptr<general_skeleton>) data[0])->get_joint(old_vec_ref));
					cv::Vec3d new_vec = cur_vec - p_vec;

					//rotate old vector according to previous rotations
					old_vec = fl::FLMath::matrix_mul(rot_mat, old_vec);

					//rotation
					cv::Vec3d angles = fl::FLMath::rotation_angles_zxy(old_vec, new_vec);
					sstr << std::setprecision(2) << fl::FLMath::radToDeg(angles[0]) << " " << std::setprecision(2)
							<< fl::FLMath::radToDeg(angles[1]) << " " << std::setprecision(2)
							<< fl::FLMath::radToDeg(angles[2]) << " ";

					//update rotation matrix
					rot_mat *= fl::FLMath::matrix_rot_zxy(angles[0], angles[1], angles[2]);

					p_vec = cur_vec;
				}
			}

			sstr << std::endl;
		}

		return sstr.str();
	}

	std::string BVHController::bvh_str(std::vector<std::shared_ptr<general_skeleton> > data)
	{
		return bvh_str(data, (double) 1 / 30);
	}

	std::string BVHController::bvh_str(std::shared_ptr<general_skeleton> data)
	{
		std::vector<std::shared_ptr<general_skeleton> > vec;
		vec.push_back(data);
		return bvh_str(vec);
	}

	void BVHController::bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename)
	{
		std::ofstream out_file(filename);
		out_file << bvh_str(data);
		out_file.close();
	}

	void BVHController::bvh_file(std::shared_ptr<general_skeleton> data, std::string filename)
	{
		std::vector<std::shared_ptr<general_skeleton> > result;
		result.push_back(data);
		return bvh_file(result, filename);
	}

	std::vector<std::shared_ptr<general_skeleton> > BVHController::read_bvh(std::string bvh_str)
	{
		//frame time
		//TODO how to return this? via class var?
		double frame_time = 0.33333;

		std::string tmp = bvh_str;
		std::locale loc;

		for (unsigned int i = 0; i < bvh_str.length(); i++)
		{
			tmp[i] = std::tolower((char) bvh_str[i], loc);
		}

		//the resulting skeletons
		std::vector<std::shared_ptr<general_skeleton> > result;

		//------------------------------
		// read offsets
		//------------------------------
		std::shared_ptr<general_skeleton> offset_skel = std::shared_ptr<general_skeleton>(
				new general_skeleton());

		std::unordered_map<int, int> joint_parent;
		std::unordered_map<int, std::vector<int> > joint_channel;
		std::vector<int> joint_sequence;

		//joints that have more than one child
		std::vector<int> joint_end_effector;

		std::pair<int, int> pos_root = MStr::find_line(tmp, "root");

		std::string el_root(tmp, pos_root.first + 4, pos_root.second);

		//trim element
		el_root = MStr::trim(el_root);

		if (joint_str.find(el_root) == joint_str.end())
		{
			//element not found in spec
			return result;
		}
		int el_root_id = joint_str[el_root];

		//parse root offset
		offset_skel->set_joint(el_root_id,
				parse_offset(tmp, pos_root.first + pos_root.second,
						std::shared_ptr<general_joint>(new general_joint(0, 0, 0))));

		//parse root channels
		joint_channel.insert(std::make_pair(el_root_id, parse_channels(tmp, pos_root.first + pos_root.second)));

		//set sequence
		joint_sequence.push_back(el_root_id);

		int read_depth = 1;
		unsigned int read_pos = pos_root.first + pos_root.second;
		int el_parent = el_root_id;

		while (read_depth > 0)
		{
			std::pair<int, int> pos_joint = MStr::find_line(tmp, std::string("joint"), read_pos);
			unsigned int pos_bracket = tmp.find("}", read_pos);

			if (pos_bracket == std::string::npos)
			{
				std::cout << "pos_bracket == npos. el_parent: " << maej_str[el_parent] << std::endl;
				//no bracket to follow, therefore syntax error
				return result;
			}
			else if ((unsigned int) pos_joint.first == std::string::npos)
			{
				std::cout << "pos_joint == npos. el_parent: " << maej_str[el_parent] << std::endl;
				//no joint to follow, therefore done with header
				read_depth = 0;
			}
			else if ((unsigned int) pos_bracket < (unsigned int) pos_joint.first)
			{
				//bracket comes next, decreasing depth
				read_depth--;

				//reset parent
				el_parent = joint_parent[el_parent];

				//set read position
				read_pos = pos_bracket + 1;
			}
			else
			{
				std::string el_joint = MStr::trim(std::string(tmp, pos_joint.first + 5, pos_joint.second));

				if (joint_str.find(el_joint) == joint_str.end())
				{
					std::cout << "written joint is undefined in spec. el_joint: " << el_joint << std::endl;
					return result;
				}
				int el_joint_id = joint_str[el_joint];

				joint_parent.insert(std::make_pair(el_joint_id, el_parent));

				//update read pos
				read_pos = pos_joint.first + pos_joint.second;

				//parse offset
				offset_skel->set_joint(el_joint_id,
						parse_offset(tmp, (unsigned int) read_pos, offset_skel->get_joint(el_parent)));

				//parse channels
				joint_channel.insert(std::make_pair(el_joint_id, parse_channels(tmp, (unsigned int) read_pos)));

				//set sequence anyway; multi child joints will be filtered later
//				if (!curr_parent_split)
//				{
				joint_sequence.push_back(el_joint_id);
//				}

				//set parent to current joint
				el_parent = el_joint_id;

				unsigned int pos_joint = tmp.find("joint", read_pos);
				unsigned int pos_end_site = tmp.find("end site", read_pos);

				if (pos_end_site < pos_joint)
				{
					if (end_effectors.find(el_parent) == end_effectors.end())
					{
						std::cout << "spec lacks end effector. el_parent: " << maej_str[el_parent] << std::endl;
						//spec lacks end effector
						return result;
					}
					el_joint_id = end_effectors[el_parent];
					read_pos = pos_end_site + 5;

					joint_end_effector.push_back(el_joint_id);

					//set parent
					joint_parent.insert(std::make_pair(el_joint_id, el_parent));

					//parse offset
					offset_skel->set_joint(el_joint_id,
							parse_offset(tmp, (unsigned int) read_pos, offset_skel->get_joint(el_parent)));

					//set sequence
					joint_sequence.push_back(el_joint_id);

					read_pos = tmp.find("}", read_pos);
					if (read_pos == std::string::npos)
					{
						std::cout << "no closing bracket found for end effector. el_joint: " << maej_str[el_joint_id]
								<< std::endl;
						//no closing bracket found, therefore syntax error
						return result;
					}
					read_pos++;
				}
				read_depth++;
			}

		}

		//offset skeleton is not stored. It's just for calculating the other ones
		//result.push_back(offset_skel);

		//------------------------------
		// read motion data
		//------------------------------
		std::string::
		size_type pos_motion = tmp.find("motion");
		if (pos_motion == std::string::npos)
		{
			return result;
		}

		//frames count

		std::pair<int, int> pos_frames = MStr::find_line(tmp, "frames:", (unsigned int) pos_motion);
		int frames = std::stoi(std::string(tmp, pos_frames.first + 7, pos_frames.second));

		unsigned int pos_motion_data = pos_frames.first + pos_frames.second + 1;

		//frame_time
		std::pair<int, int> pos_frame_time = MStr::find_line(tmp, "frame time:", (unsigned int) pos_motion_data);

		//frames
		frame_time = std::stod(std::string(tmp, pos_frame_time.first + 12, pos_frame_time.second));
		pos_motion_data = pos_frame_time.first + pos_frame_time.second + 1;

		//rotation matrices
		std::unordered_map<int, cv::Mat> joint_rot_mat;

		std::istringstream tmp_sstr(std::string(tmp, pos_motion_data));
		//parse motions
		for (int i = 0; i < frames; i++)
		{
			std::string line;
			std::getline(tmp_sstr, line);

			std::shared_ptr<general_skeleton> next_skel = std::shared_ptr<general_skeleton>(
					new general_skeleton());

			std::vector<double> motion = MStr::double_list(line);

			//set joints
			int m_read_offset = 0;

			for (unsigned int j = 0; j < joint_sequence.size(); j++)
			{

				if (j != 0 && !joint_end_effector.empty()
						&& std::find(joint_end_effector.begin(), joint_end_effector.end(), joint_sequence[j])
								!= joint_end_effector.end())
				{
					//joint has no motion information

					//offset
					cv::Vec3d orig_offset = fl::FLMath::jointToVec(offset_skel->get_joint((int) joint_sequence[j]))
							- fl::FLMath::jointToVec(offset_skel->get_joint((int) joint_parent[joint_sequence[j]]));

					cv::Vec3d new_offset = fl::FLMath::matrix_mul(
							(cv::Mat) joint_rot_mat[joint_parent[joint_sequence[j]]], orig_offset);

					cv::Vec3d parent_pos = fl::FLMath::jointToVec(
							next_skel->get_joint((int) joint_parent[joint_sequence[j]]));

					next_skel->set_joint((int) joint_sequence[j], fl::FLMath::vecToJoint(new_offset + parent_pos));
				}
				else
				{

					int m_read_offset_tmp = 0;
					std::vector<int> channels = joint_channel[joint_sequence[j]];

					//rotation
					cv::Mat motion_rot_mat = cv::Mat::eye(3, 3, CV_64F);

					double rot_zeta = 0;
					double rot_xi = 0;
					double rot_ypsilon = 0;

					std::list<cv::Mat> rot_mats_tmp_vec;

					if (channels[3] != -1)
					{
						rot_zeta = motion[m_read_offset + channels[3]];
						m_read_offset_tmp++;

						rot_mats_tmp_vec.push_back(fl::FLMath::matrix_rot_z(fl::FLMath::degToRad(rot_zeta)));
					}

					if (channels[4] != -1)
					{
						rot_xi = motion[m_read_offset + channels[4]];
						m_read_offset_tmp++;

						if (channels[4] < channels[3])
						{
							rot_mats_tmp_vec.push_front(fl::FLMath::matrix_rot_x(fl::FLMath::degToRad(rot_xi)));
						}
						else
						{
							rot_mats_tmp_vec.push_back(fl::FLMath::matrix_rot_x(fl::FLMath::degToRad(rot_xi)));
						}
					}

					if (channels[5] != -1)
					{
						rot_ypsilon = motion[m_read_offset + channels[5]];
						m_read_offset_tmp++;

						if (channels[5] < channels[3] && channels[5] < channels[4])
						{
							rot_mats_tmp_vec.push_front(fl::FLMath::matrix_rot_y(fl::FLMath::degToRad(rot_ypsilon)));
						}
						else if (channels[5] > channels[3] && channels[5] > channels[4])
						{
							rot_mats_tmp_vec.push_back(fl::FLMath::matrix_rot_y(fl::FLMath::degToRad(rot_ypsilon)));
						}
						else
						{
							std::list<cv::Mat>::iterator iterator;
							iterator = rot_mats_tmp_vec.begin();
							iterator++;
							rot_mats_tmp_vec.insert(iterator,
									fl::FLMath::matrix_rot_y(fl::FLMath::degToRad(rot_ypsilon)));
						}
					}

					for (std::list<cv::Mat>::const_iterator iterator = rot_mats_tmp_vec.begin(), end =
							rot_mats_tmp_vec.end(); iterator != end; ++iterator)
					{
						motion_rot_mat *= *iterator;
					}

					if (j != 0)
					{
						motion_rot_mat *= joint_rot_mat[joint_parent[joint_sequence[j]]];
					}

					joint_rot_mat[joint_sequence[j]] = motion_rot_mat;

					//offset
					cv::Vec3d motion_offset;

					if (channels[0] != -1 || channels[1] != -1 || channels[2] != -1)
					{
						motion_offset[0] = 0;
						motion_offset[1] = 0;
						motion_offset[2] = 0;

						if (channels[0] != -1)
						{
							motion_offset[0] = motion[m_read_offset + channels[0]];
							m_read_offset_tmp++;
						}

						if (channels[1] != -1)
						{
							motion_offset[1] = motion[m_read_offset + channels[1]];
							m_read_offset_tmp++;
						}

						if (channels[2] != -1)
						{
							motion_offset[2] = motion[m_read_offset + channels[2]];
							m_read_offset_tmp++;
						}
					}

					//apply rot_mat and offset to joints
					if (j == 0)
					{
						//handle root element
						cv::Vec3d orig_offset = fl::FLMath::jointToVec(offset_skel->get_joint((int) joint_sequence[j]));
						next_skel->set_joint((int) joint_sequence[j],
								fl::FLMath::vecToJoint(orig_offset + motion_offset));
					}
					else
					{
						//handle any other element
						cv::Vec3d orig_offset = fl::FLMath::jointToVec(offset_skel->get_joint((int) joint_sequence[j]))
								- fl::FLMath::jointToVec(offset_skel->get_joint((int) joint_parent[joint_sequence[j]]));
						cv::Vec3d new_offset = orig_offset;
						if (j != 0)
						{
							new_offset = fl::FLMath::matrix_mul(
									(cv::Mat) joint_rot_mat[joint_parent[joint_sequence[j]]], orig_offset);
						}

						cv::Vec3d parent_pos = fl::FLMath::jointToVec(
								next_skel->get_joint((int) joint_parent[joint_sequence[j]]));

						next_skel->set_joint((int) joint_sequence[j],
								fl::FLMath::vecToJoint(new_offset + parent_pos + motion_offset));
					}

					m_read_offset += m_read_offset_tmp;
				}
			}

			result.push_back(next_skel);
		}

		return result;
	}

	std::vector<std::shared_ptr<general_skeleton> > BVHController::read_bvh_file(std::string filename)
	{
		std::ifstream in_file(filename);
		std::stringstream sstr;

		if (in_file.is_open())
		{
			std::string line;
			while (std::getline(in_file, line))
			{
				sstr << line << std::endl;
			}
			in_file.close();
			return read_bvh(sstr.str());
		}
		else
		{
			return std::vector<std::shared_ptr<general_skeleton> >();
		}
	}

	std::vector<int> BVHController::parse_channels(std::string& value, unsigned int pos)
	{
		std::pair<int, int> pos_channel = MStr::find_line(value, "channels", pos);
		std::vector<std::string> str_channels = MStr::split(value, pos_channel.first + 8, pos_channel.second);

		str_channels.erase(str_channels.begin());

		std::vector<int> el_channels;

		for (unsigned int i = 0; i < 6; i++)
		{
			el_channels.push_back(-1);
		}

		for (unsigned int i = 0; i < str_channels.size(); i++)
		{
			if (((std::string) str_channels[i]).compare(BVHController::Xpos) == 0)
			{
				el_channels[0] = i;
			}
			else if (((std::string) str_channels[i]).compare(BVHController::Ypos) == 0)
			{
				el_channels[1] = i;
			}
			else if (((std::string) str_channels[i]).compare(BVHController::Zpos) == 0)
			{
				el_channels[2] = i;
			}
			else if (((std::string) str_channels[i]).compare(BVHController::Zrot) == 0)
			{
				el_channels[3] = i;
			}
			else if (((std::string) str_channels[i]).compare(BVHController::Xrot) == 0)
			{
				el_channels[4] = i;
			}
			else if (((std::string) str_channels[i]).compare(BVHController::Yrot) == 0)
			{
				el_channels[5] = i;
			}
		}

		return el_channels;

	}

	std::shared_ptr<general_joint> BVHController::parse_offset(std::string& value, unsigned int pos,
			std::shared_ptr<general_joint> parent_joint)
	{
		std::pair<int, int> pos_offset = MStr::find_line(value, "offset", pos);

		std::vector<double> offset = MStr::double_list(value, pos_offset.first + 6, pos_offset.second);

		if (offset.size() != 3)
		{
			//syntax error
			return std::shared_ptr<general_joint>(new general_joint());
		}

		cv::Vec3d el_position = fl::FLMath::stdVecToVec3d(offset) + fl::FLMath::jointToVec(parent_joint);

		return fl::FLMath::vecToJoint(el_position);
	}

} // namespace mae
