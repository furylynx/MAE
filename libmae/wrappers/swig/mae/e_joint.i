 // e_joint.i - SWIG interface

//custom includes


//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


%module(directors="1") w_e_joint
%{
 	#include "../../../src/mae/e_joint.hpp"
%}
 
//shared_ptr
 
//templates
%template(int_vector) std::vector<int>;
//%template(e_bone_vector) std::vector<mae::e_joint>;
 
// Parse the original header file
%include "../../../src/mae/e_joint.hpp"