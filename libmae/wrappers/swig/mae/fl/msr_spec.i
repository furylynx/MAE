//-- msr_spec.i - SWIG interface

//-- custom includes
 //...

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"

//%feature("director") mae::fl::msr_spec;

//-- module definition
%module(directors="1") w_msr_spec
%{
	#include "../../../src/mae/fl/msr_spec.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::msr_spec);

//-- Parse the original header file
%include "../../../src/mae/fl/msr_spec.hpp"

//-- templates
%template (UIntIntMap) std::map<unsigned int, int>;
