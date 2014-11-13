// bvh_controller.i - SWIG interface
 
//custom includes
%include "bvh_spec.i"
%include "../general_skeleton.i"

//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "exception.i"


//module definition
%module(directors="1") w_bvh_controller
%{
	#include "../../../src/mae/fl/bvh_controller.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::bvh_spec);
%shared_ptr(mae::fl::bvh_controller);

// Parse the original header file
%include "../../../src/mae/fl/bvh_controller.hpp"

//templates
%template (general_skeleton_vector) std::vector<std::shared_ptr<mae::general_skeleton> >;
%template (general_skeleton_vector_double_pair) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, double>;


