// basis.i - SWIG interface

//custom includes
%include "vec3d.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//module definition
%module w_basis
%{
	#include "../../../src/mae/math/basis.hpp"
%}

//templates


//shared_ptr
%shared_ptr(mae::math::vec3d);

// Parse the original header file
%include "../../../src/mae/math/basis.hpp"
