// i_endpoint.i - SWIG interface
 
//custom includes
%include "i_part.i"

//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_i_endpoint
%{
	#include "../../../src/mae/fl/laban/ps/i_endpoint.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_endpoint);

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/i_endpoint.hpp"

//templates
//...

