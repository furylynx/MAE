// turn_symbol.i - SWIG interface

//custom includes
%include "i_symbol.i"
%include "i_degree_sign.i"
%include "i_dynamics_sign.i"
%include "e_turn_direction.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_turn_symbol
%{
	#include "../../../src/mae/fl/laban/mv/turn_symbol.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::i_degree_sign);
%shared_ptr(mae::fl::laban::mv::turn_symbol);

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/turn_symbol.hpp"

//templates
//...

