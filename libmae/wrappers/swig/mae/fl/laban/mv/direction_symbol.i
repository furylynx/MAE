//-- direction_symbol.i - SWIG interface

//-- custom includes
%include "i_symbol.i"
%include "i_dynamics_sign.i"
%include "pin.i"
%include "space_measurement.i"
%include "e_level.i"
%include "e_direction.i"
%include "e_contact_hook.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_direction_symbol
%{
	#include "../../../src/mae/fl/laban/mv/direction_symbol.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::mv::space_measurement);
%shared_ptr(mae::fl::laban::mv::pin);
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::direction_symbol);

//-- cast method
%extend mae::fl::laban::mv::direction_symbol {
  static std::shared_ptr<mae::fl::laban::mv::direction_symbol > cast_to_direction_symbol(std::shared_ptr<mae::fl::laban::mv::i_symbol> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::mv::direction_symbol>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/direction_symbol.hpp"

//-- templates
//...
