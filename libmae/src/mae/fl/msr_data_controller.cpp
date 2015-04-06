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

			std::map<unsigned int, int> id_map = spec->get_id_map();
			std::shared_ptr<hierarchy> h = spec->get_hierarchy();

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
				std::cerr << "Max frame is greater than amount of frames" << std::endl;
			}


			//advance in string until the demanded first frame is reached
			handle_frames(stream, begin_frame, &line_count, false);

			//read skeleton data
			std::vector<std::shared_ptr<general_skeleton> > result_skeletons = handle_frames(stream, (end_frame-begin_frame), &line_count, true);

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

				std::vector<std::shared_ptr<hierarchy_element> > h_elements = skeleton->get_hierarchy()->get_element_sequence();

				for (std::size_t j = 0; j < h_elements.size(); j++)
				{
					std::shared_ptr<hierarchy_element> element = h_elements.at(j);

					std::shared_ptr<general_joint> joint = skeleton->get_joint(element->get_id());
					result_sstr << joint->get_x() << " " << joint->get_y() << " " << joint->get_z() << " " << joint->get_confidence() << std::endl;

					//TODO line necessary?
					result_sstr << "0 0 0 0" << std::endl;
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


		std::vector<std::shared_ptr<general_skeleton> > msr_data_controller::handle_frames(std::basic_istream<char>& stream, std::size_t amount_frames, std::size_t* line_count, bool create_skeleton_data) const
		{
			std::vector<std::shared_ptr<general_skeleton> > result;

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

				unsigned int amount_rows_per_frame = std::atoi(count_line_elements.at(0).c_str());

				//TODO
			}

			return result;
		}

	} // namespace fl
} // namespace mae
