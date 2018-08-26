//-- vec3d.i - SWIG interface

//-- custom includes

//-- global includes
%include "std_string.i"

//-- module definition
%module(directors="1") w_svg_style
%{
	#include "../../../src/mae/fl/laban/svg_style.hpp"
%}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/svg_style.hpp"

//-- templates
//...


