// dynamic_sign.i - SWIG interface

//custom includes
%include "i_dynamics_sign.i"
%include "e_dynamic.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_dynamic_sign
%{
	#include "../../../src/mae/fl/laban/mv/dynamic_sign.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/dynamic_sign.hpp"
