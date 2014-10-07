// i_pre_sign.i - SWIG interface
 
//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_i_pre_sign
%{
	#include "../../../src/mae/fl/laban/ps/i_pre_sign.hpp"
%}

//shared_ptr
%shared_ptr(i_pre_sign);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/i_pre_sign.hpp"
