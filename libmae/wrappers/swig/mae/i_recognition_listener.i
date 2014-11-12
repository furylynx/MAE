 // i_recognition_listener.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"

%module(directors="1") w_i_recognition_listener
%{
	#include "../../../src/mae/i_recognition_listener.hpp"
%}

//Director
//%feature("director") laban_sequence_recognition_listener;

//shared_ptr
%shared_ptr(mae::i_recognition_listener<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence);

// Parse the original header file
%include "../../../src/mae/i_recognition_listener.hpp"

//templates
%template(string_vector) std::vector<std::string>;
%template (laban_sequence_recognition_listener) mae::i_recognition_listener<mae::fl::laban::laban_sequence>;
%template (laban_sequence_vector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;




