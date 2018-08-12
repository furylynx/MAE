//-- mos.i - SWIG interface

//-- custom includes
//...

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_mos
%{
	#include "../../../src/mae/mos.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/mos.hpp"

//-- templates
//...
