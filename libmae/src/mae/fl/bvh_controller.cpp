#include "bvh_controller.hpp"

//internal includes
#include "../math/internal_math.hh"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

namespace mae
{
	namespace fl
	{

		bvh_controller::bvh_controller()
		{
            precision_ = 2;
		}
		
        bvh_controller::bvh_controller(std::size_t precision)
        {
            precision_ = precision;
        }

		bvh_controller::~bvh_controller()
		{
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
			if (elements.at(0)->is_base_joint())
			{
				sstr << "#";
			}

			sstr << std::endl;
			sstr << "{" << std::endl;

			//offset of root element
			std::shared_ptr<general_joint> root_joint = data.at(0)->get_joint(elements.at(0)->get_id());
			sstr << "\t" << "OFFSET" << " " << std::setprecision(precision_) << root_joint->get_x();
			sstr << " " << std::setprecision(precision_) << root_joint->get_y();
			sstr << " " << std::setprecision(precision_) << root_joint->get_z() << std::endl;

			//channels for the root
			sstr << "\t" << "CHANNELS" << " " << 6;
			sstr << " " << "Xposition" << " " << "Yposition" << " " << "Zposition";
			sstr << " " << "Zrotation" << " " << "Xrotation" << " " << "Yrotation" << std::endl;
//            sstr << " " << "Yrotation" << " " << "Zrotation" << " " << "Xrotation" << std::endl;
            
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
					int prev_parent_id = elements.at(i-1)->get_parent()->get_id();
					for (unsigned int j = 1; j <= i; j++)
					{
					    if (1 == j || elements.at(i - j)->get_id() == prev_parent_id) {
                            
                            //print closing brackets
                            std::stringstream bstr;
                            for (unsigned int k = 0; indent_count > 0 && k < indent_count - 1; k++)
                            {
                                bstr << "\t";
                            }
                            bstr << "}" << std::endl;
                        
                            sstr << bstr.rdbuf();
                        
                            if (elements.at(i)->get_parent()->get_id() == elements.at(i - j)->get_parent()->get_id())
                            {
                                break;
                            }
                        
                            prev_parent_id = elements.at(i - j)->get_parent()->get_id();
                            indent_count--;
					    }
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
					if (elements.at(i)->is_base_joint())
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
					sstr << isstr.str() << "OFFSET" << " " << std::setprecision(precision_) << 0.0;
					sstr << " " << std::setprecision(precision_) << 0.0;
					sstr << " " << std::setprecision(precision_) << 0.0 << std::endl;
				}
				else
				{
					sstr << isstr.str() << "OFFSET" << " " << std::setprecision(precision_);
					sstr << current_joint->get_x() - parent_joint->get_x();
					sstr << " " << std::setprecision(precision_);
					sstr << current_joint->get_y() - parent_joint->get_y();
					sstr << " " << std::setprecision(precision_);
					sstr << current_joint->get_z() - parent_joint->get_z();
					sstr << std::endl;
				}

				//print channels for the joint
				if (elements.at(i)->is_parent())
				{
					sstr << isstr.str() << "CHANNELS" << " " << 3 << " " << "Zrotation" << " ";
					sstr << "Xrotation" << " " << "Yrotation" << std::endl;
//                    sstr << isstr.str() << "CHANNELS" << " " << 3 << " " << "Yrotation" << " ";
//                    sstr << "Zrotation" << " " << "Xrotation" << std::endl;
				}
			}

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
            sstr << std::setprecision(precision_) << root_joint->get_x() << " ";
            sstr << std::setprecision(precision_) << root_joint->get_y() << " ";
            sstr << std::setprecision(precision_) << root_joint->get_z() << " ";

			for (unsigned int i = 0; i < elements.size(); i++)
			{
				if (elements.at(i)->is_parent())
				{
					//rotation for any other joint
					sstr << std::setprecision(precision_) << 0.0 << " " << std::setprecision(precision_) << 0.0 << " "
							<< std::setprecision(precision_) << 0.0 << " ";
				}
			}

			sstr << std::endl;

