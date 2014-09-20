/*
 * skeleton_merger.cpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#include "skeleton_merger.hpp"

namespace mae
{

	skeleton_merger::skeleton_merger()
	{
		// TODO Auto-generated constructor stub

	}

	skeleton_merger::~skeleton_merger()
	{
		// TODO Auto-generated destructor stub
	}

	std::shared_ptr<general_skeleton> skeleton_merger::merge(std::vector<std::shared_ptr<general_skeleton> > skeletons)
	{
		std::shared_ptr<general_skeleton> result;

		//TODO merge

		return result;
	}

	std::vector<std::shared_ptr<general_skeleton> > skeleton_merger::merge(std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons)
	{
		std::vector<std::shared_ptr<general_skeleton> > result;

		for (unsigned int i = 0; i < skeletons.size(); i++)
		{
			result.push_back(merge(skeletons.at(i)));
		}

		return result;
	}

	std::vector<std::shared_ptr<general_skeleton> > skeleton_merger::merge_find_mapping(std::vector<std::shared_ptr<general_skeleton> > skeletons, int num_users)
	{
		std::vector<std::vector<std::shared_ptr<general_skeleton> > > mapped_skels;
		mapped_skels.reserve(num_users);

		//TODO find mapping
		//TODO use correlation to find mappings

		return merge(mapped_skels);
	}

} // namespace mae
