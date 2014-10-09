// i_limb.i - SWIG interface
 
//custom includes
$include "i_part.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_i_limb
%{
	#include "../../../src/mae/fl/laban/ps/i_limb.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_limb);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/i_limb.hpp"
