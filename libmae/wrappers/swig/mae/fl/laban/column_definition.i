// column_definition.i - SWIG interface
 
//custom includes
%include "ps/i_pre_sign.i"


//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_column_definition
%{
	#include "../../../src/mae/fl/laban/column_definition.hpp"
%}

//shared_ptr
%shared_ptr(i_pre_sign);
%shared_ptr(column_definition);

//templates


// Parse the original header file
%include "../../../src/mae/fl/laban/column_definition.hpp"
