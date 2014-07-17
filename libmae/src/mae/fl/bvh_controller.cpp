/*
 * BVHController.cpp
 *
 *  Created on: 11.06.2014
 *      Author: keks
 */

#include "bvh_controller.hpp"

namespace mae
{
	namespace fl
	{

		bvh_controller::bvh_controller()
		{

		}

		bvh_controller::~bvh_controller()
		{
			// TODO Auto-generated destructor stub
		}

		std::string bvh_controller::bvh_str(std::vector<std::shared_ptr<general_skeleton> > data, double framerate)
		{
			if (data.size() == 0)
			{
				return "--no data present--";
			}

			std::stringstream sstr;

			//set fixed floating point representation
			sstr << std::fixed;

			//------------------------------
			//print header
			//------------------------------
			sstr << "HIERARCHY" << std::endl;

			//root element is torso
			if (!data.at(0)->get_hierarchy())
			{
				return "--no skeleton hierarchy present--";
			}

			std::vector<std::shared_ptr<hierarchy_element> > elements =
					data.at(0)->get_hierarchy()->get_element_sequence();

			if (elements.size() == 0)
			{
				return "--skeleton hierarchy has no elements--";
			}
			//escape name
			std::string root_name = mstr::replace(elements.at(0)->get_name(), "#", "#_");

			sstr << "ROOT " << root_name;

			//append sharp symbol to indicate that this is a torso joint
			if (elements.at(0)->is_torso_joint())
			{
				sstr << "#";
			}

			sstr << std::endl;
			sstr << "{" << std::endl;

			//offset of root element
			std::shared_ptr<general_joint> root_joint = data.at(0)->get_joint(elements.at(0)->get_id());
			sstr << "\t" << "OFFSET" << " " << std::setprecision(2) << root_joint->get_x();
			sstr << " " << std::setprecision(2) << root_joint->get_y();
			sstr << " " << std::setprecision(2) << root_joint->get_z() << std::endl;

			//channels for the root
			sstr << "\t" << "CHANNELS" << " " << 6;
			sstr << " " << "Xposition" << " " << "Yposition" << " " << "Zposition";
			sstr << " " << "Zrotation" << " " << "Xrotation" << " " << "Yrotation" << std::endl;

			//handle all other elements
			unsigned int indent_count = 1;
			for (unsigned int i = 1; i < elements.size(); i++)
			{
				if (elements.at(i)->get_parent()->get_id() == elements.at(i - 1)->get_id())
				{
					//simple successor
					indent_count++;
				}
				else
				{
					//end site before so brackets must get closed
					for (unsigned int j = 1; j <= i; j++)
					{
						//print closing brackets
						std::stringstream bstr;
						for (unsigned int k = 0; k < indent_count - 1; k++)
						{
							bstr << "\t";
						}
						bstr << "}" << std::endl;

						sstr << bstr.rdbuf();

						if (elements.at(i)->get_parent()->get_id() == elements.at(i - j)->get_parent()->get_id())
						{
							break;
						}

						indent_count--;
					}
				}

				std::stringstream isstr;
				for (unsigned int k = 0; k < indent_count - 1; k++)
				{
					isstr << "\t";
				}

				//check for end site
				if (elements.at(i)->is_parent())
				{
					//escape name
					std::string element_name = mstr::replace(elements.at(i)->get_name(), "#", "#_");

					sstr << isstr.str() << "JOINT" << " " << element_name;

					//append sharp symbol to indicate that this is a torso joint
					if (elements.at(i)->is_torso_joint())
					{
						sstr << "#";
					}
				}
				else
				{
					sstr << isstr.str() << "End Site";
				}

				sstr << std::endl;

				//bracket
				sstr << isstr.str() << "{" << std::endl;

				//increase indent
				isstr << "\t";

				//print offset
				std::shared_ptr<general_joint> current_joint = data.at(0)->get_joint(elements.at(i)->get_id());

				hierarchy_element* pparent = elements.at(i)->get_parent();
				while (pparent->is_dummy() && pparent->get_parent())
				{
					pparent = pparent->get_parent();
				}
				std::shared_ptr<general_joint> parent_joint = data.at(0)->get_joint(pparent->get_id());

				if (elements.at(i)->is_dummy())
				{
					sstr << isstr.str() << "OFFSET" << " " << std::setprecision(2) << 0.0;
					sstr << " " << std::setprecision(2) << 0.0;
					sstr << " " << std::setprecision(2) << 0.0 << std::endl;
				}
				else
				{
					sstr << isstr.str() << "OFFSET" << " " << std::setprecision(2);
					sstr << current_joint->get_x() - parent_joint->get_x();
					sstr << " " << std::setprecision(2);
					sstr << current_joint->get_y() - parent_joint->get_y();
					sstr << " " << std::setprecision(2);
					sstr << current_joint->get_z() - parent_joint->get_z();
					sstr << std::endl;
				}

				//print channels for the joint
				if (elements.at(i)->is_parent())
				{
					sstr << isstr.str() << "CHANNELS" << " " << 3 << " " << "Zrotation" << " ";
					sstr << "Xrotation" << " " << "Yrotation" << std::endl;
				}
			}
			std::cout << "closing brackets (end)" << std::endl;

			//closing brackets
			while (indent_count > 0)
			{
				std::stringstream isstr;
				for (unsigned int k = 0; k < indent_count - 1; k++)
				{
					isstr << "\t";
				}
				sstr << isstr.str() << "}" << std::endl;

				indent_count--;
			}

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
			sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2)
					<< 0.0 << " ";
			//torso rotation
			sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2)
					<< 0.0 << " ";

