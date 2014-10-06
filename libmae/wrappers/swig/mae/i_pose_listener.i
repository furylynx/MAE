// i_pose_listener.i - SWIG interface
 
%include "shared_ptr.i"
#include "exception.i"

#include "general_pose.i"
 
 %module i_pose_listener
 %{
 #include "../../../src/mae/i_pose_listener.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_pose_listener.hpp"
