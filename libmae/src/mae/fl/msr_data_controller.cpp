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
			std::shared_ptr<msr_data> result;

			//TODO parse file

			return result;
		}

		std::shared_ptr<msr_data> msr_data_controller::read_msr_str(std::string msr_str, std::shared_ptr<msr_spec> spec, unsigned int begin_frame, unsigned int end_frame) const
		{
			std::shared_ptr<msr_data> result;

			//TODO parse file

			return result;
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

	} // namespace fl
} // namespace mae
