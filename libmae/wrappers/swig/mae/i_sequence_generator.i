//-- i_sequence_generator.i - SWIG interface

//-- custom includes
%include "bone.i"
%include "general_enriched_pose.i"

//-- global includes
//%include "stl.i"
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_vector.i"
%include <std_list.i>
%include "exception.i"

//-- module definition
%module(directors="1") w_i_sequence_generator
%{
	#include "../../../src/mae/i_sequence_generator.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_enriched_pose)

//-- Parse the original header file
%include "../../../src/mae/i_sequence_generator.hpp"

//-- templates
%template (BoneVector) std::vector<mae::bone>;
%template (EnrichedPoseList) std::list<std::shared_ptr<mae::general_enriched_pose> >;
