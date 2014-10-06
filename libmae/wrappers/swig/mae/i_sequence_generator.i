// i_sequence_generator.i - SWIG interface
 
%include "shared_ptr.i"
%include "std_vector.i"
%include "std_list.i"
#include "exception.i"

#include "bone.i"
#include "general_enriched_pose.i"

%template (bone_vector) vector<bone>;
%template (enriched_pose_list) list<shared_ptr<general_enriched_pose> >;

 
 %module i_sequence_generator
 %{
 #include "../../../src/mae/i_sequence_generator.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_sequence_generator.hpp"
