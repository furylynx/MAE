//-- msr_data_controller.i - SWIG interface
 
//-- custom includes
%include "msr_spec.i"
%include "msr_data.i"
%include "../general_skeleton.i"

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "exception.i"

//-- TODO director
//%typemap(javadirectorin) std::shared_ptr<mae::fl::msr_spec> "new msr_spec($jniinput, false)"
//%typemap(javadirectorin) std::shared_ptr<mae::fl::general_skeleton> "new general_skeleton($jniinput, false)"
//%feature("director") mae::fl::bvh_controller; 

//-- module definition
%module(directors="1") w_msr_data_controller
%{
	#include "../../../src/mae/fl/msr_data_controller.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::msr_spec);
%shared_ptr(mae::fl::msr_data_controller);

//-- Parse the original header file
%include "../../../src/mae/fl/msr_data_controller.hpp"

//-- templates
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
