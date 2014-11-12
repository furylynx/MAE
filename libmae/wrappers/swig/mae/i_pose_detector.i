// i_pose_detector.i - SWIG interface
 
//custom includes
%include "general_pose.i"
%include "bone.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"

 
%module(directors="1") w_i_pose_detector
%{
	#include "../../../src/mae/i_pose_detector.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_pose)
%shared_ptr(mae::i_pose_detector<mae::general_skeleton>);
%shared_ptr(mae::i_pose_detector<mae::fl::fl_skeleton>);

// Parse the original header file
%include "../../../src/mae/i_pose_detector.hpp"

//templates
%template (bone_vector) std::vector<mae::bone>;
%template (general_skeleton_pose_detector) mae::i_pose_detector<mae::general_skeleton>;
%template (fl_skeleton_pose_detector) mae::i_pose_detector<mae::fl::fl_skeleton>;
