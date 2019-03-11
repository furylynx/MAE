//-- bvh_spec.i - SWIG interface
 
//-- custom includes
 //...
 
//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"

//%feature("director") mae::fl::bvh_spec; 

//-- module definition
%module(directors="1") w_bvh_spec
%{
	#include "../../../src/mae/fl/bvh_spec.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::bvh_spec);

//-- Parse the original header file
%include "../../../src/mae/fl/bvh_spec.hpp"

//-- templates
%template (StringIntMap) std::map<std::string, int>;
%template (StringBoolMap) std::map<std::string, bool>;
