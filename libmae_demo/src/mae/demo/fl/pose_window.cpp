/*
 * pose_window.cpp
 *
 *  Created on: 12.10.2014
 *      Author: keks
 */

#include "pose_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			pose_window::pose_window(std::string title, bool backgroundimage, int width, int height, int x_pos, int y_pos, Uint32 flags)
					: sdl_window(title, width, height, x_pos, y_pos, flags)
			{
				backgroundimage_ = backgroundimage;

				directions_handler_ = std::shared_ptr<res::directions_handler>(
						new res::directions_handler(get_surface()->format));

				initialize();
			}

			pose_window::~pose_window()
			{
				// TODO Auto-generated destructor stub
			}

			void pose_window::initialize()
			{
				//load background png image
				SDL_Surface* loaded_surface = IMG_LoadTyped_RW(
						SDL_RWFromConstMem(res::background0.data, res::background0.size), 0, "PNG");

				if (loaded_surface != nullptr)
				{
					background_ = SDL_ConvertSurface(loaded_surface, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(loaded_surface);
					loaded_surface = nullptr;

					if (background_ == nullptr)
					{
						std::stringstream e_sstr;
						e_sstr << "Unable to optimize image " << "! SDL Error: " << SDL_GetError() << std::endl;
						throw std::runtime_error(e_sstr.str());
					}
				}
				else
				{
					std::stringstream e_sstr;
					e_sstr << "Unable to load image " << "! SDL Error: " << SDL_GetError() << std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				repaint();
			}

			void pose_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}
			}

			void pose_window::paint(SDL_Surface* graphics)
			{
				//Apply the background image to the graphics
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = (int) (background_->w * (double) get_width() / 1920.0);
				bg_os.h = (int) (background_->h * (double) get_height() / 1080.0);

				if (background_ != nullptr && backgroundimage_)
				{
					SDL_BlitScaled(background_, NULL, graphics, &bg_os);
				}
				else
				{
					SDL_FillRect(graphics, &bg_os, 0xFFFFFFFF);
				}

				if (current_pose_ != nullptr)
				{
					//paint the pose
					std::list<int> used_parts = current_pose_->get_body_parts();

					for (std::list<int>::iterator it = used_parts.begin(); it != used_parts.end(); it++)
					{
						unsigned int direction = current_pose_->get_direction(*it);

						if (direction < directions_handler_->size() && direction > 0)
						{
							SDL_Surface* g_dir = directions_handler_->get_direction_image(direction);

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

							//do some scaling
							offset_scale.x = (int) (offset_scale.x * (double) get_width() / 1920.0);
							offset_scale.y = (int) (offset_scale.y * (double) get_height() / 1080.0);

							offset_scale.w = (int) (g_dir->w * (double) get_width() / 1920.0);
							offset_scale.h = (int) (g_dir->h * (double) get_height() / 1080.0);

							//Blit the surface
							SDL_BlitScaled(g_dir, NULL, graphics, &offset_scale);
						}
						else
						{
							std::cout << "direction is unknown!!" << std::endl;
						}
					}
				}

			}

			void pose_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void pose_window::on_pose(long timestamp, std::shared_ptr<general_pose> pose)
			{
				current_pose_ = pose;

				repaint();
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
