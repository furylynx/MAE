// e_limb_side.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_limb_side
%{
	#include "../../../src/mae/fl/laban/ps/e_limb_side.hpp"
%}

//shared_ptr

//templates
%template(int_vector) std::vector<int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/e_limb_side.hpp"
