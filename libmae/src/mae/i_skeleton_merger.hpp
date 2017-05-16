#ifndef MAE_I_SKELETON_MERGER_HPP_
#define MAE_I_SKELETON_MERGER_HPP_

//custom includes
//...

//global includes
#include <vector>
#include <memory>

namespace mae
{
	template <typename T>
	class i_skeleton_merger
	{
		public:
			virtual ~i_skeleton_merger(){}

			/**
			 * Merges several skeletons to one more accurate skeleton.
			 *
			 * @param skeletons The skeletons to be merged.
			 * @return The resulting skeleton.
			 */
			virtual std::shared_ptr<T> merge(
					std::vector<std::shared_ptr<T> > skeletons) = 0;

			/**
			 * Merges all skeletons in one bin into a new skeleton. This means that the outer vector is processed by index and all skeletons in this container are merged.
			 *
			 * @param skeletons The skeletons to be merged.
			 * @return The merged skeletons.
			 */
			virtual std::vector<std::shared_ptr<T> > merge(
					std::vector<std::vector<std::shared_ptr<T> > > skeletons) = 0;

			/**
			 * Merges the skeleton data, which is present in data per stream, by finding a mapping for the skeletons and then merging the mapped skeletons. This means that the outer vector has one element for each stream
			 * and the inner vector represents the skeleton data of the different users on that stream.
			 *
			 * @param skeletons The skeleton data.
			 * @return The merged skeletons.
			 */
			virtual std::vector<std::shared_ptr<T> > merge_find_mapping(
					std::vector<std::vector<std::shared_ptr<T> > > skeletons) = 0;

	};

} // namespace mae

#endif // MAE_I_SKELETON_MERGER_HPP_
