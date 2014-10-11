/*
 * directions_handler.cpp
 *
 *  Created on: 12.10.2014
 *      Author: keks
 */

#include "directions_handler.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{
			namespace res
			{

				directions_handler::directions_handler(SDL_PixelFormat* format)
				{
					if (format == nullptr)
					{
						throw std::invalid_argument("Format must not be null.");
					}

					format_ = format;

					initialize();
				}

				directions_handler::~directions_handler()
				{
				}

				SDL_Surface* directions_handler::get_direction_image(unsigned int direction)
				{
					if (direction > 0 && direction < directions_.size())
					{
						return directions_.at(direction);
					}
					else
					{
						throw std::invalid_argument("The given direction is unknown to this handler.");
					}
				}

				SDL_Surface* directions_handler::get_direction_image(mae::fl::e_fl_direction direction)
				{
					return get_direction_image(mae::fl::e_fl_direction_c::to_int(direction));
				}

				unsigned int directions_handler::size()
				{
					return directions_.size();
				}

				void directions_handler::initialize()
				{
					//Loading success flag
					bool success = true;

					//load all other directions (33 images)
					std::vector<mae::fl::e_fl_direction> fl_dirs = mae::fl::e_fl_direction_c::vec();
					for (unsigned int i = 0; i < fl_dirs.size(); i++)
					{
						if (fl_dirs.at(i) == mae::fl::e_fl_direction::INVALID_FL_DIRECTION)
						{
							directions_.push_back(nullptr);
							continue;
						}

						if (i >= res::laban_res_size)
						{
							//nothing to do...
							break;
						}

						SDL_Surface* png_sur = IMG_LoadTyped_RW(SDL_RWFromConstMem(res::laban_res[i-1].data, res::laban_res[i-1].size), 0, "PNG");

						if (png_sur == nullptr)
						{
							//failed to load, therefore break, do cleanup and throw exception
							success = false;
							break;
						}
						else
						{
							SDL_Surface* sur = SDL_ConvertSurface(png_sur, format_, 0);

							//Get rid of old loaded surface
							SDL_FreeSurface(png_sur);
							png_sur = nullptr;

							if (sur == nullptr)
							{
								//failed to load, therefore break, do cleanup and throw exception
								success = false;
								break;
							}
							else
							{
								//add surface to list
								directions_.push_back(sur);
							}
						}
					}

					if (!success)
					{
						cleanup();
						std::stringstream e_sstr;
						e_sstr << "Could not load the resources. " << std::endl;

						throw std::runtime_error(e_sstr.str());
					}
				}

				void directions_handler::cleanup()
				{
					for (unsigned int i = 0; i < directions_.size(); i++)
					{
						if (directions_.at(i) != nullptr)
						{
							SDL_FreeSurface(directions_.at(i));
						}
					}

					directions_.clear();
				}

			} // namespace res
		} // namespace fl
	} // namespace demo
} // namespace mae
