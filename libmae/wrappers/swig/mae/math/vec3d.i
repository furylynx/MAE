// vec3d.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "exception.i"


//module definition
%module w_vec3d
%{
	#include "../../../src/mae/math/vec3d.hpp"
%}

//shared_ptr

//templates


// Parse the original header file
%include "../../../src/mae/math/vec3d.hpp"
