//-- i_movement.i - SWIG interface

//-- custom includes
%include "draw_laban_rect.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"
// std::type_index
%include "std_type_index.i"

//-- module definition
%module(directors="1") w_i_movement
%{
	#include "../../../src/mae/fl/laban/i_movement.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::i_movement);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/i_movement.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
%template (DoubleVector) std::vector<double>;
//%template (TypeIndexVector) std::vector<std::type_index>;

