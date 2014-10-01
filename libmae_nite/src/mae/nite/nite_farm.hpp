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
#include "device_info.hpp"

//global includes
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include <mae/mae.hpp>

namespace mae
{
	namespace nite
	{

		class nite_farm
		{
			public:
				/**
				 * Creates a farm for nite controllers from the controllers.
				 *
				 * @param controllers The controllers.
				 * @param max_users The number if maximum users accepted.
				 * @param debug True for debug output on terminal.
				 */
				nite_farm(std::vector<std::shared_ptr<nite_controller> > controllers, unsigned int max_users = 15,
						bool debug = false);

				/**
				 * Creates a farm for nite controllers from the configration files.
				 *
				 * @param configs The paths to the XML configurations for the controllers.
				 * @param max_users The number if maximum users accepted.
				 * @param debug True for debug output on terminal.
				 */
				nite_farm(std::vector<std::string> configs, unsigned int max_users = 15, bool debug = false);

				/**
				 * Creates a farm for nite controllers from the devices info and the with the present configuration.
				 *
				 * @param devices The devices info.
				 * @param config_path The path to the XML configuration file.
				 * @param max_users The number if maximum users accepted.
				 * @param debug True for debug output on terminal.
				 */
				nite_farm(std::vector<std::shared_ptr<device_info> > devices, std::string config_path, unsigned int max_users = 15, bool debug = false);

				/**
				 * Creates a farm for nite controllers from present configuration. Adds a controller for each available device.
				 *
				 * @param config_path The path to the XML configuration file.
				 * @param max_users The number if maximum users accepted.
				 * @param debug True for debug output on terminal.
				 */
				nite_farm(std::string config_path, unsigned int max_users = 15, bool debug = false);
				virtual ~nite_farm();

				/**
				 * Sets the skeleton merger used to merge skeletons from the stream. This
				 * overwrites the default merger applied to the farm.
				 *
				 * @param merger The merger.
				 */
				virtual void set_merger(std::shared_ptr<i_skeleton_merger<general_skeleton> > merger);

				/**
				 * Returns the currently applied skeleton merger.
				 *
				 * @return The merger.
				 */
				virtual std::shared_ptr<i_skeleton_merger<general_skeleton> > get_merger();

				/**
				 * Adds a new controller to the farm, which is generated from the XML configuration.
				 * The device is selected by the configuration file.
				 *
				 * @param config_path The path to the XML configuration file.
				 */
				virtual void add_controller(std::string config_path);

				/**
				 * Adds a new controller to the farm, which is generated from the configuration.
				 * The device is selected by the device information.
				 *
				 * @param devi_info The device information
				 * @param config_path The string configuration for the controller.
				 */
				virtual void add_controller(std::shared_ptr<device_info> devi_info,std::string config_path);

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
				virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(
						unsigned int each_n_frames = 1);

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

				/**
				 * Lists all available OpenNI devices.
				 *
				 * @return The device info.
				 */
				static std::vector<std::shared_ptr<device_info> > list_available_device_infos();

				/**
				 * Returns the device info for the device with the serial number. Returns null
				 * if no info for the device with the given serial number is present.
				 *
				 * @param serial_number The serial number.
				 * @return The device info.
				 */
				static std::shared_ptr<device_info> get_device_info(std::string serial_number);

			private:
				unsigned int max_users_;
				bool debug_;

				std::vector<std::shared_ptr<nite_controller> > controllers_;
				std::vector<std::thread> threads_;
				std::vector<std::shared_ptr<std::mutex> > mutexes_;
				std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > skeleton_data_;
				bool running_;

				std::shared_ptr<i_skeleton_merger<general_skeleton> > merger_;

				/**
				 * Runs the thread for the given nite_controller.
				 */
				virtual void nite_run(std::shared_ptr<nite_controller> controller, unsigned int id);

				/**
				 * Lists all available OpenNI devices.
				 *
				 * @return The node info list.
				 */
				static xn::NodeInfoList list_available_devices();

				/**
				 * Returns the device node for the device info.
				 *
				 * @param devi The device info.
				 * @return The device node.
				 */
				static xn::NodeInfo get_node_info(device_info devi);
		};

	} // namespace nite
} // namespace mae

#endif // NITE_FARM_HPP_
