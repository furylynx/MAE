// i_movement.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module w_i_movement
%{
	#include "../../../src/mae/fl/laban/i_movement.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);

//templates
%template (int_int_map) std::map<int, int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/i_movement.hpp"
