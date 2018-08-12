//-- relationship_bow.i - SWIG interface

//-- custom includes
%include "i_movement.i"
%include "e_relationship_type.i"
%include "mv/relationship_endpoint.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_relationship_bow
%{
	#include "../../../src/mae/fl/laban/relationship_bow.hpp"
%}

//-- cast method
%extend mae::fl::laban::relationship_bow {
  static std::shared_ptr<mae::fl::laban::relationship_bow> cast_to_relationship_bow(std::shared_ptr<mae::fl::laban::i_movement> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::relationship_bow>(base);
  }
}


//-- shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::relationship_endpoint);
%shared_ptr(mae::fl::laban::relationship_bow);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/relationship_bow.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
