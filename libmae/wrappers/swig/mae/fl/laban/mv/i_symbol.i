// i_symbol.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_i_symbol
%{
	#include "../../../src/mae/fl/laban/mv/i_symbol.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/i_symbol.hpp"
