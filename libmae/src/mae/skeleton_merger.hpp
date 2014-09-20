/*
 * skeleton_merger.hpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#ifndef SKELETON_MERGER_HPP_
#define SKELETON_MERGER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_skeleton.hpp"

//global includes
#include <memory>
#include <vector>
#include <string>

namespace mae
{

	class skeleton_merger
	{
		public:
			skeleton_merger();
			virtual ~skeleton_merger();

			virtual std::shared_ptr<general_skeleton> merge(std::vector<std::shared_ptr<general_skeleton> > skeletons);

			virtual std::vector<std::shared_ptr<general_skeleton> > merge(std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons);

			virtual std::vector<std::shared_ptr<general_skeleton> > merge_find_mapping(std::vector<std::shared_ptr<general_skeleton> > skeletons, int num_users);
	};

} // namespace mae

#endif // SKELETON_MERGER_HPP_
