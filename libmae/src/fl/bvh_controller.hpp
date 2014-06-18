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
#include "../controller/mstr.hpp"

#include "math.hpp"
#include "bvh_spec.hpp"

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


namespace mae
{
	namespace fl
	{
		class bvh_controller
		{
			public:
				bvh_controller();
				virtual ~bvh_controller();

				virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data);
				virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data, double framerate);

				virtual std::string bvh_str(std::shared_ptr<general_skeleton> data);

				virtual void bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename);
				virtual void bvh_file(std::shared_ptr<general_skeleton> data, std::string filename);

				virtual std::pair<std::vector<std::shared_ptr<general_skeleton> >, double> read_bvh(std::string bvh_str, std::shared_ptr<bvh_spec> spec = std::shared_ptr<bvh_spec>());
				virtual std::pair<std::vector<std::shared_ptr<general_skeleton> >, double> read_bvh_file(std::string filename, std::shared_ptr<bvh_spec> spec = std::shared_ptr<bvh_spec>());

			private:
				std::shared_ptr<general_joint> parse_offset(std::string& value, unsigned int pos,
						std::shared_ptr<general_joint> parent_joint);
				std::vector<int> parse_channels(std::string& value, unsigned int pos);

				std::shared_ptr<hierarchy_element> generate_hierarchy_element(std::shared_ptr<bvh_spec> spec, int element_count, std::string element_name, bool is_dummy=false);

				const std::string Xpos = "xposition";
				const std::string Ypos = "yposition";
				const std::string Zpos = "zposition";
				const std::string Zrot = "zrotation";
				const std::string Xrot = "xrotation";
				const std::string Yrot = "yrotation";

		};

	} // namespace fl
} // namespace mae

#endif // BVHCONTROLLER_HPP_
