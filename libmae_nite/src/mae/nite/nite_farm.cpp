/*
 * nite_farm.cpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#include "nite_farm.hpp"

namespace mae
{
	namespace nite
	{

		nite_farm::nite_farm(std::vector<std::shared_ptr<nite_controller> > controllers)
		{
			controllers_ = controllers;
		}

		nite_farm::nite_farm(std::vector<std::string> configs)
		{
			initialize_controllers(configs);
		}

		nite_farm::~nite_farm()
		{
		}

		void nite_farm::add_controller(std::string config)
		{
			//TODO add controller
		}

		void nite_farm::add_controller(std::shared_ptr<nite_controller> controller)
		{
			//TODO add controller
		}

		std::vector<std::shared_ptr<mae::general_skeleton> > nite_farm::wait_for_update(unsigned int each_n_frames)
		{
			std::vector<std::shared_ptr<mae::general_skeleton> > result;
			//TODO wait for an update on all controllers

			return result;
		}

		bool nite_farm::was_keyboard_hit()
		{
			return nite_controller::xn_was_keyboard_hit();
		}

		bool nite_farm::xn_was_keyboard_hit()
		{
			return nite_controller::xn_was_keyboard_hit();
		}

		void nite_farm::initialize_controllers(std::vector<std::string> configs)
		{
			//TODO initialize controllers

		}

	} // namespace nite
} // namespace mae
