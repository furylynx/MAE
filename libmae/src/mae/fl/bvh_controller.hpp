#ifndef MAE_FL_BVHCONTROLLER_HPP_
#define MAE_FL_BVHCONTROLLER_HPP_

//custom includes
#include "../general_skeleton.hpp"
#include "../mstr.hpp"

#include "bvh_spec.hpp"
#include "bvh_data.hpp"

#include "../math/math.hpp"

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
#include <list>


namespace mae
{
	namespace fl
	{
		class bvh_controller
		{
			public:
				/**
				 * Creates a new BVH controller which is used to read and/or write BVH files.
				 */
				bvh_controller();
				virtual ~bvh_controller();

				/**
				 * Generates a BVH string from the skeleton data. The string contains the content
				 * which can be written to a BVH file. Assumes the frame rate to be 30 fps.
				 *
				 * @param data The skeleton data.
				 * @return The BVH string.
				 */
				virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data);

				/**
				 * Generates a BVH string from the skeleton data. The string contains the content
				 * which can be written to a BVH file.
				 *
				 * @param data The skeleton data.
				 * @param framerate The frame rate
				 * @return The BVH string.
				 */
				virtual std::string bvh_str(std::vector<std::shared_ptr<general_skeleton> > data, double framerate);

				/**
				 * Generates a BVH string from the one skeleton. The string contains the content
				 * which can be written to a BVH file. Sets the frame rate to 30 fps (which doesn't
				 * matter since one skeleton does not provide any motion).
				 *
				 * @param data The skeleton.
				 * @return The BVH string.
				 */
				virtual std::string bvh_str(std::shared_ptr<general_skeleton> data);

				/**
				 * Prints the BVH file for the skeleton data. Assumes the frame rate to be 30 fps.
				 *
				 * @param data The skeleton data.
				 * @param filename The file name.
				 */
				virtual void print_bvh_file(std::vector<std::shared_ptr<general_skeleton> > data, std::string filename);

				/**
				 * Prints the BVH file from the one skeleton. Sets the frame rate to 30 fps (which doesn't
				 * matter since one skeleton does not provide any motion).
				 *
				 * @param data The skeleton.
				 * @param filename The file name.
				 */
				virtual void print_bvh_file(std::shared_ptr<general_skeleton> data, std::string filename);

				/**
				 * Reads the BVH string which is a string containing the content of a potential bvh file.
				 * Uses a specification to define the IDs of the joints as well as the right-left and
				 * top-down directions..
				 *
				 * @param bvh_str The BVH string.
				 * @param spec The specification for the reader.
				 * @return The bvh data.
				 */
				virtual std::shared_ptr<bvh_data> read_bvh_str(std::string bvh_str, std::shared_ptr<bvh_spec> spec);

				/**
				 * Reads the BVH file. Uses a specification to define the IDs of the joints as well as the
				 * right-left and top-down directions.
				 *
				 * @param filename The BVH file name
				 * @param spec The specification for the reader.
				 * @return The bvh data.
				 */
				virtual std::shared_ptr<bvh_data> read_bvh_file(std::string filename, std::shared_ptr<bvh_spec> spec);

			private:
				/**
				 * Parses the offset values from the BVH string.
				 *
				 * @param value The BVH string.
				 * @param pos The position in the string.
				 * @param parent_joint The parent joint.
				 * @return The joint.
				 */
				std::shared_ptr<general_joint> parse_offset(std::string& value, unsigned int pos,
						std::shared_ptr<general_joint> parent_joint);

				/**
				 * Parses the channel information.
				 *
				 * @param value The BVH string.
				 * @param pos The position in the string
				 * @return The channel information.
				 */
				std::vector<int> parse_channels(std::string& value, unsigned int pos);

				/**
				 * Generates the hierarchy element.
				 *
				 * @param spec The specification
				 * @param element_count The element ID.
				 * @param element_name The name of the element.
				 * @param is_dummy True if the element is meant to be a dummy value.
				 * @return The hierarchy element.
				 */
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

#endif // MAE_FL_BVHCONTROLLER_HPP_
