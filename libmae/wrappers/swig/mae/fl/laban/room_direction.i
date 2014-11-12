// room_direction.i - SWIG interface

//custom includes
%include "i_movement.i"
%include "mv/pin.i"


//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module(directors="1") w_room_direction
%{
	#include "../../../src/mae/fl/laban/room_direction.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::pin);
%shared_ptr(mae::fl::laban::room_direction);

//templates
%template (int_int_map) std::map<int, int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/room_direction.hpp"