			for (unsigned int i = 1; i < elements.size(); i++)
			{
				if (elements.at(i)->get_parent()->get_children().size() <= 1)
				{
					//rotation for any other joint
					sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " "
							<< std::setprecision(2) << 0.0 << " ";
				}
			}

			sstr << std::endl;

			//------------------------------
			// 	> motion data for other frames
			//------------------------------
			std::cout << "print motion" << std::endl;
			for (unsigned int skel_id = 1; skel_id < data.size(); skel_id++)
			{
				//torso location
				std::shared_ptr<general_joint> next_root_joint = data.at(skel_id)->get_joint(elements.at(0)->get_id());
				sstr << std::setprecision(2) << next_root_joint->get_x() - root_joint->get_x() << " ";
				sstr << std::setprecision(2) << next_root_joint->get_y() - root_joint->get_y() << " ";
				sstr << std::setprecision(2) << next_root_joint->get_z() - root_joint->get_z() << " ";
				//torso hold unrotated state
				sstr << std::setprecision(2) << 0.0 << " " << std::setprecision(2) << 0.0 << " " << std::setprecision(2)
						<< 0.0 << " ";

				std::unordered_map<int, cv::Mat> rotations;
				rotations.insert(std::make_pair(elements.at(0)->get_id(), cv::Mat::eye(3, 3, CV_64F)));

				for (unsigned int i = 1; i < elements.size(); i++)
				{
					if (elements.at(i)->get_parent()->get_children().size() <= 1)
					{
						hierarchy_element* pparent = elements.at(i)->get_parent();
						while (pparent->is_dummy() && pparent->get_parent())
						{
							pparent = pparent->get_parent();
						}

						cv::Vec3d old_vec = math::jointToVec(data.at(0)->get_joint(elements.at(i)->get_id()))
								- math::jointToVec(data.at(0)->get_joint(pparent->get_id()));
						cv::Vec3d new_vec = math::jointToVec(data.at(skel_id)->get_joint(elements.at(i)->get_id()))
								- math::jointToVec(data.at(skel_id)->get_joint(pparent->get_id()));

						//rotate old vector according to previous rotations
						old_vec = math::matrix_mul(rotations.at(pparent->get_id()), old_vec);

						//rotation
						cv::Vec3d angles = math::rotation_angles_zxy(old_vec, new_vec);
						sstr << std::setprecision(2) << math::radToDeg(angles[0]) << " " << std::setprecision(2)
								<< math::radToDeg(angles[1]) << " " << std::setprecision(2) << math::radToDeg(angles[2])
								<< " ";

						//update rotation matrix
						rotations.insert(
								std::make_pair(elements.at(i)->get_id(),
										rotations.at(pparent->get_id())
												* math::matrix_rot_zxy(angles[0], angles[1], angles[2])));
					}
				}

				sstr << std::endl;
			}

