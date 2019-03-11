//-- path.i - SWIG interface

//-- custom includes
%include "i_movement.i"
%include "e_path_type.i"

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_path
%{
	#include "../../../src/mae/fl/laban/path.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::path);

//-- cast method
%extend mae::fl::laban::path {
  static std::shared_ptr<mae::fl::laban::path> cast_to_path(std::shared_ptr<mae::fl::laban::i_movement> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::path>(base);
  }
}


//-- Parse the original header file
%include "../../../src/mae/fl/laban/path.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
