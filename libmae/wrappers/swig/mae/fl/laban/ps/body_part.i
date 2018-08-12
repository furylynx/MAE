//-- body_part.i - SWIG interface

//-- custom includes
%include "i_pre_sign.i"
%include "e_side.i"
%include "i_part.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_body_part
%{
	#include "../../../src/mae/fl/laban/ps/body_part.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_pre_sign);
%shared_ptr(mae::fl::laban::ps::body_part);

//-- cast method
%extend mae::fl::laban::ps::body_part {
  static std::shared_ptr<mae::fl::laban::ps::body_part > cast_to_body_part(std::shared_ptr<mae::fl::laban::ps::i_pre_sign> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::ps::body_part>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/body_part.hpp"

//-- templates
//...
