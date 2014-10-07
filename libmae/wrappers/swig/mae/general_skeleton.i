// general_skeleton.i - SWIG interface
 
//custom includes
%include "bone.i"
%include "hierarchy.i"
%include "general_joint.i"
%include "basis.i"
%include "vec3d.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_general_skeleton
%{
	#include "../../../src/mae/general_skeleton.hpp"
%}

//shared_ptr
%shared_ptr(mae::bone);
%shared_ptr(mae::hierarchy);
%shared_ptr(mae::vec3d);

//templates

 
 // Parse the original header file
 %include "../../../src/mae/general_skeleton.hpp"
