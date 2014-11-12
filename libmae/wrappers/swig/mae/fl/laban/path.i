// path.i - SWIG interface

//custom includes
%include "i_movement.i"

%include "e_path_type.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module(directors="1") w_path
%{
	#include "../../../src/mae/fl/laban/path.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::path);

// Parse the original header file
%include "../../../src/mae/fl/laban/path.hpp"

//templates
%template (int_int_map) std::map<int, int>;


