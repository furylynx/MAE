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
	namespace model
	{

		class GeneralPose
		{
			public:
				GeneralPose();
				GeneralPose(std::unordered_map<int, int> hashmap_direction,
						std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance);
				virtual ~GeneralPose();

				virtual void setDirection(int bodyPart, int direction);
				virtual int getDirection(int bodyPart);

				virtual void setDistance(int bodyPart, int direction, double distance);
				virtual double getDistance(int bodyPart, int direction);

			private:
				std::unordered_map<int, int> hashmap_direction;
				std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance;

		};

	} /* namespace model */
} /* namespace mae */

#endif /* GENERALPOSE_HPP_ */
