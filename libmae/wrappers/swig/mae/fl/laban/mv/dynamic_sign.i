//-- dynamic_sign.i - SWIG interface

//-- custom includes
%include "i_dynamics_sign.i"
%include "e_dynamic.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_dynamic_sign
%{
	#include "../../../src/mae/fl/laban/mv/dynamic_sign.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::mv::dynamic_sign);

//-- cast method
%extend mae::fl::laban::mv::dynamic_sign {
  static std::shared_ptr<mae::fl::laban::mv::dynamic_sign> cast_to_dynamic_sign(std::shared_ptr<mae::fl::laban::mv::i_dynamics_sign> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::mv::dynamic_sign>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/dynamic_sign.hpp"

//-- templates
//...
