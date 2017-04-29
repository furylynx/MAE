/*
 * mos.hpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#ifndef MOS_HPP_
#define MOS_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#ifdef WIN32
	#include <conio.h>
#else // linux
    #include <cstdio>
	#include <unistd.h>
	#include <stdlib.h>
	#include <termios.h>
	#include <fcntl.h>
#endif // WIN32

namespace mae
{
	class mos
	{
		public:
			/**
			 * Returns the path separator char used on the current OS.
			 *
			 * @return The separator char.
			 */
			static char path_separator();

			/**
			 * Returns true if the keyboard was hit since the start of the program.
			 *
			 * @return True if keyboard was hit.
			 */
			static bool was_keyboard_hit();
	};

} // namespace mae

#endif // MOS_HPP_
