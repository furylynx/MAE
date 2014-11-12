 // e_bone.i - SWIG interface

//custom includes


//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


%module(directors="1") w_e_bone
%{
 	#include "../../../src/mae/e_bone.hpp"
%}
 
//shared_ptr
//...
  
// Parse the original header file
%include "../../../src/mae/e_bone.hpp"
 
//templates
%template(int_vector) std::vector<int>;
%template(e_bone_vector) std::vector<mae::e_bone>;

//rename
//%rename (EBone) e_bone;
 
