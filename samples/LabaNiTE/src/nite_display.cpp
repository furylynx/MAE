/*
 * nite_display.cpp
 *
 *  Created on: 26.06.2014
 *      Author: keks
 */

#include "nite_display.hpp"

namespace lni
{

	unsigned int nite_display::ref_count_ = 0;
	bool nite_display::sdl_controller_ = false;

	nite_display::nite_display()
	{
		//Start up SDL and create window
		if (!init_sdl())
		{
			std::cout << "Failed to initialize!" << std::endl;
		}
		else
		{
			//Load media
			if (!load_media_sdl())
			{
				std::cout << "Failed to load media!" << std::endl;
			}
			else
			{
				//Apply the background image
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = (int) (g_background_->w * (double) SCREEN_WIDTH / 1920.0);
				bg_os.h = (int) (g_background_->h * (double) SCREEN_HEIGHT / 1080.0);

				SDL_BlitScaled(g_background_, NULL, g_screen_surface, &bg_os);
				//SDL_BlitSurface(g_background_, NULL, g_screen_surface, NULL);
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

		std::list<int> used_parts = pose->get_body_parts();

		//---
		//display pose
		//---

		//Apply the background image
		SDL_Rect bg_os;
		bg_os.x = 0;
		bg_os.y = 0;
		bg_os.w = (int) (g_background_->w * (double) SCREEN_WIDTH / 1920.0);
		bg_os.h = (int) (g_background_->h * (double) SCREEN_HEIGHT / 1080.0);

		SDL_BlitScaled(g_background_, NULL, g_screen_surface, &bg_os);
		//SDL_BlitSurface(g_background_, NULL, g_screen_surface, NULL);

		for (std::list<int>::iterator it = used_parts.begin(); it != used_parts.end(); it++)
		{
			unsigned int direction = pose->get_direction(*it);

			if (direction <= g_directions.size() && direction > 0)
			{
				SDL_Surface* g_dir = g_directions.at(direction - 1);

				//apply direction for all body parts
				//Make a temporary rectangle to hold the offsets
				SDL_Rect offset_scale;
				offset_scale.x = 0;
				offset_scale.y = 0;

				//Give the offsets to the rectangle

				if (*it == mae::e_bone_c::to_int(mae::e_bone::HEAD))
				{
					offset_scale.x = 930;
					offset_scale.y = 100;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_UPPER_ARM))
				{
					offset_scale.x = 400;
					offset_scale.y = 150;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_FOREARM))
				{
					offset_scale.x = 400;
					offset_scale.y = 400;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM))
				{
					offset_scale.x = 300;
					offset_scale.y = 275;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_UPPER_ARM))
				{
					offset_scale.x = 1520;
					offset_scale.y = 150;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_FOREARM))
				{
					offset_scale.x = 1520;
					offset_scale.y = 400;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_WHOLE_ARM))
				{
					offset_scale.x = 1620;
					offset_scale.y = 275;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_THIGH))
				{
					offset_scale.x = 700;
					offset_scale.y = 650;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_SHANK))
				{
					offset_scale.x = 700;
					offset_scale.y = 900;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_LEG))
				{
					offset_scale.x = 600;
					offset_scale.y = 775;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_THIGH))
				{
					offset_scale.x = 1220;
					offset_scale.y = 650;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_SHANK))
				{
					offset_scale.x = 1220;
					offset_scale.y = 900;
				}
				else if (*it == mae::e_bone_c::to_int(mae::e_bone::RIGHT_WHOLE_LEG))
				{
					offset_scale.x = 1320;
					offset_scale.y = 775;
				}

				//TODO do some scaling
				offset_scale.x = (int) (offset_scale.x * (double) SCREEN_WIDTH / 1920.0);
				offset_scale.y = (int) (offset_scale.y * (double) SCREEN_HEIGHT / 1080.0);

				offset_scale.w = (int) (g_dir->w * (double) SCREEN_WIDTH / 1920.0);
				offset_scale.h = (int) (g_dir->h * (double) SCREEN_HEIGHT / 1080.0);

				//Blit the surface
				//SDL_BlitSurface(g_dir, NULL, g_screen_surface, &offset);
				SDL_BlitScaled(g_dir, NULL, g_screen_surface, &offset_scale);
			}
			else
			{
				std::cout << "direction is unknown!!" << std::endl;
			}
		}

		SDL_UpdateWindowSurface(g_window_);
	}

	bool nite_display::init_sdl()
	{
		//Initialization flag
		bool success = true;

		if (!sdl_controller_)
		{
			try
			{
				sdl_controller_ = sdl_controller::initialize_sdl();
			} catch (std::exception &e)
			{
				std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
				success = false;
			}
		}

		if (sdl_controller_)
		{
			ref_count_++;
		}

		//Initialize SDL
//		if (SDL_Init( SDL_INIT_VIDEO) < 0)
//		{
//			std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//			success = false;
//		}
//		else
//		{
		//Create window
		g_window_ = SDL_CreateWindow("LabaNiTe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
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
//		}
		return success;

	}

	bool nite_display::load_media_sdl()
	{
		//Loading success flag
		bool success = true;

		//load background png image
		SDL_Surface* loadedSurface = IMG_Load("resources/background0.png");

		if (loadedSurface != NULL)
		{
			g_background_ = SDL_ConvertSurface(loadedSurface, g_screen_surface->format, NULL);
			if (g_background_ == NULL)
			{
				std::cout << "Unable to optimize image " << "resources/background0.png" << "! SDL Error: "
						<< SDL_GetError() << std::endl;
			}
			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
			loadedSurface = NULL;
		}

		if (g_background_ == NULL)
		{
			std::cout << "Unable to load image " << "resources/background0.png" << "! SDL Error: " << SDL_GetError()
					<< std::endl;
			success = false;
		}

		//load all other directions (33 images)
		std::vector<mae::fl::e_fl_direction> fl_dirs = mae::fl::e_fl_direction_c::vec();
		for (unsigned int i = 0; i < fl_dirs.size(); i++)
		{
			if (fl_dirs.at(i) == mae::fl::e_fl_direction::INVALID_FL_DIRECTION)
			{
				continue;
			}

			//load direction png image
			std::stringstream sstr;
			sstr << "resources/laban_direction" << mae::fl::e_fl_direction_c::to_int(fl_dirs.at(i)) << ".png";

			SDL_Surface* png_sur = IMG_Load(sstr.str().c_str());

			if (png_sur == NULL)
			{
				std::cout << "Unable to load image " << sstr.str() << "! SDL Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				SDL_Surface* sur = SDL_ConvertSurface(png_sur, g_screen_surface->format, NULL);
				if (sur == NULL)
				{
					std::cout << "Unable to optimize image " << sstr.str() << "! SDL Error: " << SDL_GetError()
							<< std::endl;
				}
				else
				{
					//add surface to list
					g_directions.push_back(sur);
				}

				//Get rid of old loaded surface
				SDL_FreeSurface(png_sur);
				png_sur = NULL;
			}
		}

		return success;
	}

	void nite_display::close_sdl()
	{
		//Deallocate surfaces
		SDL_FreeSurface(g_background_);
		g_background_ = NULL;

		for (unsigned int i = 0; i < g_directions.size(); i++)
		{
			SDL_FreeSurface(g_directions.at(i));
		}
		g_directions.clear();

		//Destroy window
		SDL_DestroyWindow(g_window_);
		g_window_ = NULL;

		//Quit SDL subsystems
		if (sdl_controller_)
		{
			ref_count_--;
		}

//		SDL_Quit();

		if (ref_count_ == 0)
		{
			sdl_controller::close_sdl();
		}
	}

} // namespace lni
