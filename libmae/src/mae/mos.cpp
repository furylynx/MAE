/*
 * mos.cpp
 *
 *  Created on: 19.09.2014
 */

#include "mos.hpp"

namespace mae
{

	char mos::path_separator()
	{
		#ifdef _WIN32
			return '\\';
		#else
			return '/';
		#endif
	}

	bool mos::was_keyboard_hit()
	{
		#ifdef WIN32
			return (int)_kbhit();
		#else // linux
			struct termios oldt, newt;
			int ch;
			int oldf;

			// don't echo and don't wait for ENTER
			tcgetattr(STDIN_FILENO, &oldt);
			newt = oldt;
			newt.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);
			oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

			// make it non-blocking (so we can check without waiting)
			if (0 != fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK))
			{
				return 0;
			}

			ch = std::getchar();

			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
			if (0 != fcntl(STDIN_FILENO, F_SETFL, oldf))
			{
				return 0;
			}

			if(ch != EOF)
			{
				ungetc(ch, stdin);
				return 1;
			}

			return 0;
		#endif // WIN32
	}

} // namespace mae
