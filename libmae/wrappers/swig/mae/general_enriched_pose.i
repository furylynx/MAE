// general_enriched_pose.i - SWIG interface
 
 
//custom includes
%include "general_pose.i"
 
//global includes
%include "stl.i"
%include "std_shared_ptr.i"
%include "std_unordered_map.i"
%include "exception.i"



%module w_general_enriched_pose
%{
	#include "../../../src/mae/general_enriched_pose.hpp"
%}
 
//shared_ptr
%shared_ptr(general_pose)
 
//templates
%template (int_bool_map) std::unordered_map<int, bool>;
%template (int_int_map) std::unordered_map<int, int>;
 
// Parse the original header file
%include "../../../src/mae/general_enriched_pose.hpp"
