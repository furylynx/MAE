//-- e_joint.i - SWIG interface

//-- custom includes
//...

//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_e_hand_joint
%{
 	#include "../../../src/mae/e_hand_joint.hpp"
%}

//-- shared_ptr
//...
  
//-- Parse the original header file
%include "../../../src/mae/e_hand_joint.hpp"
 
//-- templates
%template(IntVector) std::vector<int>;
%template(EHandJointVector) std::vector<mae::e_hand_joint>;
 
