// space_symbol.i - SWIG interface

//custom includes
%include "i_symbol.i"
%include "space_measurement.i"
%include "i_dynamics_sign.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_space_symbol
%{
	#include "../../../src/mae/fl/laban/mv/space_symbol.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::mv::space_measurement);
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::space_symbol);

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/space_symbol.hpp"

//templates
//...

