//-- general_pose.i - SWIG interface
 
//-- custom includes
 
//-- global includes
//%include "stl.i"

%include "std_shared_ptr_fix.i"
%include "std_list.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_general_pose
%{
	#include "../../../src/mae/general_pose.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_pose);

//-- Parse the original header file
%include "../../../src/mae/general_pose.hpp"

//-- templates
%template (IntList) std::list<int>;


