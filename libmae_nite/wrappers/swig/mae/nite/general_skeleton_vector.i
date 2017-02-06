//-- general_skeleton_vector.i - SWIG interface
//-- This file is necessary in order to suppress the creation of a new class for the vector

//-- global include
%include "std_vector.i"

//-- import the class
%import "../../../../libmae/wrappers/swig/mae/general_skeleton.i"

//-- define smart pointer for the class
%shared_ptr(mae::general_skeleton);

//-- create the vector for the class
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
