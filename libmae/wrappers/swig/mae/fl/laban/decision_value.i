// decision_value.i - SWIG interface
 
//custom includes

 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_decision_value
%{
	#include "../../../src/mae/fl/laban/decision_value.hpp"
%}

//shared_ptr

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/decision_value.hpp"
