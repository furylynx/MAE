// i_sequence_listener.i - SWIG interface
 
//custom includes 

//global includes
%include "std_shared_ptr.i"
 
%module(directors="1") w_i_sequence_listener
%{
	#include "../../../src/mae/i_sequence_listener.hpp"
%}

//shared_ptr
%shared_ptr(mae::i_sequence_listener<mae::fl::laban::laban_sequence>);

// Parse the original header file
%include "../../../src/mae/i_sequence_listener.hpp"

//templates
%template (laban_sequence_sequence_listener) mae::i_sequence_listener<mae::fl::laban::laban_sequence>;
%template (laban_sequence_vector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;

//Director
//%feature("director") laban_sequence_sequence_listener;
