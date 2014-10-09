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
%module w_path
%{
	#include "../../../src/mae/fl/laban/path.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);

//templates
%template (int_int_map) std::map<int, int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/path.hpp"
