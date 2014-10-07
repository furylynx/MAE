// bvh_spec.i - SWIG interface
 
//custom includes
 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//module definition
%module w_bvh_spec
%{
	#include "../../../src/mae/fl/bvh_spec.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::bvh_spec);

//templates
%template (string_int_map) std::map<std::string, int>;
%template (string_bool_map) std::map<std::string, bool>;

// Parse the original header file
%include "../../../src/mae/fl/bvh_spec.hpp"
