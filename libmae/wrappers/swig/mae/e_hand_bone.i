//-- e_bone.i - SWIG interface

//-- custom includes
//...

//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_e_hand_bone
%{
 	#include "../../../src/mae/e_hand_bone.hpp"
%}
 
//-- shared_ptr
//...
  
//-- Parse the original header file
%include "../../../src/mae/e_hand_bone.hpp"
 
//-- templates
%template(IntVector) std::vector<int>;
%template(EHandBoneVector) std::vector<mae::e_hand_bone>;

