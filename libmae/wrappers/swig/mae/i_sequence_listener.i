// i_sequence_listener.i - SWIG interface
 
//custom includes 
//...

//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"

%feature("director") mae::i_sequence_listener; 

%module(directors="1") w_i_sequence_listener
%{
	#include "../../../src/mae/i_sequence_listener.hpp"
%}

//shared_ptr
//%shared_ptr(mae::i_sequence_listener);
//%shared_ptr(mae::i_sequence_listener<mae::fl::laban::laban_sequence>);

// Parse the original header file
%include "../../../src/mae/i_sequence_listener.hpp"

//templates
//...

//Director
//%feature("director") laban_sequence_sequence_listener;

