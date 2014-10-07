// general_pose.i - SWIG interface
 
//custom includes
 
//global includes
%include "stl.i"
%include "std_shared_ptr.i"
%include "std_list.i"
%include "std_unordered_map.i"
%include "exception.i"


%module w_general_pose
%{
	#include "../../../src/mae/general_pose.hpp"
%}

//shared_ptr

//templates
%template (int_list) std::list<int>;
%template (int_int_double_map) std::unordered_map<int, unordered_map<int, double> >;
%template (int_int_map) std::unordered_map<int, int>;
 
 // Parse the original header file
 %include "../../../src/mae/general_pose.hpp"
