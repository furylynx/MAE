// general_pose.i - SWIG interface
 
//custom includes
 
//global includes
%include "stl.i"
%include "std_shared_ptr.i"
%include "std_list.i"
%include "exception.i"


%module(directors="1") w_general_pose
%{
	#include "../../../src/mae/general_pose.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_pose);

//templates
%template (int_list) std::list<int>;
 
 // Parse the original header file
 %include "../../../src/mae/general_pose.hpp"
