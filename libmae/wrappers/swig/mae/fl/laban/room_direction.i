//-- room_direction.i - SWIG interface

//-- custom includes
%include "i_movement.i"
%include "mv/pin.i"


//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_room_direction
%{
	#include "../../../src/mae/fl/laban/room_direction.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::pin);
%shared_ptr(mae::fl::laban::room_direction);

//-- cast method
%extend mae::fl::laban::room_direction {
  static std::shared_ptr<mae::fl::laban::room_direction> cast_to_room_direction(std::shared_ptr<mae::fl::laban::i_movement> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::room_direction>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/room_direction.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
