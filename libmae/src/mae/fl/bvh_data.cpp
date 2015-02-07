/*
 * bvh_data.cpp
 *
 *  Created on: 07.02.2015
 *      Author: furylynx
 */

#include "bvh_data.hpp"

namespace mae
{
	namespace fl
	{

		bvh_data::bvh_data()
		{
			framerate_ = 0;
		}

		bvh_data::~bvh_data()
		{
		}

		bvh_data::bvh_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data, double framerate)
		{
			skeleton_data_ = skeleton_data;
			framerate_ = framerate;
		}


		void bvh_data::set_skeleton_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data)
		{
			skeleton_data_ = skeleton_data;
		}

		std::vector<std::shared_ptr<general_skeleton> > bvh_data::get_skeleton_data() const
		{
			return skeleton_data_;
		}

		void bvh_data::set_framerate(double framerate)
		{
			framerate_ = framerate;
		}

		double bvh_data::get_framerate() const
		{
			return framerate_;
		}

	} // namespace math
} // namespace mae
