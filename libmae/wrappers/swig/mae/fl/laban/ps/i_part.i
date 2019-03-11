//-- i_part.i - SWIG interface
 
//-- custom includes
//...

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_i_part
%{
	#include "../../../src/mae/fl/laban/ps/i_part.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/i_part.hpp"

//-- templates
//...
