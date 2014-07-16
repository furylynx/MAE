/*
 * sequence_printer.hpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#ifndef SEQUENCE_PRINTER_HPP_
#define SEQUENCE_PRINTER_HPP_


//custom includes
#include "mae/i_sequence_listener.hpp"
#include "mae/fl/laban/laban_sequence.hpp"

//global includes
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace lni
{

	class sequence_printer : public mae::i_sequence_listener<mae::fl::laban::laban_sequence>
	{
		public:
			sequence_printer(unsigned int print_after_frames, std::string filename);
			virtual ~sequence_printer();

			virtual void on_sequence(long timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence);


		private:
			unsigned int print_after_frames_;
			unsigned int curr_frames_;
			unsigned int loops_;

			std::string filename_;
	};

} // namespace lni

#endif // SEQUENCE_PRINTER_HPP_
