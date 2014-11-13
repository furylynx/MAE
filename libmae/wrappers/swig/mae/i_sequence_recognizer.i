// i_sequence_recognizer.i - SWIG interface

//custom includes
%include "bone.i"

//global includes
%include "std_shared_ptr.i"
%include "std_vector.i"
%include "exception.i"


%module(directors="1") w_i_sequence_recognizer
%{
	#include "../../../src/mae/i_sequence_recognizer.hpp"
%}

//shared_ptr
//%shared_ptr(mae::i_sequence_recognizer);

// Parse the original header file
%include "../../../src/mae/i_sequence_recognizer.hpp"

//templates
%template (bone_vector) std::vector<mae::bone>;
