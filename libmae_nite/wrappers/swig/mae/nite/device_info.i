//-- device_info.i - SWIG interface

//-- custom includes
//...
 
//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_device_info
%{
	#include "../../../src/mae/nite/device_info.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::nite::device_info);

//-- Parse the original header file
%include "../../../src/mae/nite/device_info.hpp"

//-- templates
//...
