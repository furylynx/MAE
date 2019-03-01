//-- bvh_controller.i - SWIG interface
 
//-- custom includes
%include "bvh_spec.i"
%include "bvh_data.i"
%include "../general_skeleton.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "exception.i"

//-- TODO director
//%typemap(javadirectorin) std::shared_ptr<mae::fl::bvh_spec> "new bvh_spec($jniinput, false)"
//%typemap(javadirectorin) std::shared_ptr<mae::fl::general_skeleton> "new general_skeleton($jniinput, false)"
//%feature("director") mae::fl::bvh_controller; 

//-- module definition
%module(directors="1") w_bvh_controller
%{
	#include "../../../src/mae/fl/bvh_controller.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::bvh_spec);
%shared_ptr(mae::fl::bvh_controller);

//-- Parse the original header file
%include "../../../src/mae/fl/bvh_controller.hpp"

//-- templates
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
//%template (GeneralSkeletonVectorDoublePair) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, double>;
