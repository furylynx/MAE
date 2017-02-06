/*
 * bvh_data.hpp
 *
 *  Created on: 07.02.2015
 *      Author: furylynx
 */

#ifndef BVH_DATA_HPP_
#define BVH_DATA_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../general_skeleton.hpp"

//global includes
#include <vector>
#include <memory>
#include <exception>

namespace mae
{
	namespace fl
	{

		class bvh_data
		{
			public:
				/**
				 * Creates a new bvh data object.
				 */
				bvh_data();

				/**
				 * Creates a new bvh data object.
				 *
				 * @param skeleton_data The skeleton data from the file.
				 * @param framerate The applied framerate.
				 */
				bvh_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data, double framerate);
				virtual ~bvh_data();

				/**
				 * Sets the skeleton data.
				 *
				 * @param skeleton_data The skeleton data.
				 */
				virtual void set_skeleton_data(std::vector<std::shared_ptr<general_skeleton> > skeleton_data);

				/**
				 * Returns the skeleton data.
				 *
				 * @return The skeleton data.
				 */
				virtual std::vector<std::shared_ptr<general_skeleton> > get_skeleton_data() const;

				/**
				 * Sets the framerate.
				 *
				 * @param framerate The framerate.
				 */
				virtual void set_framerate(double framerate);

				/**
				 * Returns the framerate.
				 *
				 * @return The framerate.
				 */
				virtual double get_framerate() const;


			private:
				std::vector<std::shared_ptr<general_skeleton> > skeleton_data_;
				double framerate_;
		};

	} // namespace fl
} // namespace mae

#endif // BVH_DATA_HPP_
