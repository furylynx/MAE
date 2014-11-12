 // bone.i - SWIG interface

//custom includes
%include "e_bone.i"

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

%module(directors="1") w_bone
%{
	#include "../../../src/mae/bone.hpp"
%}

//shared_ptr

//templates
%template(bone_vector) std::vector<mae::bone>;   
 
// Parse the original header file
%include "../../../src/mae/bone.hpp"
