// i_movement_detector.i - SWIG interface
 
%include "shared_ptr.i"
#include "std_vector.i"
#include "exception.i"

#include "i_pose_listener.i"
#include "bone.i"
 
 %module i_movement_detector
 %{
 #include "../../../src/mae/i_movement_detector.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_movement_detector.hpp"
