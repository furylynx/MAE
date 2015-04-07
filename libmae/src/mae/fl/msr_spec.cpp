/*
 * msr_spec.cpp
 *
 *  Created on: 04.04.2015
 *      Author: keks
 */

#include "msr_spec.hpp"

namespace mae
{
	namespace fl
	{

		msr_spec::msr_spec(std::map<unsigned int, int> id_map, std::shared_ptr<hierarchy> hierarchy, std::size_t lines_per_joint, std::size_t pos_line_index)
		{
			id_map_ = id_map;
			hierarchy_ = hierarchy;
			lines_per_joint_ = lines_per_joint;
			pos_line_index_ = pos_line_index;
		}

		msr_spec::~msr_spec()
		{

		}

		std::map<unsigned int, int> msr_spec::get_id_map() const
		{
			return id_map_;
		}

		std::shared_ptr<hierarchy> msr_spec::get_hierarchy() const
		{
			return hierarchy_;
		}

		std::size_t msr_spec::get_lines_per_joint() const
		{
			return lines_per_joint_;
		}

		std::size_t msr_spec::get_pos_line_index() const
		{
			return pos_line_index_;
		}

		std::shared_ptr<msr_spec> msr_spec::default_spec()
		{
			std::shared_ptr<hierarchy> h = hierarchy::default_hierarchy();

			std::map<unsigned int, int> id_map;

			std::vector<std::shared_ptr<hierarchy_element> > h_elements = h->get_sorted_element_sequence();

			for (std::size_t i = 0; i < h_elements.size(); i++)
			{
				id_map.insert(std::make_pair(i, h_elements.at(i)->get_id()));
			}

			return std::shared_ptr<msr_spec>(new msr_spec(id_map, h, 2, 1));

		}

		std::shared_ptr<msr_spec> msr_spec::default_msr_spec()
		{
			std::shared_ptr<hierarchy> h = hierarchy::default_kinect_hierarchy();

			std::map<unsigned int, int> id_map;

			std::vector<std::shared_ptr<hierarchy_element> > h_elements = h->get_sorted_element_sequence();

			for (std::size_t i = 0; i < h_elements.size(); i++)
			{
				id_map.insert(std::make_pair(i, h_elements.at(i)->get_id()));
			}

			return std::shared_ptr<msr_spec>(new msr_spec(id_map, h, 2, 1));
		}

	} // namespace fl
} // namespace mae
