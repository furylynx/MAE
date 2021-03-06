#ifndef MAE_GENERALKEYPOSEDETECTOR_HPP_
#define MAE_GENERALKEYPOSEDETECTOR_HPP_

//custom includes
#include "i_kp_detector.hpp"

#include "bone.hpp"

//global includes
#include <iostream>
#include <list>
#include <memory>

namespace mae
{

	class kp_detector: public i_kp_detector
	{
		public:
			/**
			 * Creates a new key pose detector.
			 *
			 * @param debug True if debug output shall be printed to the terminal.
			 */
			kp_detector(bool debug = false);

			virtual ~kp_detector();

			/**
			 * Estimates the current frame and returns an enriched pose. Edits the given enriched poses,
			 * (e.g., sets key pose to false) but does not append the new enriched pose to the vector.
			 * Instead the new enriched pose is returned.
			 *
			 * @param framerate The framerate.
			 * @param currentPose The currently processed pose.
			 * @param previousSequence The previous sequence which will be edited too.
			 * @param bodyParts All body parts that shall be processed.
			 * @return The enriched pose.
			 */
			virtual std::shared_ptr<general_enriched_pose> estimate_frame(double framerate, std::shared_ptr<general_pose> current_pose,
					std::list<std::shared_ptr<general_enriched_pose> > previous_sequence, std::vector<bone> body_parts);

			/**
			 * Clears the buffer used to store the data.
			 */
			virtual void clear_buffer();

		private:
			bool debug_;
			const unsigned int RANGE_KP = 5; //10 ??

	};

} // namespace mae

#endif // MAE_GENERALKEYPOSEDETECTOR_HPP_
