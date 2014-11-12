// e_dynamic.i - SWIG interface
 
//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_dynamic
%{
	#include "../../../src/mae/fl/laban/mv/e_dynamic.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_dynamic.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_dynamic_vector) std::vector<mae::fl::laban::mv::e_dynamic>;
