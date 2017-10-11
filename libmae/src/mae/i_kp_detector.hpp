#ifndef MAE_IKEYPOSEDETECTOR_HPP_
#define MAE_IKEYPOSEDETECTOR_HPP_

//custom includes
#include "general_pose.hpp"
#include "general_enriched_pose.hpp"
#include "bone.hpp"

//global includes
#include <vector>
#include <list>
#include <memory>

namespace mae {

		class i_kp_detector {
			public:
				virtual ~i_kp_detector(){}

				/**
				 * Estimates the current frame and returns an enriched pose. Edits the given enriched poses,
				 * (e.g. sets key pose to false) but does not append the new enriched pose to the vector.
				 * Instead the new enriched pose is returned.
				 *
				 * @param framerate The framerate.
				 * @param currentPose The currently processed pose.
				 * @param previousSequence The previous sequence which will be edited too.
				 * @param bodyParts All body parts that shall be processed.
				 * @return The enriched pose.
				 */
				virtual std::shared_ptr<general_enriched_pose> estimate_frame(double framerate, std::shared_ptr<general_pose> currentPose, std::list<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<bone> bodyParts) = 0;

				/**
				 * Clears the buffer used to store the data.
				 */
				virtual void clear_buffer() = 0;
		};

} // namespace mae

#endif // MAE_IKEYPOSEDETECTOR_HPP_
