// e_turn_direction.i - SWIG interface
 
//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_e_turn_direction
%{
	#include "../../../src/mae/fl/laban/mv/e_turn_direction.hpp"
%}

//shared_ptr

//templates
%template(int_vector) std::vector<int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_turn_direction.hpp"
