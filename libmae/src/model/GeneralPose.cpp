/*
 * GeneralPose.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "GeneralPose.hpp"

namespace mae {
	namespace model {

		GeneralPose::GeneralPose() {
			this->hashmap_direction= std::unordered_map<int, int>();
			this->hashmap_distance= std::unordered_map<int, std::unordered_map<int, double> >();
		}


		GeneralPose::GeneralPose(std::unordered_map<int, int> hashmap_direction, std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance) {
			this->hashmap_direction = hashmap_direction;
			this->hashmap_distance = hashmap_distance;
		}

		GeneralPose::~GeneralPose() {
			hashmap_direction.clear();
			hashmap_distance.clear();
		}


		void GeneralPose::setDirection(int bodyPart, int direction){


			if (hashmap_direction.find(bodyPart) == hashmap_direction.end()){
				//key is not in map
				hashmap_direction.insert(std::make_pair(bodyPart, direction));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_direction[bodyPart] = direction;
			}

		}

		int GeneralPose::getDirection(int bodyPart){

			if (hashmap_direction.find(bodyPart) == hashmap_direction.end()){
				return -1;
			}else{
				return hashmap_direction[bodyPart];
			}

		}

		void GeneralPose::setDistance(int bodyPart, int direction, double distance){

			if (hashmap_distance.find(bodyPart) == hashmap_distance.end()){
				//key is not in map
				std::unordered_map<int, double> hm_dist_val = std::unordered_map<int, double>();
				hm_dist_val.insert(std::make_pair(direction, distance));

				hashmap_distance.insert(std::make_pair(bodyPart, hm_dist_val));

			}else{
				//key already exists, load inner hashmap containing assignments of direction to distance

				std::unordered_map<int, double> hm_dist_val = hashmap_distance[bodyPart];

				if (hm_dist_val.find(direction) == hm_dist_val.end()){
					//no key present for the given direction therefore a new one will be created
					hm_dist_val.insert(std::make_pair(direction, distance));

				}else{
					//update distance value for direction
					hm_dist_val[direction] = distance;
				}
			}

		}



		double GeneralPose::getDistance(int bodyPart, int direction){

			if (hashmap_distance.find(bodyPart) == hashmap_distance.end()){
				return -1;
			}else{
				std::unordered_map<int, double> hm_dist_val = hashmap_distance[bodyPart];

				if (hm_dist_val.find(bodyPart) == hm_dist_val.end()){
					return -1;
				}else{
					return hm_dist_val[bodyPart];
				}
			}
		}

	} // namespace model
} // namespace mae
