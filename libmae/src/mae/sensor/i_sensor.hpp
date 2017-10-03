//
// Created on 13/02/2017.
//

#ifndef MAE_I_SENSOR_HPP
#define MAE_I_SENSOR_HPP

//custom includes
#include "../general_skeleton.hpp"
#include "../general_skeleton_basis_pair.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>

namespace mae {
    namespace sensor {
        class i_sensor {
            public:
                virtual ~i_sensor(){}

                /**
				 * Waits until the next (n-th) frame is processed and returns the skeleton data on that frame.
				 * This is a blocking method.
				 *
				 * @param each_n_frames The n-th frame to be processed.
				 * @return The skeleton data.
				 */
                virtual std::vector<std::shared_ptr<mae::general_skeleton> > wait_for_update(unsigned int each_n_frames = 1) = 0;

                /**
				 * Waits until the next (n-th) frame is processed and returns the skeleton data as well as the basis on that frame.
				 * This is a blocking method.
				 *
				 * @param each_n_frames The n-th frame to be processed.
				 * @return The skeleton data and basis pair.
				 */
                virtual std::vector<std::shared_ptr<mae::general_skeleton_basis_pair> > wait_for_update_with_basis(unsigned int each_n_frames = 1) = 0;
        };
    }
}


#endif //MAE_I_SENSOR_HPP
