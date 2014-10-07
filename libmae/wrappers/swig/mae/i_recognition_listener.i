 // i_recognition_listener.i - SWIG interface

//custom includes

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"

%module w_i_recognition_listener
%{
	#include "../../../src/mae/i_recognition_listener.hpp"
%}

//shared_ptr
//TODO sequence template arg

//templates
%template(string_vector) std::vector<std::string>;
//TODO vector of sequences template arg

// Parse the original header file
%include "../../../src/mae/i_recognition_listener.hpp"
