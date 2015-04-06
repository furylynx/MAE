/*
 * plain_data_controller.hpp
 *
 *  Created on: 04.04.2015
 *      Author: keks
 */

#ifndef PLAIN_DATA_CONTROLLER_HPP_
#define PLAIN_DATA_CONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../general_skeleton.hpp"
#include "../mstr.hpp"

#include "msr_data.hpp"
#include "msr_spec.hpp"

//global includes
#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>

namespace mae
{
	namespace fl
	{

		class msr_data_controller
		{
			public:
				/**
				 * Creates a new MSR data controller which is used to read and/or write MSR data files.
				 */
				msr_data_controller();
				virtual ~msr_data_controller();

				/**
				 * Reads the MSR data file. Uses a specification to define the IDs of the joints.
				 *
				 * @param filename The MSR data file name.
				 * @param spec The MSR data specification.
				 *
				 * @return The MSR data.
				 */
				virtual std::shared_ptr<msr_data> read_msr_file(std::string filename, std::shared_ptr<msr_spec> spec) const;

				/**
				 * Reads a specific part of the MSR data file (e.g., a gesture). Uses a specification to
				 * define the IDs of the joints.
				 *
				 * @param filename The MSR data file name.
				 * @param spec The MSR data specification.
				 * @param begin_frame The first frame of the sequence.
				 * @param end_frame The last frame of the sequence.
				 *
				 * @return The MSR data.
				 */
				virtual std::shared_ptr<msr_data> read_msr_file(std::string filename, std::shared_ptr<msr_spec> spec, unsigned int begin_frame, unsigned int end_frame) const;

				/**
				 * Reads the MSR data string. Uses a specification to define the IDs of the joints.
				 *
				 * @param filename The MSR data file name.
				 * @param spec The MSR data specification.
				 *
				 * @return The MSR data.
				 */
				virtual std::shared_ptr<msr_data> read_msr_str(std::string msr_str, std::shared_ptr<msr_spec> spec) const;

				/**
				 * Reads a specific part of the MSR data string (e.g., a gesture). Uses a specification to
				 * define the IDs of the joints.
				 *
				 * @param filename The MSR data file name.
				 * @param spec The MSR data specification.
				 * @param begin_frame The first frame of the sequence.
				 * @param end_frame The last frame of the sequence.
				 *
				 * @return The MSR data.
				 */
				virtual std::shared_ptr<msr_data> read_msr_str(std::string msr_str, std::shared_ptr<msr_spec> spec, unsigned int begin_frame, unsigned int end_frame) const;


				/**
 				 * Generates a MSR data string from the skeleton data. The string contains the content
				 * which can be written to a MSR data file.
				 *
				 * @param data The skeleton data.
				 *
				 * @return The MSR data string.
				 */
				virtual std::string msr_str(std::vector<std::shared_ptr<general_skeleton> > data) const;

				/**
 				 * Generates a MSR data string from the skeleton data. The string contains the content
				 * which can be written to a MSR data file.
				 *
				 * @param data The skeleton data.
				 *
				 * @return The MSR data string.
				 */
				virtual std::string msr_str(std::shared_ptr<general_skeleton> data) const;

				/**
				 * Prints the MSR data file for the skeleton data.
				 *
				 * @param filename The MSR data file name.
				 * @param data The skeleton data.
				 */
				virtual void print_msr_file(std::string filename, std::vector<std::shared_ptr<general_skeleton> > data) const;

				/**
				 * Prints the MSR data file for the skeleton data.
				 *
				 * @param filename The MSR data file name.
				 * @param data The skeleton data.
				 */
				virtual void print_msr_file(std::string filename, std::shared_ptr<general_skeleton> data) const;


			private:
				std::vector<std::shared_ptr<general_skeleton> > handle_frames(std::basic_istream<char>& stream, std::size_t amount_frames, std::size_t* line_count, bool create_skeleton_data = true) const;

		};

	} // namespace fl
} // namespace mae

#endif // PLAIN_DATA_CONTROLLER_HPP_
