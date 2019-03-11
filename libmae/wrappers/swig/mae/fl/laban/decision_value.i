//-- decision_value.i - SWIG interface

//-- custom includes
//...

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_decision_value
%{
	#include "../../../src/mae/fl/laban/decision_value.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/decision_value.hpp"

//-- templates
//...
