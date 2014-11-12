// e_time_unit.i - SWIG interface
 
//custom includes
 
//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_time_unit
%{
	#include "../../../src/mae/fl/laban/e_time_unit.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/e_time_unit.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_time_unit_vector) std::vector<mae::fl::laban::e_time_unit>;


