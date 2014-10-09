// i_degree_sign.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_i_degree_sign
%{
	#include "../../../src/mae/fl/laban/mv/i_degree_sign.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_degree_sign);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/i_degree_sign.hpp"