			//------------------------------
			// 	> motion data for other frames
			//------------------------------
			for (unsigned int skel_id = 1; skel_id < data.size(); skel_id++)
			{
				//torso location
				std::shared_ptr<general_joint> next_root_joint = data.at(skel_id)->get_joint(elements.at(0)->get_id());
				sstr << std::setprecision(precision_) << next_root_joint->get_x() << " ";
				sstr << std::setprecision(precision_) << next_root_joint->get_y() << " ";
				sstr << std::setprecision(precision_) << next_root_joint->get_z() << " ";

				std::unordered_map<int, cv::Mat> rotations;

				for (unsigned int i = 0; i < elements.size(); i++)
				{
                    if (elements.at(i)->is_parent())
                    {
                        std::size_t el_id = elements.at(i)->get_id();
                        cv::Mat parent_rot = ( 0 == i ? cv::Mat::eye(3, 3, CV_64F) : rotations.at(elements.at(i)->get_parent()->get_id()) );
     
                        std::shared_ptr<hierarchy_element> fchild = elements.at(i)->get_children().at(0);
    
                        // bone as defined in the offset skeleton (first skeleton in sequence)
                        cv::Vec3d old_vec = mae::math::internal_math::joint_to_vec(data.at(0)->get_joint(fchild->get_id()))
                                            - mae::math::internal_math::joint_to_vec(data.at(0)->get_joint(el_id));
    
                        // current orientation of the same bone
                        cv::Vec3d new_vec = mae::math::internal_math::joint_to_vec(data.at(skel_id)->get_joint(fchild->get_id()))
                                            - mae::math::internal_math::joint_to_vec(data.at(skel_id)->get_joint(el_id));
    
                        //rotate old vector according to previous rotations
                        cv::Vec3d old_vec_rot = mae::math::internal_math::matrix_mul(parent_rot, old_vec);
    
                        //rotation
                        cv::Vec3d angles = mae::math::internal_math::rotation_angles_zxy(old_vec_rot, new_vec);
//                        cv::Vec3d angles = mae::math::internal_math::rotation_angles_yzx(old_vec_rot, new_vec);
                        sstr << std::setprecision(precision_) << mae::math::internal_math::rad_to_deg(angles[0]) << " " << std::setprecision(precision_)
                             << mae::math::internal_math::rad_to_deg(angles[1]) << " " << std::setprecision(precision_)
                             << mae::math::internal_math::rad_to_deg(angles[2]) << " ";
    
                        //update rotation matrix
                        rotations.insert(
                                std::make_pair(elements.at(i)->get_id(),
                                               parent_rot * mae::math::internal_math::matrix_rot_zxy(angles[0], angles[1], angles[2])));
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
		
		void bvh_controller::print_bvh_file(std::shared_ptr<bvh_data> data, std::string filename)
		{
			print_bvh_file(data->get_skeleton_data(), filename, data->get_framerate());
		}
		
		void bvh_controller::print_bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename, double framerate)
		{
			std::ofstream out_file(filename);
			out_file << bvh_str(data, framerate);
			out_file.close();
		}

		void bvh_controller::print_bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename)
		{
			print_bvh_file(data, filename, (double) 1 / 30);
		}

		void bvh_controller::print_bvh_file(std::shared_ptr<general_skeleton> data, std::string filename)
		{
			std::vector<std::shared_ptr<general_skeleton> > result;
			result.push_back(data);
			return print_bvh_file(result, filename);
		}

		std::shared_ptr<bvh_data> bvh_controller::read_bvh_str(
				std::string bvh_str, std::shared_ptr<bvh_spec> spec)
		{
		    //prepare string
		    bvh_str = mstr::replace(mstr::replace(mstr::replace(bvh_str, "\t", "   "), "\r\n", "\n"), "\r", "\n");
		    
			std::map<std::string, int> joint_str;
			std::map<std::string, bool> joint_torso;

			joint_str = spec->get_id_map();
			joint_torso = spec->get_basis_map();

			//frame time
			double frame_time = 0.33333;

			std::string tmp = mstr::to_lower(bvh_str);

			//the resulting skeletons
			std::vector<std::shared_ptr<general_skeleton> > skeletons;

			//------------------------------
			// read offsets
			//------------------------------
            std::vector<int> joint_sequence;
            std::unordered_map<int, std::vector<int> > joint_channel;
			std::shared_ptr<general_skeleton> offset_skel = read_offset_skeleton(bvh_str, spec, joint_sequence, joint_channel);

			//offset skeleton is not stored. It's just for calculating the other ones

			//------------------------------
			// read motion data
			//------------------------------
			std::string::size_type pos_motion = tmp.find("motion");
			if (pos_motion == std::string::npos)
			{
//				return std::shared_ptr<bvh_data>(new bvh_data(skeletons, frame_time));
                throw std::invalid_argument("Syntax error in BVH file. Cannot parse motion data.");
			}

			//frames count

			std::pair<std::string::size_type, std::string::size_type> pos_frames = mstr::find_line(tmp, "frames:",
					pos_motion);

			std::string frames_string = std::string(tmp, pos_frames.first + 7, pos_frames.second - 7);
			int frames = std::stoi(frames_string);

			std::string::size_type pos_motion_data = pos_frames.first + pos_frames.second + 1;

			//frame_time
			std::pair<std::string::size_type, std::string::size_type> pos_frame_time = mstr::find_line(tmp,
					"frame time:", pos_motion_data);

			//frames
			std::string frame_time_string = std::string(tmp, pos_frame_time.first + 12, pos_frame_time.second - 12);
			frame_time = std::stod(frame_time_string);
			pos_motion_data = pos_frame_time.first + pos_frame_time.second + 1;

			std::istringstream tmp_sstr(std::string(tmp, pos_motion_data));
			//parse motions
			for (int frame_count = 0; frame_count < frames; frame_count++)
			{
				std::string line;
				std::getline(tmp_sstr, line);

				std::shared_ptr<general_skeleton> next_skel = std::make_shared<general_skeleton>(offset_skel->get_hierarchy());
				next_skel->set_right_left(offset_skel->get_right_left());
				next_skel->set_top_down(offset_skel->get_top_down());

				//set origin joint for it is used as a reference
				//next_skel->set_joint(hy_root->get_id(), std::shared_ptr<general_joint>(new general_joint(0, 0, 0)));


				std::vector<double> motion = mstr::double_list(line);

				//rotation matrices
				std::unordered_map<int, cv::Mat> joint_rot_mat;

				//set joints
				int m_read_offset = 0;

				for (unsigned int i = 0; i < joint_sequence.size(); i++)
				{
					if (i != 0 && !next_skel->get_hierarchy()->at(joint_sequence.at(i))->is_parent())
					{
						//joint is end site therefore has no motion information

						//offset
						cv::Vec3d orig_offset = mae::math::internal_math::joint_to_vec(offset_skel->get_joint(joint_sequence.at(i)))
								- mae::math::internal_math::joint_to_vec(
										offset_skel->get_joint(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()));

						cv::Vec3d new_offset = mae::math::internal_math::matrix_mul(
								joint_rot_mat.at(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()), orig_offset);

						cv::Vec3d parent_pos = mae::math::internal_math::joint_to_vec(
								next_skel->get_joint(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()));

						next_skel->set_joint(joint_sequence.at(i), mae::math::internal_math::vec_to_joint(new_offset + parent_pos));
					}
					else
					{
						int m_read_offset_tmp = 0;
						std::vector<int> channels = joint_channel.at(joint_sequence.at(i));
						
                        //offset
                        cv::Vec3d motion_offset;
                        motion_offset[0] = 0;
                        motion_offset[1] = 0;
                        motion_offset[2] = 0;
                        
                        if (channels.at(0) != -1 || channels.at(1) != -1 || channels.at(2) != -1)
                        {
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

							rot_mats_tmp_vec.push_back(mae::math::internal_math::matrix_rot_z(mae::math::math::deg_to_rad(rot_zeta)));
						}

						if (channels.at(4) != -1)
						{
							rot_xi = motion.at(m_read_offset + channels.at(4));
							m_read_offset_tmp++;
                            const cv::Mat &r = mae::math::internal_math::matrix_rot_x(mae::math::math::deg_to_rad(rot_xi));
                            
                            if (channels.at(4) < channels.at(3))
							{
								rot_mats_tmp_vec.push_front(r);
							}
							else
							{
								rot_mats_tmp_vec.push_back(r);
							}
						}

						if (channels.at(5) != -1)
						{
							rot_ypsilon = motion.at(m_read_offset + channels.at(5));
							m_read_offset_tmp++;
                            const cv::Mat &r = mae::math::internal_math::matrix_rot_y(mae::math::math::deg_to_rad(rot_ypsilon));
                            
                            if (channels.at(5) < channels.at(3) && channels.at(5) < channels.at(4))
							{
								rot_mats_tmp_vec.push_front(r);
							}
							else if (channels.at(5) > channels.at(3) && channels.at(5) > channels.at(4))
							{
								rot_mats_tmp_vec.push_back(r);
							}
							else
							{
								std::list<cv::Mat>::iterator it = rot_mats_tmp_vec.begin();
								it++;
								rot_mats_tmp_vec.insert(it, r);
							}
						}

						for (std::list<cv::Mat>::const_iterator iterator = rot_mats_tmp_vec.begin(), end =
								rot_mats_tmp_vec.end(); iterator != end; ++iterator)
						{
							motion_rot_mat *= *iterator;
						}

						if (i != 0)
						{
                            motion_rot_mat = joint_rot_mat.at(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()) * motion_rot_mat;
						}

						joint_rot_mat.insert(std::make_pair(joint_sequence.at(i), motion_rot_mat));

						//apply rot_mat and offset to joints
						if (i == 0)
						{
							//handle root element
                            next_skel->set_joint(joint_sequence.at(i), mae::math::internal_math::vec_to_joint(motion_offset));
						}
						else
						{
							//handle any other element
							
							//determine the bone in the offset skeleton
							cv::Vec3d orig_offset = mae::math::internal_math::joint_to_vec(offset_skel->get_joint(joint_sequence.at(i)))
									- mae::math::internal_math::joint_to_vec(
											offset_skel->get_joint(
                                                    next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()));
							
							//determine the rotated bone for the current frame
							cv::Vec3d new_offset = mae::math::internal_math::matrix_mul(
										joint_rot_mat.at(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()),
										orig_offset);
							
							cv::Vec3d parent_pos = mae::math::internal_math::joint_to_vec(
									next_skel->get_joint(next_skel->get_hierarchy()->at(joint_sequence.at(i))->get_parent()->get_id()));

                            next_skel->set_joint(joint_sequence.at(i),
                                                 mae::math::internal_math::vec_to_joint(new_offset + parent_pos));
						}

						//move read offset
						m_read_offset += m_read_offset_tmp;
					}
				}

				skeletons.push_back(next_skel);
			}

			return std::shared_ptr<bvh_data>(new bvh_data(skeletons, frame_time));
		}
        
        
        void bvh_controller::set_anchors_and_directions(std::shared_ptr<bvh_spec> &spec, std::shared_ptr<general_skeleton> offset_skel, const std::shared_ptr<hierarchy> &hy) const
        {
		    //get anchors and define right-left and top-down direction for the skeleton
            bool left_anchor_undef = true;
            int left_anchor_id = -1;
            bool right_anchor_undef = true;
            int right_anchor_id = -1;
            bool top_anchor_undef = true;
            int top_anchor_id = -1;
            bool down_anchor_undef = true;
            int down_anchor_id = -1;
            std::vector<std::shared_ptr<hierarchy_element> > hy_els = hy->get_element_sequence();
            for (unsigned int i = 0; i < hy_els.size(); i++)
            {
                if (left_anchor_undef && mstr::to_lower(hy_els.at(i)->get_name()) == spec->get_left_anchor())
                {
                    left_anchor_id = hy_els.at(i)->get_id();
                    left_anchor_undef = false;
                }
                else if (right_anchor_undef && mstr::to_lower(hy_els.at(i)->get_name()) == spec->get_right_anchor())
                {
                    right_anchor_id = hy_els.at(i)->get_id();
                    right_anchor_undef = false;
                }
                else if (top_anchor_undef && mstr::to_lower(hy_els.at(i)->get_name()) == spec->get_top_anchor())
                {
                    top_anchor_id = hy_els.at(i)->get_id();
                    top_anchor_undef = false;
                }
                else if (down_anchor_undef && mstr::to_lower(hy_els.at(i)->get_name()) == spec->get_bottom_anchor())
                {
                    down_anchor_id = hy_els.at(i)->get_id();
                    down_anchor_undef = false;
                }

                if (!left_anchor_undef && !right_anchor_undef && !top_anchor_undef && !down_anchor_undef)
                {
                    break;
                }
            }
            
            if (left_anchor_undef || right_anchor_undef || top_anchor_undef || down_anchor_undef)
            {
				throw std::invalid_argument("At least one anchor could not be found!");
            }
            
            offset_skel->set_right_left(
                    std::shared_ptr<bone>(
                            new bone(bone::RESERVED_RIGHT_LEFT, "RIGHT_LEFT", right_anchor_id, left_anchor_id)));
            offset_skel->set_top_down(
                    std::shared_ptr<bone>(
                            new bone(bone::RESERVED_TOP_DOWN, "TOP_DOWN", top_anchor_id, down_anchor_id)));
        }
        
        std::shared_ptr<bvh_data> bvh_controller::read_bvh_file(
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
				return std::shared_ptr<bvh_data>(new bvh_data(std::vector<std::shared_ptr<general_skeleton> >(), 0.0));
			}
		}

