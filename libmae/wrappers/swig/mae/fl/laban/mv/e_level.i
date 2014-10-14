// e_level.i - SWIG interface
 
//custom includes
//%import "../../e_fl_direction.i"

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//forward declaration


//module definition
%module w_e_level
%{
	#include "../../../src/mae/fl/laban/mv/e_level.hpp"
%}

//shared_ptr

//templates
%template(int_vector) std::vector<int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_level.hpp"