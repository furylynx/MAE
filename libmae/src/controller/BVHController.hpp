/*
 * BVHController.hpp
 *
 *  Created on: 11.06.2014
 *      Author: keks
 */

#ifndef BVHCONTROLLER_HPP_
#define BVHCONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/general_skeleton.hpp"
#include "../model/maej.hpp"
#include "MStr.hpp"

#include "../fl/FLMath.hpp"

//global includes
#include <stdio.h>
#include <vector>
#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <algorithm>


//TODO move to fl since it uses the math class

namespace mae
{

	class BVHController
	{
		public:
			BVHController();
			virtual ~BVHController();

			virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data);
			virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data, double framerate);

			virtual std::string bvh_str(std::shared_ptr<general_skeleton> data);

			virtual void bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename);
			virtual void bvh_file(std::shared_ptr<general_skeleton> data, std::string filename);

			virtual std::vector<std::shared_ptr<general_skeleton> > read_bvh(std::string bvh_str);
			virtual std::vector<std::shared_ptr<general_skeleton> > read_bvh_file(std::string filename);

		private:
			std::shared_ptr<general_joint> parse_offset(std::string& value, unsigned int pos, std::shared_ptr<general_joint> parent_joint);
			std::vector<int> parse_channels(std::string& value, unsigned int pos);

			std::vector<std::vector<int> > ext;
			std::vector<int> head;
			std::unordered_map<std::string, int> joint_str;

			std::unordered_map<int, int> end_effectors;

			const std::string Xpos = "xposition";
			const std::string Ypos = "yposition";
			const std::string Zpos = "zposition";
			const std::string Zrot = "zrotation";
			const std::string Xrot = "xrotation";
			const std::string Yrot = "yrotation";

	};

} // namespace mae

#endif // BVHCONTROLLER_HPP_
