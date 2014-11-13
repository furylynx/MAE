 // movement_controller.i - SWIG interface

//custom includes
%include "bone.i"
%include "i_sequence_listener.i"
%include "i_recognition_listener.i"
%include "i_pose_listener.i"

%include "i_movement_detector.i"
%include "i_sequence_recognizer.i"
%include "i_pose_detector.i"
%include "i_sequence_generator.i"


//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"


%module(directors="1") w_movement_controller
%{
	#include "../../../src/mae/movement_controller.hpp"
%}

//shared_ptr
%shared_ptr(mae::i_pose_listener)

// Parse the original header file
%include "../../../src/mae/movement_controller.hpp"

//templates
%template (bone_vector) std::vector<mae::bone>;

