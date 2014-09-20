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
			/**
			 * Creates a new skeleton merger which merges skeleton data.
			 */
			skeleton_merger();
			virtual ~skeleton_merger();

			/**
			 * Merges several skeletons to one more accurate skeleton.
			 *
			 * @param skeletons The skeletons to be merged.
			 * @return The resulting skeleton.
			 */
			virtual std::shared_ptr<general_skeleton> merge(std::vector<std::shared_ptr<general_skeleton> > skeletons);

			/**
			 * Merges all skeletons in one bin into a new skeleton. This means that the outer vector is processed by index and all skeletons in this container are merged.
			 *
			 * @param skeletons The skeletons to be merged.
			 * @return The merged skeletons.
			 */
			virtual std::vector<std::shared_ptr<general_skeleton> > merge(std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons);

			/**
			 * Merges the skeleton data, which is present in data per stream, by finding a mapping for the skeletons and then merging the mapped skeletons. This means that the outer vector has one element for each stream
			 * and the inner vector represents the skeleton data of the different users on that stream.
			 *
			 * @param skeletons The skeleton data.
			 * @return The merged skeletons.
			 */
			virtual std::vector<std::shared_ptr<general_skeleton> > merge_find_mapping(std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons);
	};

} // namespace mae

#endif // SKELETON_MERGER_HPP_
