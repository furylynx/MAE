/*
 * GeneralEnrichedPose.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "GeneralEnrichedPose.hpp"


namespace mae {
	namespace model {

		GeneralEnrichedPose::GeneralEnrichedPose(){
			this->hashmap_keypose= std::unordered_map<int, bool>();
			this->hashmap_inmotion= std::unordered_map<int, bool>();
		}


		GeneralEnrichedPose::GeneralEnrichedPose(std::unordered_map<int, bool> hashmap_keypose, std::unordered_map<int, bool> hashmap_inmotion){
			this->hashmap_keypose = hashmap_keypose;
			this->hashmap_inmotion = hashmap_inmotion;
		}


		GeneralEnrichedPose::~GeneralEnrichedPose() {
			this->hashmap_keypose.clear();
			this->hashmap_inmotion.clear();
		}

		void GeneralEnrichedPose::setKeyPose(int bodyPart, bool isKeyPose){

			if (hashmap_keypose.find(bodyPart) == hashmap_keypose.end()){
				//key is not in map
				hashmap_keypose.insert(std::make_pair(bodyPart, isKeyPose));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_keypose[bodyPart] = isKeyPose;
			}

		}


		bool GeneralEnrichedPose::isKeyPose(int bodyPart){
			if (hashmap_keypose.find(bodyPart) == hashmap_keypose.end()){
				return hashmap_keypose[bodyPart];
			}else{
				return false;
			}
		}

		void GeneralEnrichedPose::setInMotion(int bodyPart, bool isInMotion){

			if (hashmap_inmotion.find(bodyPart) == hashmap_inmotion.end()){
				//key is not in map
				hashmap_inmotion.insert(std::make_pair(bodyPart, isInMotion));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_inmotion[bodyPart] = isInMotion;
			}
		}


		bool GeneralEnrichedPose::isInMotion(int bodyPart){

			if (hashmap_inmotion.find(bodyPart) == hashmap_inmotion.end()){
				return hashmap_inmotion[bodyPart];
			}else{
				return false;
			}
		}







	} // namespace model
} // namespace mae
