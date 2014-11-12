// i_sequence_listener.i - SWIG interface
 
//custom includes 

//global includes
%include "std_shared_ptr.i"
 
%feature("notabstract") mae::i_sequence_listener<mae::fl::laban::laban_sequence>;
 
%module(directors="1") w_i_sequence_listener
%{
	#include "../../../src/mae/i_sequence_listener.hpp"
%}


//shared_ptr
//TODO sequence template arg

//templates
%template (laban_sequence_sequence_listener) std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> >;

//Director
%feature("director") mae::i_sequence_listener<mae::fl::laban::laban_sequence>;

// Parse the original header file
%include "../../../src/mae/i_sequence_listener.hpp"
