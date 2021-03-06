/*
 * sequence_window.cpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#include "sequence_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			sequence_window::sequence_window(std::string title, bool backgroundimage, int width, int height,
					int x_pos, int y_pos, Uint32 flags)
					: sdl_window(title, width, height, x_pos, y_pos, flags)
			{
				background_ = nullptr;
				backgroundimage_ = backgroundimage;

				visualizer_ = std::shared_ptr<laban_visualizer>(new laban_visualizer(get_surface()->format));

				initialize();
			}

			sequence_window::~sequence_window()
			{
				cleanup();
			}

			void sequence_window::initialize()
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
						e_sstr << "Unable to optimize image "  << "! SDL Error: " << SDL_GetError()
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

				repaint();
			}

			void sequence_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}
			}

			void sequence_window::paint(SDL_Surface* graphics)
			{
				//Apply the background image to the graphics
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = get_width();
				bg_os.h = get_height();

				if (background_ != nullptr && backgroundimage_)
				{
					SDL_BlitScaled(background_, NULL, graphics, &bg_os);
				}
				else
				{
					SDL_FillRect(graphics, &bg_os, 0xFFFFFFFF);
				}

				if (current_sequence_ != nullptr)
				{
					visualizer_->paint_sequence(graphics, current_sequence_, get_width(), get_height());
				}
			}

			void sequence_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void sequence_window::on_sequence(uint64_t timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
			{
				current_sequence_ = sequence;
				repaint();
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
