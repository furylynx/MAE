//-- default_limb.i - SWIG interface

//-- custom includes
%include "i_part.i"
%include "i_limb.i"
%include "e_limb.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_default_limb
%{
	#include "../../../src/mae/fl/laban/ps/default_limb.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_limb);
%shared_ptr(mae::fl::laban::ps::default_limb);

//-- cast method
%extend mae::fl::laban::ps::default_limb {
  static std::shared_ptr<mae::fl::laban::ps::default_limb > cast_to_default_limb(std::shared_ptr<mae::fl::laban::ps::i_part> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::ps::default_limb>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/default_limb.hpp"

//-- templates
//...
