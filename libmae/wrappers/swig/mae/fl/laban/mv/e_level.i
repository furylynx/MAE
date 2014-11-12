// e_level.i - SWIG interface
 
//custom includes
//%import "../../e_fl_direction.i"

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//forward declaration


//module definition
%module(directors="1") w_e_level
%{
	#include "../../../src/mae/fl/laban/mv/e_level.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_level.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_level_vector) std::vector<mae::fl::laban::mv::e_level>;
