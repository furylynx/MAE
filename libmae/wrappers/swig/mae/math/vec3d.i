//-- vec3d.i - SWIG interface

//-- custom includes

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_vec3d
%{
	#include "../../../src/mae/math/vec3d.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::math::vec3d);

//-- Parse the original header file
%include "../../../src/mae/math/vec3d.hpp"

//-- templates
//...


