//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "laban_visualizer"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../../src/mae/demo/fl/laban_visualizer.cpp"


BOOST_AUTO_TEST_CASE( paintsequence )
{

    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    mae::demo::fl::laban_visualizer lv(format);

    std::shared_ptr<mae::fl::laban::laban_sequence> sequence = std::make_shared<mae::fl::laban::laban_sequence>("TestSequence", "Tester", 1, mae::fl::laban::e_time_unit::MILLISECOND, 200, 5);

    int width = 200;
    int height = 100;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, (int)format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);

    //white background
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FillRect(surface, &rect, 0xFFFFFFFF);

    //print sequence to the surface
    lv.paint_sequence(surface, sequence, width, height);


    BOOST_CHECK_EQUAL(surface->w, width);
    BOOST_CHECK_EQUAL(surface->h, height);

    //free the surface
    SDL_FreeSurface(surface);
    surface = nullptr;
    SDL_FreeFormat(format);


}
