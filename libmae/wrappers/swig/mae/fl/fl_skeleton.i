// fl_skeleton.i - SWIG interface
 
//custom includes
%include "../general_skeleton.i"
%include "../basis.i"

 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_fl_skeleton
%{
	#include "../../../src/mae/fl/fl_skeleton.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::basis);

//templates

// Parse the original header file
%include "../../../src/mae/fl/fl_skeleton.hpp"
