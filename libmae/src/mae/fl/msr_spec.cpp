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

		msr_spec::msr_spec(std::map<std::string, int> id_map, std::shared_ptr<hierarchy> hierarchy)
		{
			id_map_ = id_map;
			hierarchy_ = hierarchy;
		}

		msr_spec::~msr_spec()
		{

		}

		std::map<unsigned int, int> msr_spec::get_id_map()
		{
			return id_map_;
		}

		std::shared_ptr<hierarchy> msr_spec::get_hierarchy()
		{
			return hierarchy_;
		}

		static std::shared_ptr<msr_spec> msr_spec::default_spec()
		{
			std::shared_ptr<hierarchy> h = hierarchy::default_hierarchy();

			std::unordered_map<unsigned int, int> id_map;

			std::vector<std::shared_ptr<hierarchy_element> > h_elements = h->get_element_sequence();

			for (std::size_t i = 0; i < h_elements.size(); i++)
			{
				id_map.insert(std::make_pair(i, h_elements.at(i)->get_id()));
			}

			return std::shared_ptr<msr_spec>(new msr_spec(id_map, h));

		}

	} // namespace fl
} // namespace mae
