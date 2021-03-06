//-- bone.i - SWIG interface

//-- custom includes
%include "e_bone.i"
%include "e_hand_bone.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- shared_ptr
%shared_ptr(mae::bone);

//-- module definition
%module(directors="1") w_bone
%{
	#include "../../../src/mae/bone.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::bone);

//-- Parse the original header file
%include "../../../src/mae/bone.hpp"

//-- templates
%template(BoneVector) std::vector<mae::bone>;

