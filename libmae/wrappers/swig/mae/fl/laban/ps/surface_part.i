//-- surface_part.i - SWIG interface

//-- custom includes
%include "i_part.i"
%include "e_limb_side.i"
%include "i_limb.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_surface_part
%{
	#include "../../../src/mae/fl/laban/ps/surface_part.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_limb);
%shared_ptr(mae::fl::laban::ps::surface_part);

//-- cast method
%extend mae::fl::laban::ps::surface_part {
  static std::shared_ptr<mae::fl::laban::ps::surface_part > cast_to_surface_part(std::shared_ptr<mae::fl::laban::ps::i_part> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::ps::surface_part>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/surface_part.hpp"

//-- templates
//...
