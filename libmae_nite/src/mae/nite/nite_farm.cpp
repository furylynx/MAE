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

		nite_farm::nite_farm(std::vector<std::shared_ptr<nite_controller> > controllers, unsigned int  max_users, bool debug)
		{
			max_users_ = max_users;
			debug_ = debug;
			running_ = true;

			merger_ = std::shared_ptr<mae::skeleton_merger>(new mae::skeleton_merger());

			for (unsigned int i=0 ; i < controllers.size(); i++)
			{
				add_controller(controllers.at(i));
			}
		}

		nite_farm::nite_farm(std::vector<std::string> configs, unsigned int  max_users, bool debug)
		{
			max_users_ = max_users;
			debug_ = debug;
			running_ = true;

			merger_ = std::shared_ptr<mae::skeleton_merger>(new mae::skeleton_merger());

			for(unsigned int i=0; i < configs.size(); i++)
			{
				add_controller(configs.at(i));
			}
		}

		nite_farm::~nite_farm()
		{
			running_ = false;

			for(unsigned int i = 0; i < threads_.size(); i++)
			{
				threads_.at(i).join();
			}
		}

		void nite_farm::add_controller(std::string config)
		{
			std::shared_ptr<nite_controller> nc = std::shared_ptr<nite_controller>(new nite_controller(config, max_users_, debug_));
			add_controller(nc);
		}

		void nite_farm::add_controller(std::shared_ptr<nite_controller> controller)
		{
			if (controllers_.size() == 0)
			{
				controllers_.push_back(controller);
				skeleton_data_.push_back(std::vector<std::shared_ptr<general_skeleton> >());

				//never used but index of vector remains consistent
				mutexes_.push_back(std::shared_ptr<std::mutex>(new std::mutex()));
			}
			else
			{
				unsigned int thread_id = controllers_.size();
				controllers_.push_back(controller);
				skeleton_data_.push_back(std::vector<std::shared_ptr<general_skeleton> >());
				mutexes_.push_back(std::shared_ptr<std::mutex>(new std::mutex()));
				threads_.push_back(std::thread(&nite_farm::nite_run, this, controller, thread_id));
			}
		}

		std::vector<std::shared_ptr<mae::general_skeleton> > nite_farm::wait_for_update(unsigned int each_n_frames)
		{
			if (controllers_.size() == 0)
			{
				throw std::invalid_argument("No controllers defined.");
			}

			//wait for an update on the first controller and use data present from all other controllers
			skeleton_data_.at(0) = controllers_.front()->wait_for_update(each_n_frames);

			for (unsigned int i = 0; i < mutexes_.size(); i++)
			{
				mutexes_.at(i)->lock();
			}

			std::vector<std::shared_ptr<mae::general_skeleton> > result = merger_->merge_find_mapping(skeleton_data_);

			for (unsigned int i = 0; i < mutexes_.size(); i++)
			{
				mutexes_.at(i)->unlock();
			}

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

		void nite_farm::nite_run(std::shared_ptr<nite_controller> controller, unsigned int id)
		{
			while (running_)
			{
				std::vector<std::shared_ptr<mae::general_skeleton> > data = controller->wait_for_update();
				mutexes_.at(id)->lock();

				skeleton_data_.at(id) = data;

				mutexes_.at(id)->unlock();
			}
		}

	} // namespace nite
} // namespace mae
