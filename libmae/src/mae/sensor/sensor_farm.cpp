
#include "sensor_farm.hpp"


namespace mae
{
    namespace sensor
    {

        sensor_farm::sensor_farm(std::vector<std::shared_ptr<i_sensor> > sensors, unsigned int max_users,
                               bool debug)
        {
            max_users_ = max_users;
            debug_ = debug;
            running_ = true;

            merger_ = std::shared_ptr<i_skeleton_merger<general_skeleton> >(new mae::fl::skeleton_merger());

            for (unsigned int i = 0; i < sensors.size(); i++)
            {
                add_sensor(sensors.at(i));
            }
        }

        sensor_farm::sensor_farm(unsigned int max_users, bool debug)
        {
            max_users_ = max_users;
            debug_ = debug;
            running_ = true;

            merger_ = std::shared_ptr<i_skeleton_merger<general_skeleton> >(new mae::fl::skeleton_merger());
        }

        sensor_farm::~sensor_farm()
        {
            for (unsigned int i = 0; i < threads_.size(); i++)
            {
                threads_.at(i)->join();
            }
        }

        void sensor_farm::set_merger(std::shared_ptr<i_skeleton_merger<general_skeleton> > merger)
        {
            merger_ = merger;
        }

        std::shared_ptr<i_skeleton_merger<general_skeleton> > sensor_farm::get_merger()
        {
            return merger_;
        }

        void sensor_farm::add_sensor(std::shared_ptr<i_sensor> sensor)
        {
            if (sensors_.size() == 0)
            {
                sensors_.push_back(sensor);
                skeleton_data_.push_back(std::vector<std::shared_ptr<general_skeleton> >());

                //never used but index of vector remains consistent
                mutexes_.push_back(std::shared_ptr<std::mutex>(new std::mutex()));
            }
            else
            {
                unsigned int thread_id = sensors_.size();
                sensors_.push_back(sensor);
                skeleton_data_.push_back(std::vector<std::shared_ptr<general_skeleton> >());
                mutexes_.push_back(std::shared_ptr<std::mutex>(new std::mutex()));
                threads_.push_back(
                        std::shared_ptr<std::thread>(
                                new std::thread(&sensor_farm::sensor_run, this, sensor, thread_id)));
            }
        }

        std::vector<std::shared_ptr<mae::general_skeleton> > sensor_farm::wait_for_update(unsigned int each_n_frames)
        {
            return merger_->merge_find_mapping(wait_for_update_unmerged(each_n_frames));
        }

        std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > sensor_farm::wait_for_update_unmerged(
                unsigned int each_n_frames)
        {
            if (sensors_.size() == 0)
            {
                throw std::invalid_argument("No controllers defined.");
            }

            //wait for an update on the first controller and use data present from all other controllers
            skeleton_data_.at(0) = sensors_.front()->wait_for_update(each_n_frames);

            for (unsigned int i = 1; i < mutexes_.size(); i++)
            {
                mutexes_.at(i)->lock();
            }

            std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > result = skeleton_data_;

            for (unsigned int i = 1; i < mutexes_.size(); i++)
            {
                mutexes_.at(i)->unlock();
            }

            return result;
        }

        std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >,
                std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > > sensor_farm::wait_for_update_both(
                unsigned int each_n_frames)
        {
            std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > unmerged = wait_for_update_unmerged(
                    each_n_frames);
            std::vector<std::shared_ptr<mae::general_skeleton> > merged = merger_->merge_find_mapping(unmerged);
            return std::make_pair(merged, unmerged);
        }

        bool sensor_farm::get_debug() const
        {
            return debug_;
        }

        unsigned int sensor_farm::get_max_users() const
        {
            return max_users_;
        }


        void sensor_farm::sensor_run(std::shared_ptr<i_sensor> controller, unsigned int thread_id)
        {
            while (running_ && controller != nullptr)
            {
                std::vector<std::shared_ptr<mae::general_skeleton> > data = controller->wait_for_update();
                mutexes_.at(thread_id)->lock();

                skeleton_data_.at(thread_id) = data;

                mutexes_.at(thread_id)->unlock();

            }
        }

    } // namespace nite2
} // namespace mae
