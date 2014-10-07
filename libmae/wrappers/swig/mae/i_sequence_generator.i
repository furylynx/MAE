// i_sequence_generator.i - SWIG interface
 
//custom includes
%include "bone.i"
%include "general_enriched_pose.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "std_list.i"
%include "exception.i"


%module w_i_sequence_generator
%{
	#include "../../../src/mae/i_sequence_generator.hpp"
%}

//shared_ptr
%shared_ptr(general_enriched_pose)
//TODO sequence template arg

//templates
%template (bone_vector) std::vector<bone>;
%template (enriched_pose_list) std::list<std::shared_ptr<general_enriched_pose> >;


// Parse the original header file
%include "../../../src/mae/i_sequence_generator.hpp"
