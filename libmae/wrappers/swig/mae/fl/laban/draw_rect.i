//-- vec3d.i - SWIG interface

//-- custom includes

//-- global includes
%include "std_string.i"

//-- module definition
%module(directors="1") w_draw_rect
%{
	#include "../../../src/mae/fl/laban/draw_rect.hpp"
%}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/draw_rect.hpp"

//-- templates
//...


