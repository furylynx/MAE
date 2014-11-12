 // i_recognition_listener.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"

%module(directors="1") w_i_recognition_listener
%{
	#include "../../../src/mae/i_recognition_listener.hpp"
%}

//shared_ptr
//TODO sequence template arg

//templates
%template(string_vector) std::vector<std::string>;
%template (laban_sequence_recognition_listener) std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> >;

//Director
%feature("director") laban_sequence_recognition_listener;

// Parse the original header file
%include "../../../src/mae/i_recognition_listener.hpp"
