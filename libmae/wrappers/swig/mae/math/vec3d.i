// vec3d.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_vec3d
%{
	#include "../../../src/mae/math/vec3d.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/math/vec3d.hpp"

//templates
//...

//rename
//%rename (Vec3d) vec3d;
