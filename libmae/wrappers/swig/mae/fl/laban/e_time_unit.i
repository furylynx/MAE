// e_time_unit.i - SWIG interface
 
//custom includes
 
//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_e_time_unit
%{
	#include "../../../src/mae/fl/laban/e_time_unit.hpp"
%}

//shared_ptr

//templates
%template(int_vector) std::vector<int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/e_time_unit.hpp"
