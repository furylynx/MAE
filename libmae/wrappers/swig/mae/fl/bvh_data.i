//-- bvh_data.i - SWIG interface
 
//-- custom includes
%include "../general_skeleton.i"
 
//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_vector.i"
%include "exception.i"

//%feature("director") mae::fl::bvh_data; 

//-- module definition
%module(directors="1") w_bvh_data
%{
	#include "../../../src/mae/fl/bvh_data.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::bvh_data);

//-- Parse the original header file
%include "../../../src/mae/fl/bvh_data.hpp"

//-- templates
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
