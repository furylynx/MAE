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

		nite_farm::nite_farm(std::vector<std::shared_ptr<nite_controller> > controllers, unsigned int max_users,
				bool debug)
		{
			max_users_ = max_users;
			debug_ = debug;
			running_ = true;

			merger_ = std::shared_ptr<mae::skeleton_merger>(new mae::skeleton_merger());

			for (unsigned int i = 0; i < controllers.size(); i++)
			{
				add_controller(controllers.at(i));
			}
		}

		nite_farm::nite_farm(std::vector<std::string> configs, unsigned int max_users, bool debug)
		{
			max_users_ = max_users;
			debug_ = debug;
			running_ = true;

			merger_ = std::shared_ptr<mae::skeleton_merger>(new mae::skeleton_merger());

			for (unsigned int i = 0; i < configs.size(); i++)
			{
				add_controller(configs.at(i));
			}
		}

		nite_farm::nite_farm(std::vector<std::shared_ptr<device_info> > devices, std::string config_path,
				unsigned int max_users, bool debug)
		{
			max_users_ = max_users;
			debug_ = debug;
			running_ = true;

			merger_ = std::shared_ptr<mae::skeleton_merger>(new mae::skeleton_merger());

			for (unsigned int i = 0; i < devices.size(); i++)
			{
				add_controller(devices.at(i), config_path);
			}
		}

		nite_farm::nite_farm(std::string config_path, unsigned int max_users, bool debug) : nite_farm(nite_farm::list_available_device_infos(), config_path, max_users, debug)
		{
		}

		nite_farm::~nite_farm()
		{
			running_ = false;

			for (unsigned int i = 0; i < threads_.size(); i++)
			{
				threads_.at(i).join();
			}
		}

		void nite_farm::add_controller(std::string config_path)
		{
			std::shared_ptr<nite_controller> nc = std::shared_ptr<nite_controller>(
					new nite_controller(config_path, max_users_, debug_));
			add_controller(nc);
		}

		void nite_farm::add_controller(std::shared_ptr<device_info> devi_info,std::string config_path)
		{
			std::shared_ptr<nite_controller> nc = std::shared_ptr<nite_controller>(
					new nite_controller(devi_info, config_path, max_users_, debug_));
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

		xn::NodeInfoList nite_farm::list_available_devices()
		{
			xn::Context context;
			XnStatus status = context.Init();

			if (status != XN_STATUS_OK)
			{
				//std::cerr << "Could not initialize the context." << std::endl;

				throw std::runtime_error("Could not initialize the xn context.");
			}

			// find devices
			xn::EnumerationErrors errors;
			xn::NodeInfoList list;
			status = context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, list, &errors);

			if (status != XN_STATUS_OK)
			{
				//std::cerr << "Could not get the production trees." << std::endl;

				throw std::runtime_error("Could not get the production trees.");
			}

			context.Release();

			return list;
		}

		std::vector<std::shared_ptr<device_info> > nite_farm::list_available_device_infos()
		{
			std::vector<std::shared_ptr<device_info> > result;

			xn::Context context;
			XnStatus status = context.Init();

			if (status != XN_STATUS_OK)
			{
				context.Release();
				throw std::runtime_error("Could not initialize the xn context.");
			}

			// find devices
			xn::EnumerationErrors errors;
			xn::NodeInfoList list;
			status = context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, list, &errors); //XN_NODE_TYPE_DEVICE

			if (status != XN_STATUS_OK)
			{
				context.Release();
				throw std::runtime_error("Could not get the production trees.");
			}

			int i = 1;
			for (xn::NodeInfoList::Iterator it = list.Begin(); it != list.End(); ++it, ++i)
			{
				xn::NodeInfo device_node_info = *it;
				xn::Device device_node;

				device_node_info.GetInstance(device_node);
				XnBool device_exists = device_node.IsValid();

				if (!device_exists)
				{
					context.CreateProductionTree(device_node_info, device_node);
					// this might fail.
				}

				if (device_node.IsValid() && device_node.IsCapabilitySupported(XN_CAPABILITY_DEVICE_IDENTIFICATION))
				{
					const XnUInt32 n_string_buffer_size = 200;

					XnChar str_device_name[n_string_buffer_size];
					XnChar str_serial_number[n_string_buffer_size];
					XnChar str_vendor_name[n_string_buffer_size];

					XnUInt32 n_length = n_string_buffer_size;

					device_node.GetIdentificationCap().GetDeviceName(str_device_name, n_length);

					n_length = n_string_buffer_size;
					device_node.GetIdentificationCap().GetVendorSpecificData(str_vendor_name, n_string_buffer_size);

					n_length = n_string_buffer_size;
					device_node.GetIdentificationCap().GetSerialNumber(str_serial_number, n_length);

					result.push_back(
							std::shared_ptr<device_info>(
									new device_info(str_device_name, str_serial_number, str_vendor_name,
											device_node_info.GetCreationInfo())));
				}
				else
				{
					//std::cout << "[" << i << "] "<< device_node_info.GetCreationInfo() << std::endl;
				}

				// release the device if we created it
				if (!device_exists && device_node.IsValid())
				{
					device_node.Release();
				}
			}

			context.Release();

			return result;
		}

		std::shared_ptr<device_info> nite_farm::get_device_info(std::string serial_number)
		{
			std::vector<std::shared_ptr<device_info> > devices = list_available_device_infos();

			for (unsigned int i = 0; i < devices.size(); i++)
			{
				if (devices.at(i)->get_device_serial() == serial_number)
				{
					return devices.at(i);
				}
			}

			return nullptr;
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
