//-- fl_skeleton.i - SWIG interface
 
//-- custom includes
%include "../general_skeleton.i"
%include "../math/basis.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_fl_skeleton
%{
	#include "../../../src/mae/fl/fl_skeleton.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::bone);
%shared_ptr(mae::math::vec3d);
%shared_ptr(mae::math::basis);
%shared_ptr(mae::hierarchy);
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::fl_skeleton);


//-- Parse the original header file
%include "../../../src/mae/fl/fl_skeleton.hpp"

//-- templates
//...
