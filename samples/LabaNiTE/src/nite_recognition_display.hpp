/*
 * nite_recognition_display.hpp
 *
 *  Created on: 02.09.2014
 *      Author: keks
 */

#ifndef NITE_RECOGNITION_DISPLAY_HPP_
#define NITE_RECOGNITION_DISPLAY_HPP_

//custom includes
#include "sdl_controller.hpp"

//global includes
#include <mae/e_bone.hpp>
#include <mae/fl/e_fl_direction.hpp>

#include <mae/general_pose.hpp>
#include <mae/i_pose_listener.hpp>
#include <mae/i_recognition_listener.hpp>
#include <mae/fl/laban/laban_sequence.hpp>


namespace lni
{

	class nite_recognition_display : public mae::i_recognition_listener<mae::fl::laban::laban_sequence>
	{
		public:
			nite_recognition_display();
			virtual ~nite_recognition_display();

			/**
			 * Is invoked each time sequences were recognized.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(long timestamp, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences);

	};

} // namespace lni

#endif // NITE_RECOGNITION_DISPLAY_HPP_
