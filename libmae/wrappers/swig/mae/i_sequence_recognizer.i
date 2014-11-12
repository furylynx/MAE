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
%shared_ptr(mae::i_sequence_recognizer);
%shared_ptr(mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence);

// Parse the original header file
%include "../../../src/mae/i_sequence_recognizer.hpp"

//templates
%template (bone_vector) std::vector<mae::bone>;
%template (laban_sequence_vector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;
%template (laban_sequence_sequence_recognizer) mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>;

