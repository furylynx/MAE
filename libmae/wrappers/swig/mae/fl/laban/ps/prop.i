// prop.i - SWIG interface
 
//custom includes
$include "i_pre_sign.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_prop
%{
	#include "../../../src/mae/fl/laban/ps/prop.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::ps::i_pre_sign);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/prop.hpp"
