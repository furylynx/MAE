 // e_bone.i - SWIG interface

//custom includes
%template(vector_e_bone) vector<e_bone>;

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "except.i"


%module w_e_bone
%{
 	#include "../../../src/mae/e_bone.hpp"
%}
 
//shared_ptr
 
//templates
%template(e_bone_vector) std::vector<e_bone>;
 
// Parse the original header file
%include "../../../src/mae/e_bone.hpp"