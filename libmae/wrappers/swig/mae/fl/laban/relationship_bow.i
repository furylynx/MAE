// relationship_bow.i - SWIG interface

//custom includes
%include "i_movement.i"
%include "e_relationship_type.i"
%include "mv/relationship_endpoint.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module w_relationship_bow
%{
	#include "../../../src/mae/fl/laban/relationship_bow.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::mv::relationship_endpoint);
%shared_ptr(mae::fl::laban::relationship_bow);

//templates
%template (int_int_map) std::map<int, int>;

// Parse the original header file
%include "../../../src/mae/fl/laban/relationship_bow.hpp"
