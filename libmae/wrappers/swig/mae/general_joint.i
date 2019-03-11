//-- general_joint.i - SWIG interface

//-- custom includes
%include "math/vec3d.i"

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_general_joint
%{
	#include "../../../src/mae/general_joint.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_joint)
 
//-- Parse the original header file
%include "../../../src/mae/general_joint.hpp"
 
//-- templates
//...

