// vibration_symbol.i - SWIG interface

//custom includes
%include "i_symbol.i"
%include "pin.i"
%include "i_dynamics_sign.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_vibration_symbol
%{
	#include "../../../src/mae/fl/laban/mv/vibration_symbol.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::mv::pin);
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::vibration_symbol);

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/vibration_symbol.hpp"

//templates
//...

