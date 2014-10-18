// fl_pose_detector.i - SWIG interface
 
//custom includes
%include "../bone.i"
%include "../i_pose_detector.i"

%include "fl_skeleton.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_fl_pose_detector
%{
	#include "../../../src/mae/fl/fl_pose_detector.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::fl_skeleton);
%shared_ptr(mae::general_pose)

//templates
%template (bone_vector) std::vector<mae::bone>;
%template (fl_skeleton_pose_detector) mae::i_pose_detector<mae::fl::fl_skeleton>;

// Parse the original header file
%include "../../../src/mae/fl/fl_pose_detector.hpp"
