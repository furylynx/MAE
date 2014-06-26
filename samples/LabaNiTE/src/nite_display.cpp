/*
 * nite_display.cpp
 *
 *  Created on: 26.06.2014
 *      Author: keks
 */

#include "nite_display.hpp"

namespace lni
{

	nite_display::nite_display()
	{
		//Start up SDL and create window
		if (!init_sdl())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Load media
			if (!load_media_sdl())
			{
				printf("Failed to load media!\n");
			}
			else
			{
				//Apply the image
				SDL_BlitSurface(g_background_, NULL, g_screen_surface, NULL);
			}

			//Update the surface
			SDL_UpdateWindowSurface(g_window_);

		}

	}

	nite_display::~nite_display()
	{
		//close the sdl stuff
		close_sdl();
	}

	void nite_display::on_pose(long timestamp, std::shared_ptr<mae::general_pose> pose)
	{
		//TODO handle stuff
		std::cout << "listened to a new pose!" << std::endl;

	}

	bool nite_display::init_sdl()
	{
		//Initialization flag
		bool success = true;
		//Initialize SDL
		if (SDL_Init( SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create window
			g_window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
					SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (g_window_ == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				g_screen_surface = SDL_GetWindowSurface(g_window_);
			}
		}
		return success;

	}

	bool nite_display::load_media_sdl()
	{
		//Loading success flag
		bool success = true;

		//loaf background png image
		SDL_Surface* loadedSurface = IMG_Load("resources/background0.png");

		if (loadedSurface != NULL)
		{
			g_background_ = SDL_ConvertSurface(loadedSurface, g_screen_surface->format, NULL);
			if (g_background_ == NULL)
			{
				printf("Unable to optimize image %s! SDL Error: %s\n", "resources/background0.png", SDL_GetError());
			}
			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		if (g_background_ == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "resources/background0.png",
					SDL_GetError());
			success = false;
		}

		return success;
	}

	void nite_display::close_sdl()
	{
		//Deallocate surface
		SDL_FreeSurface (g_background_);
		g_background_ = NULL;

		//Destroy window
		SDL_DestroyWindow(g_window_);
		g_window_ = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

} // namespace lni
