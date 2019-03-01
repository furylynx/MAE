//-- accent_sign.i - SWIG interface

//-- custom includes
%include "i_dynamics_sign.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_accent_sign
%{
	#include "../../../src/mae/fl/laban/mv/accent_sign.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::accent_sign);

//-- cast method
%extend mae::fl::laban::mv::accent_sign {
  static std::shared_ptr<mae::fl::laban::mv::accent_sign > cast_to_accent_sign(std::shared_ptr<mae::fl::laban::mv::i_dynamics_sign> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::mv::accent_sign>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/accent_sign.hpp"

//-- templates
//...
