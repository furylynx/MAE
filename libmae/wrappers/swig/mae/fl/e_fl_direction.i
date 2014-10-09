// e_fl_direction.i - SWIG interface
 
//custom includes
//%import "laban/mv/e_direction.i"
//%import "laban/mv/e_level.i"

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_e_fl_direction
%{
	#include "../../../src/mae/fl/e_fl_direction.hpp"
%}

//shared_ptr

//templates
%template(int_vector) std::vector<int>;

// Parse the original header file
%include "../../../src/mae/fl/e_fl_direction.hpp"
