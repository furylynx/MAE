//-- e_path_type.i - SWIG interface

//-- custom includes
//...

//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_e_path_type
%{
	#include "../../../src/mae/fl/laban/e_path_type.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/e_path_type.hpp"

//-- templates
%template (IntVector) std::vector<int>;
%template(EPathTypeVector) std::vector<mae::fl::laban::e_path_type>;
