
#ifndef MAE_SENSOR_FARM_HPP
#define MAE_SENSOR_FARM_HPP

//custom includes
#include "i_sensor.hpp"
#include "sensor_info.hpp"
#include "../fl/skeleton_merger.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>

namespace mae
{
    namespace sensor
    {
        class sensor_farm {

            public:
                /**
                 * Creates a farm for sensors using the given sensors.
                 *
                 * @param controllers The controllers.
                 * @param max_users The number if maximum users accepted.
                 * @param debug True for debug output on terminal.
                 */
                sensor_farm(std::vector<std::shared_ptr<i_sensor> > sensors, unsigned int max_users = 15, bool debug = false);

                /**
                 * Creates a form for sensors.
                 * @param max_users
                 * @param debug
                 */
                sensor_farm(unsigned int max_users = 15, bool debug = false);


                virtual ~sensor_farm();

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
                 * Adds a sensor to the farm.
                 *
                 * @param sensor The skeleton tracker.
                 */
                virtual void add_sensor(std::shared_ptr<i_sensor> sensor);

                /**
                 * Waits for an update on all controllers and merges the resulting skeletons for get a more accurate one for each tracked user.
                 *
                 * @param each_n_frames Use a value greater than one to skip frames.
                 * @return The merged skeletons.
                 */
                virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(
                        unsigned int each_n_frames = 1);

                /**
                 * Waits for an update on all controllers and returns the present data.
                 *
                 * @param each_n_frames Use a value greater than one to skip frames.
                 * @return The skeleton data.
                 */
                virtual std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > wait_for_update_unmerged(
                        unsigned int each_n_frames = 1);

                /**
                 * Waits for an update on all controllers and returns the present data. Returns the merged data as first argument and unmerged data as second.
                 *
                 * @param each_n_frames Use a value greater than one to skip frames.
                 * @return The skeleton data.
                 */
                virtual std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >,
                        std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > > wait_for_update_both(
                        unsigned int each_n_frames = 1);

            protected:
                /**
                 * Returns the debug flag.
                 *
                 * @return The debug flag.
                 */
                virtual bool get_debug() const;

                /**
                 * Returns the maximum users taken into account.
                 *
                 * @return The max users.
                 */
                virtual unsigned int get_max_users() const;


            private:
                unsigned int max_users_;
                bool debug_;
                bool running_;

                std::vector<std::shared_ptr<i_sensor> > sensors_;
                std::vector<std::shared_ptr<std::thread> > threads_;
                std::vector<std::shared_ptr<std::mutex> > mutexes_;
                std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > skeleton_data_;

                std::shared_ptr<i_skeleton_merger<general_skeleton> > merger_;

                /**
                 * Runs the thread for the given i_sensor.
                 *
                 * @param sensor The sensor.
                 * @param thread_id The thread's ID.
                 */
                virtual void sensor_run(std::shared_ptr<i_sensor> sensor, unsigned int thread_id);

        };
    }
}



#endif //MAE_SENSOR_FARM_HPP
