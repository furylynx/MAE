 // movement_controller.i - SWIG interface

%include "shared_ptr.i"
%include "std_vector.i"
%include "except.i"

%include "bone.i"
%include "i_sequence_listener.i"
%include "i_recognition_listener.i"
%include "i_pose_listener.i"

%include "i_movement_detector.i"
%include "i_sequence_recognizer.i"
%include "i_pose_detector.i"
%include "i_sequence_generator.i"

%module movement_controller
%{
	#include "../../../src/mae/movement_controller.hpp"
%}     
 
// Parse the original header file
%include "../../../src/mae/movement_controller.hpp"