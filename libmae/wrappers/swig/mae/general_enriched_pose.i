// general_enriched_pose.i - SWIG interface
 
%include "shared_ptr.i"
#include "std_unordered_map.i"
#include "exception.i"

#include "general_pose.i"

%template (pose_shared_ptr) shared_ptr<general_pose>;
%template (int_bool_map) unordered_map<int, bool>;
%template (int_int_map) unordered_map<int, int>;
 
 %module general_enriched_pose
 %{
 #include "../../../src/mae/general_enriched_pose.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/general_enriched_pose.hpp"