		std::vector<int> bvh_controller::parse_channels(std::string& value, unsigned int pos)
		{
			std::pair<std::string::size_type, std::string::size_type> pos_channel = mstr::find_line(value, "channels",
					pos);
			std::vector<std::string> str_channels = mstr::split(value, pos_channel.first + 8, pos_channel.second - 8);

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

			std::vector<double> offset = mstr::double_list(value, pos_offset.first + 6, pos_offset.second - 6);

			if (offset.size() != 3)
			{
				throw std::invalid_argument("bvh_controller: More than 3 values to parse for offset.");
			}

			cv::Vec3d el_position = mae::math::internal_math::stdvec_to_vec3d(offset) + mae::math::internal_math::joint_to_vec(parent_joint);

			return mae::math::internal_math::vec_to_joint(el_position);
		}

		std::shared_ptr<hierarchy_element> bvh_controller::generate_hierarchy_element(std::shared_ptr<bvh_spec> spec,
				int element_count, std::string element_name, bool is_dummy)
		{
			std::map<std::string, int> joint_str;
			std::map<std::string, bool> joint_torso;

			if (spec != nullptr)
			{
				joint_str = spec->get_id_map();
				joint_torso = spec->get_basis_map();
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
        
        std::shared_ptr<general_skeleton> bvh_controller::read_offset_skeleton(const std::string& bvh_str, std::shared_ptr<bvh_spec> spec, std::vector<int> &joint_sequence, std::unordered_map<int, std::vector<int> > &joint_channel)
        {
		    std::string tmp = mstr::to_lower(bvh_str);
		    
            std::shared_ptr<general_skeleton> offset_skel = std::make_shared<general_skeleton>();
            
            int endeffector_count = 0;
    
            int element_count = 0;
    
            std::pair<std::string::size_type, std::string::size_type> pos_root = mstr::find_line(tmp, "root");
            std::string el_root = mstr::trim(std::string(bvh_str, pos_root.first + 4, pos_root.second - 4));
    
            //get root element for hierarchy
            element_count++;
            std::shared_ptr<hierarchy_element> hy_root = generate_hierarchy_element(spec, element_count, el_root,
                                                                                    false);
    
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
//                    std::cout << "pos_bracket == npos. el_parent: " << h_parent->get_name() << std::endl;
                    //no bracket to follow, therefore syntax error
                    throw std::invalid_argument("Syntax error in BVH file. Cannot parse initial pose.");
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
                    std::string el_joint = mstr::trim(std::string(bvh_str, pos_joint.first + 5, pos_joint.second - 5));
            
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
                    std::shared_ptr<hierarchy_element> hy_element = generate_hierarchy_element(spec, element_count,
                                                                                               el_joint, el_dummy);
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
                            //no closing bracket found, therefore syntax error
//							return std::shared_ptr<bvh_data>(new bvh_data(skeletons, frame_time));
                            std::stringstream sstr;
                            sstr << "Syntax error in BVH file. Cannot parse initial pose: no closing bracket found for end effector. el_joint: " << hy_end->get_name();
                            throw std::invalid_argument(sstr.str());
                        }
                        read_pos++;
                    }
                    read_depth++;
                }
            }
            std::shared_ptr<hierarchy> hy = std::shared_ptr<hierarchy>(new hierarchy(hy_root));
            offset_skel->set_hierarchy(hy);
    
            //get anchors and define right-left and top-down direction for the skeleton
            set_anchors_and_directions(spec, offset_skel, hy);
            
            return offset_skel;
        }
        
    } // namespace fl
} // namespace mae
