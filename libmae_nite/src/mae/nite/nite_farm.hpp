/*
 * nite_farm.hpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#ifndef NITE_FARM_HPP_
#define NITE_FARM_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "nite_controller.hpp"

//global includes
#include <memory>
#include <vector>
#include <string>

namespace mae
{
	namespace nite
	{

		class nite_farm
		{
			public:
				/**
				 * Creates a farm for nite controllers.
				 *
				 * @param controllers The controllers.
				 */
				nite_farm(std::vector<std::shared_ptr<nite_controller> > controllers);

				/**
				 * Creates a farm for nite controllers.
				 *
				 * @param configs The configurations for the controllers.
				 */
				nite_farm(std::vector<std::string> configs);
				virtual ~nite_farm();

				/**
				 * Adds a new controller to the farm, which is generated from the configuration.
				 *
				 * @param config The string configuration for the controller.
				 */
				virtual void add_controller(std::string config);

				/**
				 * Adds a controller to the farm.
				 *
				 * @param controller The controller.
				 */
				virtual void add_controller(std::shared_ptr<nite_controller> controller);

				/**
				 * Waits for an update on all controllers and merges the resulting skeletons for get a more accurate one for each tracked user.
				 *
				 * @param each_n_frames Use a value greater than one to skip frames.
				 * @return The merged skeletons.
				 */
				virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(unsigned int each_n_frames = 1);

				/**
				 * Returns true if the keyboard was hit since the start of the OpenNI controller.
				 *
				 * @return True if the keyboard was hit.
				 */
				virtual bool was_keyboard_hit();

				/**
				 * Returns true if the keyboard was hit since the start of the OpenNI controller.
				 *
				 * @return True if the keyboard was hit.
				 */
				static bool xn_was_keyboard_hit();


			private:
				std::vector<std::shared_ptr<nite_controller> > controllers_;

				/**
				 * Initializes the nite_controllers.
				 *
				 * @param configs The configurations for each camera.
				 */
				virtual void initialize_controllers(std::vector<std::string> configs);
		};

	} // namespace nite
} // namespace mae

#endif // NITE_FARM_HPP_
