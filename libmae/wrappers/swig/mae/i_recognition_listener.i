//-- i_recognition_listener.i - SWIG interface

//-- custom includes

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "stdint.i"

//-- module definition
%module(directors="1") w_i_recognition_listener
%{
	#include "../../../src/mae/i_recognition_listener.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::i_recognition_listener);

//-- Parse the original header file
%include "../../../src/mae/i_recognition_listener.hpp"

//-- templates
%template(StringVector) std::vector<std::string>;

