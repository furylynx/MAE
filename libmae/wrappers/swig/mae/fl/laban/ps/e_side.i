//-- e_side.i - SWIG interface

//-- custom includes
//...

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_e_side
%{
	#include "../../../src/mae/fl/laban/ps/e_side.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/e_side.hpp"

//-- templates
%template(IntVector) std::vector<int>;
%template(ESideVector) std::vector<mae::fl::laban::ps::e_side>;
