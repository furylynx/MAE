/*
 * GeneralPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALPOSE_HPP_
#define GENERALPOSE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <unordered_map>
#include <iostream>

namespace mae
{

	class general_pose
	{
		public:
			general_pose();
			general_pose(std::unordered_map<int, int> hashmap_direction,
					std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance);
			virtual ~general_pose();

			virtual void set_direction(int body_part, int direction);
			virtual int get_direction(int body_part);

			virtual void set_distance(int body_part, int direction, double distance);
			virtual double get_distance(int body_part, int direction);

		private:
			std::unordered_map<int, int> hashmap_direction;
			std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance;

	};

} // namespace mae

#endif // GENERALPOSE_HPP_
