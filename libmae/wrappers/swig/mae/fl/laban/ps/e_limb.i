// e_limb.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_limb
%{
	#include "../../../src/mae/fl/laban/ps/e_limb.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/e_limb.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_limb_vector) std::vector<mae::fl::laban::ps::e_limb>;

