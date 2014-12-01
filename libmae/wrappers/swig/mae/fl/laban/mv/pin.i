//-- pin.i - SWIG interface

//-- custom includes
%include "i_degree_sign.i"
%include "e_level.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_pin
%{
	#include "../../../src/mae/fl/laban/mv/pin.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::i_degree_sign);
%shared_ptr(mae::fl::laban::mv::pin);

//-- cast method
%extend mae::fl::laban::mv::pin {
  static std::shared_ptr<mae::fl::laban::mv::pin> cast_to_pin(std::shared_ptr<mae::fl::laban::mv::i_degree_sign> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::mv::pin>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/pin.hpp"

//-- templates
//...
