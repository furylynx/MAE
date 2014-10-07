// general_joint.i - SWIG interface

//custom includes
%include "vec3d.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_general_joint
%{
	#include "../../../src/mae/general_joint.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_joint)
 
//templates

// Parse the original header file
%include "../../../src/mae/general_joint.hpp"
