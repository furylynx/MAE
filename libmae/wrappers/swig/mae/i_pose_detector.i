// i_pose_detector.i - SWIG interface
 
//custom includes
%include "general_pose.i"
%include "bone.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"

 
%module w_i_pose_detector
%{
	#include "../../../src/mae/i_pose_detector.hpp"
%}
 
//shared_ptr
%shared_ptr(mae::general_pose)
//TODO shared_ptr skeleton template

//templates
%template (bone_vector) std::vector<mae::bone>;

// Parse the original header file
%include "../../../src/mae/i_pose_detector.hpp"
