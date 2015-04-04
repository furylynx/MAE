/*
 * msr_data.cpp
 *
 *  Created on: 04.04.2015
 *      Author: keks
 */

#include "msr_data.hpp"

namespace mae
{
	namespace fl
	{

		msr_data::msr_data()
		{
			framerate_ = 1/30;
		}

		msr_data::~msr_data()
		{

		}

		msr_data::msr_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data, double framerate)
		{
			skeleton_data_ = skeleton_data;
			framerate_ = framerate;
		}


		void msr_data::set_skeleton_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data)
		{
			skeleton_data_ = skeleton_data;
		}

		std::vector<std::shared_ptr<general_skeleton> > msr_data::get_skeleton_data() const
		{
			return skeleton_data_;
		}

		void msr_data::set_framerate(double framerate)
		{
			framerate_ = framerate;
		}

		double msr_data::get_framerate() const
		{
			return framerate_;
		}


	} // namespace fl
} // namespace mae
