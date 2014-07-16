/*
 * sequence_printer.cpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#include "sequence_printer.hpp"

namespace lni
{

	sequence_printer::sequence_printer(unsigned int print_after_frames, std::string filename)
	{
		print_after_frames_ = print_after_frames;
		curr_frames_ = 0;
		loops_ = 0;

		filename_ = filename;
	}

	sequence_printer::~sequence_printer()
	{
	}

	void sequence_printer::on_sequence(long timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
	{
		curr_frames_++;

		if (curr_frames_ == print_after_frames_)
		{
			std::stringstream sstr;

			if (loops_ > 0)
			{
				sstr << loops_ << "-";
			}

			sstr << filename_;

			std::ofstream out_file(filename_);
			out_file << sequence->xml();
			out_file.close();

			curr_frames_ = 0;
			loops_ ++;
		}
	}


} // namespace lni
