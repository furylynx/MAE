#ifndef MAE_MOS_HPP_
#define MAE_MOS_HPP_

//custom includes
//...

//global includes
#include <chrono>

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

			/**
			 * Returns the current system time in milliseconds. Thus, returns the number of milliseconds since the unix epoch.
			 *
			 * @return The milliseconds since the unix epoch.
			 */
			static uint64_t current_time_millis();
	};

} // namespace mae

#endif // MAE_MOS_HPP_
