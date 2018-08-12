//-- movement.i - SWIG interface

//-- custom includes
%include "i_movement.i"

%include "ps/i_pre_sign.i"
%include "mv/i_symbol.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_movement
%{
	#include "../../../src/mae/fl/laban/movement.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::ps::i_pre_sign);
%shared_ptr(mae::fl::laban::movement);

//-- cast method
%extend mae::fl::laban::movement {
  static std::shared_ptr<mae::fl::laban::movement> cast_to_movement(std::shared_ptr<mae::fl::laban::i_movement> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::movement>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/movement.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
