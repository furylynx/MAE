// i_sequence_listener.i - SWIG interface
 
//custom includes 

//global includes
%include "std_shared_ptr.i"
 
%module w_i_sequence_listener
%{
	#include "../../../src/mae/i_sequence_listener.hpp"
%}

//shared_ptr
//TODO sequence template arg

//templates

// Parse the original header file
%include "../../../src/mae/i_sequence_listener.hpp"
