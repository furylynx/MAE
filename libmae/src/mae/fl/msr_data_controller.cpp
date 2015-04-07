/*
 * plain_data_controller.cpp
 *
 *  Created on: 04.04.2015
 *      Author: keks
 */

#include "msr_data_controller.hpp"

namespace mae
{
	namespace fl
	{

		msr_data_controller::msr_data_controller()
		{

		}

		msr_data_controller::~msr_data_controller()
		{

		}


		std::shared_ptr<msr_data> msr_data_controller::read_msr_file(std::string filename, std::shared_ptr<msr_spec> spec) const
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
				return read_msr_str(sstr.str(), spec);
			}
			else
			{
				return std::shared_ptr<msr_data>(new msr_data(std::vector<std::shared_ptr<general_skeleton> >(), 0.0));
			}
		}

		std::shared_ptr<msr_data> msr_data_controller::read_msr_file(std::string filename, std::shared_ptr<msr_spec> spec, unsigned int begin_frame, unsigned int end_frame) const
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
				return read_msr_str(sstr.str(), spec, begin_frame, end_frame);
			}
			else
			{
				return std::shared_ptr<msr_data>(new msr_data(std::vector<std::shared_ptr<general_skeleton> >(), 0.0));
			}
		}

		std::shared_ptr<msr_data> msr_data_controller::read_msr_str(std::string msr_str, std::shared_ptr<msr_spec> spec) const
		{
			unsigned int frames = 0;
			std::size_t line_count = 0;

			std::istringstream stream(msr_str);
			std::string line = "";
			while (mstr::trim(line).length() == 0)
			{
				std::getline(stream, line);
				line_count++;
			}

			line = mstr::trim(line);

			std::vector<std::string> spec_line_elements = mstr::split(line);

			if (spec_line_elements.size() != 2)
			{
				std::stringstream ex_sstr;
				ex_sstr << "Cannot parse the MSR data file. Invalid number of arguments on line " << line_count;
				throw std::runtime_error(ex_sstr.str());
			}

			frames = std::atoi(spec_line_elements.at(0).c_str());

			return read_msr_str(msr_str, spec, 0, frames);
		}

		std::shared_ptr<msr_data> msr_data_controller::read_msr_str(std::string msr_str, std::shared_ptr<msr_spec> spec, unsigned int begin_frame, unsigned int end_frame) const
		{
			if (begin_frame < end_frame)
			{
				throw std::invalid_argument("read_msr_str: begin_frame is greater than end_frame.");
			}

			unsigned int frames = 0;
			unsigned int amount_joints = 0;
			std::size_t line_count = 0;

			std::istringstream stream(msr_str);
			std::string line = "";
			while (mstr::trim(line).length() == 0)
			{
				std::getline(stream, line);
				line_count++;
			}

			line = mstr::trim(line);

			std::vector<std::string> spec_line_elements = mstr::split(line);

			if (spec_line_elements.size() != 2)
			{
				std::stringstream ex_sstr;
				ex_sstr << "Cannot parse the MSR data file. Invalid number of arguments on line " << line_count;
				throw std::runtime_error(ex_sstr.str());
			}

			frames = std::atoi(spec_line_elements.at(0).c_str());
			amount_joints = std::atoi(spec_line_elements.at(1).c_str());

			if (end_frame > frames)
			{
				end_frame = frames;
			}


			//advance in string until the demanded first frame is reached
			handle_frames(stream, begin_frame, amount_joints, &line_count, spec, false);

			//read skeleton data
			std::vector<std::shared_ptr<general_skeleton> > result_skeletons = handle_frames(stream, (end_frame-begin_frame), amount_joints, &line_count, spec, true);

			return std::shared_ptr<msr_data>(new msr_data(result_skeletons, 1/30));
		}



		std::string msr_data_controller::msr_str(std::vector<std::shared_ptr<general_skeleton> > data) const
		{
			std::stringstream result_sstr;

			unsigned int num_joints = 0;

			if (data.size() > 0)
			{
				num_joints = data.at(0)->get_hierarchy()->get_element_sequence().size();
			}

			//print amount of frames and the number of joints for each skeleton
			result_sstr << data.size() << " " << num_joints << std::endl;

			for (std::size_t i = 0; i < data.size(); i++)
			{
				std::shared_ptr<general_skeleton> skeleton = data.at(i);
				result_sstr << num_joints*2 << std::endl;

				std::vector<std::shared_ptr<hierarchy_element> > h_elements = skeleton->get_hierarchy()->get_sorted_element_sequence();

				for (std::size_t j = 0; j < h_elements.size(); j++)
				{
					std::shared_ptr<hierarchy_element> element = h_elements.at(j);

					std::shared_ptr<general_joint> joint = skeleton->get_joint(element->get_id());

					//dummy line (contains screen pos and depth info in original files)
					result_sstr << "0 0 0 0" << std::endl;
					result_sstr << joint->get_x() << " " << joint->get_y() << " " << joint->get_z() << " " << joint->get_confidence() << std::endl;

				}
			}

			return result_sstr.str();
		}

		std::string msr_data_controller::msr_str(std::shared_ptr<general_skeleton> data) const
		{
			std::vector<std::shared_ptr<general_skeleton> > result;
			result.push_back(data);
			return msr_str(result);
		}

		void msr_data_controller::print_msr_file(std::string filename, std::vector<std::shared_ptr<general_skeleton> > data) const
		{
			std::ofstream out_file(filename);
			out_file << msr_str(data);
			out_file.close();
		}

		void msr_data_controller::print_msr_file(std::string filename, std::shared_ptr<general_skeleton> data) const
		{
			std::ofstream out_file(filename);
			out_file << msr_str(data);
			out_file.close();
		}


		std::vector<std::shared_ptr<general_skeleton> > msr_data_controller::handle_frames(std::basic_istream<char>& stream, std::size_t amount_frames, std::size_t amount_joints, std::size_t* line_count, std::shared_ptr<msr_spec> spec, bool create_skeleton_data) const
		{
			std::vector<std::shared_ptr<general_skeleton> > result;

			std::map<unsigned int, int> id_map = spec->get_id_map();
			std::shared_ptr<hierarchy> hierarchy = spec->get_hierarchy();
			std::size_t lines_per_joint = spec->get_lines_per_joint();
			std::size_t pos_line_index = spec->get_pos_line_index();

			std::string line = "";

			for (std::size_t i = 0; i < amount_frames; i++)
			{
				while (mstr::trim(line).length() == 0)
				{
					std::getline(stream, line);
					(*line_count)++;
				}

				//get the amount of rows per frame
				std::vector<std::string> count_line_elements = mstr::split(line);

				if (count_line_elements.size() != 1)
				{
					std::stringstream ex_sstr;
					ex_sstr << "Cannot parse the MSR data file. Invalid number of arguments on line " << *line_count;
					throw std::runtime_error(ex_sstr.str());
				}

				std::size_t amount_rows_per_frame = std::atoi(count_line_elements.at(0).c_str());

				if (create_skeleton_data)
				{
					//create new skeleton
					std::shared_ptr<general_skeleton> skeleton = std::shared_ptr<general_skeleton>(new general_skeleton(hierarchy));

					for (std::size_t i = 0; i < amount_rows_per_frame; i++)
					{
						while (mstr::trim(line).length() == 0)
						{
							std::getline(stream, line);
							(*line_count)++;
						}


						if (i % lines_per_joint == pos_line_index && i < (amount_joints*lines_per_joint))
						{
							std::vector<std::string> joint_elements = mstr::split(line);

							if (joint_elements.size() != 4)
							{
								std::stringstream ex_sstr;
								ex_sstr << "Cannot parse the MSR data file. Invalid number of arguments on line " << *line_count;
								throw std::runtime_error(ex_sstr.str());
							}

							unsigned int row_id = (unsigned int)(i/lines_per_joint);

							//add joint to skeleton
							if (id_map.find(row_id) != id_map.end())
							{
									int body_part = id_map.at(row_id);
									double x = std::atof(joint_elements.at(0).c_str());
									double y = std::atof(joint_elements.at(1).c_str());
									double z = std::atof(joint_elements.at(2).c_str());
									double confidence = std::atof(joint_elements.at(3).c_str());

									skeleton->set_joint(body_part, std::shared_ptr<general_joint>(new general_joint(x, y, z, 0, confidence)));
							}
						}
					}

					//add skeleton to vector
					result.push_back(skeleton);
				}
				else
				{
					//no skeleton data is required, just skip the lines

					for (std::size_t i = 0; i < amount_rows_per_frame; i++)
					{
						while (mstr::trim(line).length() == 0)
						{
							std::getline(stream, line);
							(*line_count)++;
						}
					}
				}
			}

			return result;
		}

	} // namespace fl
} // namespace mae
