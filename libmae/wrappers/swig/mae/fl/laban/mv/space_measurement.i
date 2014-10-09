// space_measurement.i - SWIG interface

//custom includes
%include "i_degree_sign.i"
%include "e_space.i"
%include "e_space_direction.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_space_measurement
%{
	#include "../../../src/mae/fl/laban/mv/space_measurement.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::mv::i_degree_sign);
%shared_ptr(mae::fl::laban::mv::space_measurement);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/space_measurement.hpp"
