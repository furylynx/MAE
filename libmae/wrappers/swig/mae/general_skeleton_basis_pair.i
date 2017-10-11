//-- general_skeleton_basis_pair.i - SWIG interface
 
//-- custom includes
%include "general_skeleton.i"
%include "math/basis.i"
 
//-- global includes
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_general_skeleton_basis_pair
%{
	#include "../../../src/mae/general_skeleton_basis_pair.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::math::basis);
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::general_skeleton_basis_pair);

//-- Parse the original header file
%include "../../../src/mae/general_skeleton_basis_pair.hpp"

//-- templates
%template (GeneralSkeletonBasisPairVector) std::vector<std::shared_ptr<mae::general_skeleton_basis_pair> >;
