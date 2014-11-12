// laban_sequence_reader.i - SWIG interface
 
//custom includes
%include "laban_sequence.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module(directors="1") w_laban_sequence_reader
%{
	#include "../../../src/mae/fl/laban/laban_sequence_reader.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::laban_sequence);

//templates

// Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence_reader.hpp"
