// i_pose_detector.i - SWIG interface
 
%include "shared_ptr.i"
%include "std_vector.i"
#include "exception.i"

#include "general_pose.i"
#include "bone.i"

%template (bone_vector) vector<bone>;
%template (general_pose_vector) shared_ptr<general_pose>;
 
 %module i_pose_detector
 %{
 #include "../../../src/mae/i_pose_detector.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_pose_detector.hpp"
