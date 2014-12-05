//-- custom_limb.i - SWIG interface
 
//-- custom includes
%include "i_part.i"
%include "i_limb.i"
%include "i_endpoint.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_custom_limb
%{
	#include "../../../src/mae/fl/laban/ps/custom_limb.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_part);
%shared_ptr(mae::fl::laban::ps::i_limb);
%shared_ptr(mae::fl::laban::ps::i_endpoint);
%shared_ptr(mae::fl::laban::ps::custom_limb);

//-- cast method
%extend mae::fl::laban::ps::custom_limb {
  static std::shared_ptr<mae::fl::laban::ps::custom_limb > cast_to_custom_limb(std::shared_ptr<mae::fl::laban::ps::i_part> base) 
  {
    return std::dynamic_pointer_cast<mae::fl::laban::ps::custom_limb>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/ps/custom_limb.hpp"

//-- templates
//...
