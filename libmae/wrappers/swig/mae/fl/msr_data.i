//-- msr_data.i - SWIG interface
 
//-- custom includes
%include "../general_skeleton.i"
 
//-- global includes

%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"

//%feature("director") mae::fl::msr_data; 

//-- module definition
%module(directors="1") w_msr_data
%{
	#include "../../../src/mae/fl/msr_data.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::msr_data);

//-- Parse the original header file
%include "../../../src/mae/fl/msr_data.hpp"

//-- templates
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
