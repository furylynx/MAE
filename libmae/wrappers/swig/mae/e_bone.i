 // e_bone.i - SWIG interface

%include "std_string.i"
%include "std_vector.i"
%include "except.i"

%template(vector_e_bone) vector<e_bone>;

%module e_bone
%{
 	#include "../../../src/mae/e_bone.hpp"
%}
 
// Parse the original header file
%include "../../../src/mae/e_bone.hpp"