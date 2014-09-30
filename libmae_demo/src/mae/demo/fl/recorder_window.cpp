/*
 * recorder_window.cpp
 *
 *  Created on: 28.09.2014
 *      Author: keks
 */

#include "recorder_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			recorder_window::recorder_window(std::string title, std::string font_path,
					int width, int height, int x_pos, int y_pos, Uint32 flags) : sdl_window(title, width, height, x_pos, y_pos, flags)
			{

				font_str_ = font_path;
				background_ = nullptr;
				current_sequence_ = nullptr;
				countdown_ = -1;

				visualizer_ = std::shared_ptr<laban_visualizer>(
						new laban_visualizer(get_surface()->format));

				initialize();
			}

			recorder_window::~recorder_window()
			{
				cleanup();
			}

			void recorder_window::initialize()
			{
//				//load background png image
//				std::stringstream bg_sstr;
//				bg_sstr << resources_dir_;
//				bg_sstr << "background0.png";
//				SDL_Surface* loaded_surface = IMG_Load(bg_sstr.str().c_str());

				SDL_Surface* loaded_surface = IMG_LoadTyped_RW(SDL_RWFromConstMem(res::background0.data, res::background0.size), 0, "PNG");

				if (loaded_surface != nullptr)
				{
					background_ = SDL_ConvertSurface(loaded_surface, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(loaded_surface);
					loaded_surface = nullptr;

					if (background_ == nullptr)
					{
						std::stringstream e_sstr;
						e_sstr << "Unable to optimize image " << "! SDL Error: " << SDL_GetError()
								<< std::endl;
						throw std::runtime_error(e_sstr.str());
					}
				}
				else
				{
					std::stringstream e_sstr;
					e_sstr << "Unable to load image " << "! SDL Error: " << SDL_GetError()
							<< std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				small_font_ = TTF_OpenFont(font_str_.c_str(), 30);
				big_font_ = TTF_OpenFont(font_str_.c_str(), 45);

				if (small_font_ == nullptr || big_font_ == nullptr)
				{
					cleanup();

					std::stringstream e_sstr;
					e_sstr << "Unable to load font " << font_str_ << "! TTF Error: " << TTF_GetError() << std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				repaint();
			}

			void recorder_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}

				TTF_CloseFont(small_font_);
				TTF_CloseFont(big_font_);
			}

			void recorder_window::clear_paint()
			{
				current_sequence_ = nullptr;
				repaint();
			}

			void recorder_window::update_countdown(int time_left)
			{
				if (time_left < 0)
				{
					countdown_ = 0;
					clear_paint();
				}
				else
				{
					countdown_ = time_left;
					repaint();
				}

			}

			void recorder_window::paint(SDL_Surface* graphics)
			{
				//Apply the background image to the graphics
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = get_width();
				bg_os.h = get_height();

				if (background_ != nullptr)
				{
					SDL_BlitScaled(background_, NULL, graphics, &bg_os);
				}

				if (current_sequence_ != nullptr)
				{
					visualizer_->paint_sequence(graphics, current_sequence_, get_width(), get_height());

					//TODO print small countdown in one corner...
				}
				else
				{
					if (countdown_ >= 0)
					{
						//print the number in the mid
						std::stringstream sstr;
						sstr << countdown_ << " s";

						SDL_Surface* text = TTF_RenderText_Solid(big_font_, sstr.str().c_str(), text_color);

						SDL_Rect offset_scale;
						offset_scale.x = get_width()/2 - text->w/2;
						offset_scale.y = get_height()/2 - text->h/2;

						offset_scale.w = text->w;
						offset_scale.h = text->h;

						//SDL_BlitScaled(text, NULL, graphics, &offset_scale);
						SDL_BlitSurface(text, NULL, graphics, &offset_scale);
					}
					else
					{
						//print waiting for calibration or something
						SDL_Surface* text = TTF_RenderText_Solid(small_font_, wait_str, text_color);

						SDL_Rect offset_scale;
						offset_scale.x = get_width()/2 - text->w/2;
						offset_scale.y = get_height()/2 - text->h/2;

						offset_scale.w = text->w;
						offset_scale.h = text->h;

						SDL_BlitSurface(text, NULL, graphics, &offset_scale);
						//SDL_BlitScaled(text, NULL, graphics, &offset_scale);
						//SDL_BlitScaled(text, NULL, graphics, &bg_os);
					}
				}
			}

			void recorder_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void recorder_window::on_sequence(long timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
			{
				current_sequence_ = sequence;
				repaint();
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
