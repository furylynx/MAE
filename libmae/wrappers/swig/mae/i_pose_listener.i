//-- i_pose_listener.i - SWIG interface

//-- custom includes
%include "general_pose.i"

//-- global includes

%include "std_shared_ptr.i"
%include "exception.i"
%include "stdint.i"

//-- shared_ptr
%shared_ptr(mae::general_pose);


//-- module definition
%module(directors="1") w_i_pose_listener
%{
	#include "../../../src/mae/i_pose_listener.hpp"
%}

//-- Parse the original header file
%include "../../../src/mae/i_pose_listener.hpp"

//-- templates
//...
