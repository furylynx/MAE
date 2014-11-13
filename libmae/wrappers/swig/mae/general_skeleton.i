// general_skeleton.i - SWIG interface
 
//custom includes
%include "bone.i"
%include "hierarchy.i"
%include "hierarchy_element.i"
%include "general_joint.i"
%include "math/basis.i"
%include "math/vec3d.i"
 
//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_general_skeleton
%{
	#include "../../../src/mae/general_skeleton.hpp"
%}

//shared_ptr
%shared_ptr(mae::bone);
%shared_ptr(mae::hierarchy);
%shared_ptr(mae::math::vec3d);
%shared_ptr(mae::math::basis);
%shared_ptr(mae::general_skeleton);

// Parse the original header file
%include "../../../src/mae/general_skeleton.hpp"

//templates
//...
