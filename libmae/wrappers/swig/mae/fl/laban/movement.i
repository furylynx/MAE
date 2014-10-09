// movement.i - SWIG interface

//custom includes
%include "i_movement.i"

%include "ps/i_pre_sign.i"
%include "mv/i_symbol.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module w_movement
%{
	#include "../../../src/mae/fl/laban/movement.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::ps::i_pre_sign);

//templates
%template (int_int_map) std::map<int, int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/movement.hpp"