			return sstr.str();
		}

		std::string bvh_controller::bvh_str(std::vector<std::shared_ptr<general_skeleton> > data)
		{
			return bvh_str(data, (double) 1 / 30);
		}

		std::string bvh_controller::bvh_str(std::shared_ptr<general_skeleton> data)
		{
			std::vector<std::shared_ptr<general_skeleton> > vec;
			vec.push_back(data);
			return bvh_str(vec);
		}

		void bvh_controller::print_bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename)
		{
			std::ofstream out_file(filename);
			out_file << bvh_str(data);
			out_file.close();
		}

		void bvh_controller::print_bvh_file(std::shared_ptr<general_skeleton> data, std::string filename)
		{
			std::vector<std::shared_ptr<general_skeleton> > result;
			result.push_back(data);
			return print_bvh_file(result, filename);
		}

		std::pair<std::vector<std::shared_ptr<general_skeleton> >, double> bvh_controller::read_bvh_str(std::string bvh_str,
				std::shared_ptr<bvh_spec> spec)
		{
			std::unordered_map<std::string, int> joint_str;
			std::unordered_map<std::string, bool> joint_torso;
			if (spec)
			{
				joint_str = spec->get_id_map();
				joint_torso = spec->get_torso_map();
			}

			//frame time
			double frame_time = 0.33333;

			std::string tmp = mstr::to_lower(bvh_str);

			//the resulting skeletons
			std::vector<std::shared_ptr<general_skeleton> > skeletons;

			//------------------------------
			// read offsets
			//------------------------------
			std::shared_ptr<general_skeleton> offset_skel = std::shared_ptr<general_skeleton>(new general_skeleton());

			std::vector<int> joint_sequence;

			std::unordered_map<int, std::vector<int> > joint_channel;
			int endeffector_count = 0;

			int element_count = 0;

			std::pair<std::string::size_type, std::string::size_type> pos_root = mstr::find_line(tmp, "root");
			std::string el_root = mstr::trim(std::string(bvh_str, pos_root.first + 4, pos_root.second));

			//get root element for hierarchy
			element_count++;
			std::shared_ptr<hierarchy_element> hy_root = generate_hierarchy_element(spec, element_count, el_root, false);

			//parse root offset
			offset_skel->set_joint(hy_root->get_id(),
					parse_offset(tmp, pos_root.first + pos_root.second,
							std::shared_ptr<general_joint>(new general_joint(0, 0, 0))));

			//parse root channels
			joint_channel.insert(
					std::make_pair(hy_root->get_id(), parse_channels(tmp, pos_root.first + pos_root.second)));

			//set sequence
			joint_sequence.push_back(hy_root->get_id());

			int read_depth = 1;
			std::string::size_type read_pos = pos_root.first + pos_root.second;
			int el_parent = hy_root->get_id();
			hierarchy_element* h_parent = hy_root.get();

			while (read_depth > 0)
			{
				std::pair<std::string::size_type, std::string::size_type> pos_joint = mstr::find_line(tmp,
						std::string("joint"), read_pos);
				std::string::size_type pos_bracket = tmp.find("}", read_pos);

				if (pos_bracket == std::string::npos)
				{
					std::cout << "pos_bracket == npos. el_parent: " << h_parent->get_name() << std::endl;
					//no bracket to follow, therefore syntax error
					return std::make_pair(skeletons, frame_time);
				}
				else if (pos_joint.first == std::string::npos)
				{
					//no joint to follow, therefore done with header
					read_depth = 0;
				}
				else if ((unsigned int) pos_bracket < (unsigned int) pos_joint.first)
				{
					//bracket comes next, decreasing depth
					read_depth--;

					//reset parent
					el_parent = h_parent->get_parent()->get_id();
					h_parent = h_parent->get_parent();

					//set read position
					read_pos = pos_bracket + 1;
				}
				else
				{
					std::string el_joint = mstr::trim(std::string(bvh_str, pos_joint.first + 5, pos_joint.second));

					element_count++;

					//update read pos
					read_pos = pos_joint.first + pos_joint.second;
					std::shared_ptr<general_joint> el_gj = parse_offset(tmp, (unsigned int) read_pos,
							offset_skel->get_joint(el_parent));

					bool el_dummy = false;
					if (el_gj->equals(offset_skel->get_joint(el_parent)))
					{
						el_dummy = true;
					}
					std::shared_ptr<hierarchy_element> hy_element = generate_hierarchy_element(spec, element_count, el_joint,
							el_dummy);
					h_parent->push_back(hy_element);

					//parse offset
					offset_skel->set_joint(hy_element->get_id(), el_gj);

					//parse channels
					joint_channel.insert(
							std::make_pair(hy_element->get_id(), parse_channels(tmp, (unsigned int) read_pos)));

					joint_sequence.push_back(hy_element->get_id());

					//set parent to current joint
					el_parent = hy_element->get_id();
					h_parent = hy_element.get();

					std::string::size_type pos_joint = tmp.find("joint", read_pos);
					std::string::size_type pos_end_site = tmp.find("end site", read_pos);

					if (pos_end_site < pos_joint)
					{
						endeffector_count++;

						std::stringstream endstr;
						endstr << "End Site#" << endeffector_count;

						read_pos = pos_end_site + 5;
						std::shared_ptr<general_joint> el_end_gj = parse_offset(tmp, (unsigned int) read_pos,
								offset_skel->get_joint(el_parent));

						bool el_end_dummy = false;
						if (el_end_gj->equals(offset_skel->get_joint(el_parent)))
						{
							el_end_dummy = true;
						}

						element_count++;
						std::shared_ptr<hierarchy_element> hy_end = generate_hierarchy_element(spec, element_count,
								endstr.str(), el_end_dummy);
						h_parent->push_back(hy_end);

						//parse offset
						offset_skel->set_joint(hy_end->get_id(), el_end_gj);

						//set sequence
						joint_sequence.push_back(hy_end->get_id());

						read_pos = tmp.find("}", read_pos);
						if (read_pos == std::string::npos)
						{
							std::cout << "no closing bracket found for end effector. el_joint: "
									<< hy_end->get_name() << std::endl;
							//no closing bracket found, therefore syntax error
							return std::make_pair(skeletons, frame_time);
						}
						read_pos++;
					}
					read_depth++;
				}

			}
			std::shared_ptr<hierarchy> hy = std::shared_ptr<hierarchy>(new hierarchy(hy_root));

			//offset skeleton is not stored. It's just for calculating the other ones
			//skeletons.push_back(offset_skel);

			//return std::make_pair(skeletons, frame_time);

			//------------------------------
			// read motion data
			//------------------------------
			std::string::size_type pos_motion = tmp.find("motion");
			if (pos_motion == std::string::npos)
			{
				return std::make_pair(skeletons, frame_time);
			}

			//frames count

			std::pair<std::string::size_type, std::string::size_type> pos_frames = mstr::find_line(tmp, "frames:",
					pos_motion);
			int frames = std::stoi(std::string(tmp, pos_frames.first + 7, pos_frames.second));

			std::string::size_type pos_motion_data = pos_frames.first + pos_frames.second + 1;

			//frame_time
			std::pair<std::string::size_type, std::string::size_type> pos_frame_time = mstr::find_line(tmp,
					"frame time:", pos_motion_data);

			//frames
			frame_time = std::stod(std::string(tmp, pos_frame_time.first + 12, pos_frame_time.second));
			pos_motion_data = pos_frame_time.first + pos_frame_time.second + 1;

			std::istringstream tmp_sstr(std::string(tmp, pos_motion_data));
			//parse motions
			for (int frame_count = 0; frame_count < frames; frame_count++)
			{
				std::string line;
				std::getline(tmp_sstr, line);

				std::shared_ptr<general_skeleton> next_skel = std::shared_ptr<general_skeleton>(new general_skeleton());

				std::vector<double> motion = mstr::double_list(line);

				//rotation matrices
				std::unordered_map<int, cv::Mat> joint_rot_mat;

				//set joints
				int m_read_offset = 0;

				for (unsigned int i = 0; i < joint_sequence.size(); i++)
				{
					if (i != 0 && !hy->at(joint_sequence.at(i))->is_parent())
					{
						//joint is end site therefore has no motion information

						//offset
						cv::Vec3d orig_offset = math::jointToVec(offset_skel->get_joint(joint_sequence.at(i)))
								- math::jointToVec(
										offset_skel->get_joint(hy->at(joint_sequence.at(i))->get_parent()->get_id()));

						cv::Vec3d new_offset = math::matrix_mul(
								joint_rot_mat.at(hy->at(joint_sequence.at(i))->get_parent()->get_id()), orig_offset);

						cv::Vec3d parent_pos = math::jointToVec(
								next_skel->get_joint(hy->at(joint_sequence.at(i))->get_parent()->get_id()));

						next_skel->set_joint(joint_sequence.at(i), math::vecToJoint(new_offset + parent_pos));

						joint_rot_mat.insert(
								std::make_pair(joint_sequence.at(i),
										joint_rot_mat.at(hy->at(joint_sequence.at(i))->get_parent()->get_id())));
					}
					else
					{
						int m_read_offset_tmp = 0;
						std::vector<int> channels = joint_channel.at(joint_sequence.at(i));

						//rotation
						cv::Mat motion_rot_mat = cv::Mat::eye(3, 3, CV_64F);

						double rot_zeta = 0;
						double rot_xi = 0;
						double rot_ypsilon = 0;

						std::list<cv::Mat> rot_mats_tmp_vec;

						if (channels.at(3) != -1)
						{
							rot_zeta = motion.at(m_read_offset + channels.at(3));
							m_read_offset_tmp++;

							rot_mats_tmp_vec.push_back(math::matrix_rot_z(math::degToRad(rot_zeta)));
						}

						if (channels.at(4) != -1)
						{
							rot_xi = motion.at(m_read_offset + channels.at(4));
							m_read_offset_tmp++;

							if (channels.at(4) < channels.at(3))
							{
								rot_mats_tmp_vec.push_front(math::matrix_rot_x(math::degToRad(rot_xi)));
							}
							else
							{
								rot_mats_tmp_vec.push_back(math::matrix_rot_x(math::degToRad(rot_xi)));
							}
						}

						if (channels.at(5) != -1)
						{
							rot_ypsilon = motion.at(m_read_offset + channels.at(5));
							m_read_offset_tmp++;

							if (channels.at(5) < channels.at(3) && channels.at(5) < channels.at(4))
							{
								rot_mats_tmp_vec.push_front(math::matrix_rot_y(math::degToRad(rot_ypsilon)));
							}
							else if (channels.at(5) > channels.at(3) && channels.at(5) > channels.at(4))
							{
								rot_mats_tmp_vec.push_back(math::matrix_rot_y(math::degToRad(rot_ypsilon)));
							}
							else
							{
								std::list<cv::Mat>::iterator it = rot_mats_tmp_vec.begin();
								it++;
								rot_mats_tmp_vec.insert(it, math::matrix_rot_y(math::degToRad(rot_ypsilon)));
							}
						}

						for (std::list<cv::Mat>::const_iterator iterator = rot_mats_tmp_vec.begin(), end =
								rot_mats_tmp_vec.end(); iterator != end; ++iterator)
						{
							motion_rot_mat *= *iterator;
						}

						if (i != 0)
						{
							motion_rot_mat *= joint_rot_mat.at(hy->at(joint_sequence.at(i))->get_parent()->get_id());
						}

						joint_rot_mat.insert(std::make_pair(joint_sequence.at(i), motion_rot_mat));

						//offset
						cv::Vec3d motion_offset;

						if (channels.at(0) != -1 || channels.at(1) != -1 || channels.at(2) != -1)
						{
							motion_offset[0] = 0;
							motion_offset[1] = 0;
							motion_offset[2] = 0;

							if (channels.at(0) != -1)
							{
								motion_offset[0] = motion.at(m_read_offset + channels.at(0));
								m_read_offset_tmp++;
							}

							if (channels.at(1) != -1)
							{
								motion_offset[1] = motion.at(m_read_offset + channels.at(1));
								m_read_offset_tmp++;
							}

							if (channels.at(2) != -1)
							{
								motion_offset[2] = motion.at(m_read_offset + channels.at(2));
								m_read_offset_tmp++;
							}
						}

						//apply rot_mat and offset to joints
						if (i == 0)
						{
							//handle root element
							cv::Vec3d orig_offset = math::jointToVec(offset_skel->get_joint(joint_sequence.at(i)));
							next_skel->set_joint(joint_sequence.at(i), math::vecToJoint(orig_offset + motion_offset));
						}
						else
						{
							//handle any other element
							cv::Vec3d orig_offset = math::jointToVec(offset_skel->get_joint(joint_sequence.at(i)))
									- math::jointToVec(
											offset_skel->get_joint(
													hy->at(joint_sequence.at(i))->get_parent()->get_id()));
							cv::Vec3d new_offset = orig_offset;
							if (i != 0)
							{
								new_offset = math::matrix_mul(
										joint_rot_mat.at(hy->at(joint_sequence.at(i))->get_parent()->get_id()),
										orig_offset);
							}

							cv::Vec3d parent_pos = math::jointToVec(
									next_skel->get_joint(hy->at(joint_sequence.at(i))->get_parent()->get_id()));

							next_skel->set_joint(joint_sequence.at(i),
									math::vecToJoint(new_offset + parent_pos + motion_offset));
						}

						m_read_offset += m_read_offset_tmp;
					}
				}

				skeletons.push_back(next_skel);
			}

			return std::make_pair(skeletons, frame_time);
		}

		std::pair<std::vector<std::shared_ptr<general_skeleton> >, double> bvh_controller::read_bvh_file(
				std::string filename, std::shared_ptr<bvh_spec> spec)
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
				return read_bvh_str(sstr.str(), spec);
			}
			else
			{
				return std::make_pair(std::vector<std::shared_ptr<general_skeleton> >(), 0.0);
			}
		}

		std::vector<int> bvh_controller::parse_channels(std::string& value, unsigned int pos)
		{
			std::pair<std::string::size_type, std::string::size_type> pos_channel = mstr::find_line(value, "channels",
					pos);
			std::vector<std::string> str_channels = mstr::split(value, pos_channel.first + 8, pos_channel.second);

			str_channels.erase(str_channels.begin());

			std::vector<int> el_channels;

			for (std::string::size_type i = 0; i < 6; i++)
			{
				el_channels.push_back(-1);
			}

			for (std::string::size_type i = 0; i < str_channels.size(); i++)
			{
				if (((std::string) str_channels[i]).compare(bvh_controller::Xpos) == 0)
				{
					el_channels.at(0) = i;
				}
				else if (str_channels.at(i).compare(bvh_controller::Ypos) == 0)
				{
					el_channels.at(1) = i;
				}
				else if (str_channels.at(i).compare(bvh_controller::Zpos) == 0)
				{
					el_channels.at(2) = i;
				}
				else if (str_channels.at(i).compare(bvh_controller::Zrot) == 0)
				{
					el_channels.at(3) = i;
				}
				else if (str_channels.at(i).compare(bvh_controller::Xrot) == 0)
				{
					el_channels.at(4) = i;
				}
				else if (str_channels.at(i).compare(bvh_controller::Yrot) == 0)
				{
					el_channels.at(5) = i;
				}
			}

			return el_channels;

		}

		std::shared_ptr<general_joint> bvh_controller::parse_offset(std::string& value, unsigned int pos,
				std::shared_ptr<general_joint> parent_joint)
		{
			std::pair<std::string::size_type, std::string::size_type> pos_offset = mstr::find_line(value, "offset",
					pos);

			std::vector<double> offset = mstr::double_list(value, pos_offset.first + 6, pos_offset.second);

			if (offset.size() != 3)
			{
				//syntax error
				return std::shared_ptr<general_joint>(new general_joint());
			}

			cv::Vec3d el_position = math::stdVecToVec3d(offset) + math::jointToVec(parent_joint);

			return math::vecToJoint(el_position);
		}

		std::shared_ptr<hierarchy_element> bvh_controller::generate_hierarchy_element(std::shared_ptr<bvh_spec> spec, int element_count,
				std::string element_name, bool is_dummy)
		{
			std::unordered_map<std::string, int> joint_str;
			std::unordered_map<std::string, bool> joint_torso;

			if (spec != nullptr)
			{
				joint_str = spec->get_id_map();
				joint_torso = spec->get_torso_map();
			}

			bool ending_sharp = false;

			if (element_name.at(element_name.size() - 1) == '#')
			{
				ending_sharp = true;
				element_name = std::string(element_name, 0, element_name.size() - 1);
			}

			std::string element_name_lower = mstr::to_lower(element_name);

			if (element_name_lower.find("end site#") != std::string::npos)
			{
				element_name = "End Site";
			}

			int element_id = element_count + joint_str.size();

			if (joint_str.find(element_name_lower) != joint_str.end())
			{
				element_id = joint_str.at(element_name_lower);
			}

			bool element_torso = false;
			if (joint_torso.size() > 0)
			{
				if (joint_torso.find(element_name_lower) != joint_torso.end())
				{
					element_torso = joint_torso.at(element_name_lower);
				}
				else
				{
					element_torso = false;
				}
			}
			else
			{
				element_torso = ending_sharp;
			}

			return std::shared_ptr<hierarchy_element>(
					new hierarchy_element(element_id, mstr::replace(element_name, "#_", "#"), element_torso, is_dummy));


		}

	} // namespace fl
} // namespace mae
