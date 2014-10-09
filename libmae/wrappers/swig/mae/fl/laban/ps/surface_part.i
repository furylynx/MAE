// surface_part.i - SWIG interface
 
//custom includes
%include "i_part.i"
%include "e_limb_side.i"
%include "i_limb.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_surface_part
%{
	#include "../../../src/mae/fl/laban/ps/surface_part.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_limb);
%shared_ptr(mae::fl::laban::ps::surface_part);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/surface_part.hpp"
