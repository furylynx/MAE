// i_movement_detector.i - SWIG interface

//custom includes
%include "i_pose_listener.i"
%include "bone.i"
%include "general_pose.i"

//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"


%module w_i_movement_detector
%{
	#include "../../../src/mae/i_movement_detector.hpp"
%}

//shared_ptr
%shared_ptr(mae::i_pose_listener)
%shared_ptr(mae::general_pose)
//TODO shared_ptr to skeleton however template arg is...

//templates
%template(bone_vector) std::vector<mae::bone>;


// Parse the original header file
%include "../../../src/mae/i_movement_detector.hpp"
