// fl_pose_detector.i - SWIG interface
 
//custom includes
%include "../bone.i"
%include "../i_pose_detector.i"

%include "fl_skeleton.i"
 
//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//pre-definitions for templates
%shared_ptr(mae::i_pose_detector<mae::fl::fl_skeleton>);
%template (fl_skeleton_pose_detector) mae::i_pose_detector<mae::fl::fl_skeleton>;

//module definition
%module(directors="1") w_fl_pose_detector
%{
	#include "../../../src/mae/fl/fl_pose_detector.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::fl_skeleton);
%shared_ptr(mae::general_pose);
%shared_ptr(mae::fl::fl_pose_detector);

// Parse the original header file
%include "../../../src/mae/fl/fl_pose_detector.hpp"

//templates
%template (bone_vector) std::vector<mae::bone>;



