// i_part.i - SWIG interface
 
//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_i_part
%{
	#include "../../../src/mae/fl/laban/ps/i_part.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/i_part.hpp"
