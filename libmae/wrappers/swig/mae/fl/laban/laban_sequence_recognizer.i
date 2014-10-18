// laban_sequence_recognizer.i - SWIG interface
 
//custom includes
%include "../../bone.i"
%include "../../i_sequence_recognizer.i"

%include "laban_sequence.i"
%include "column_definition.i"

%include "decision_forest.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_laban_sequence_recognizer
%{
	#include "../../../src/mae/fl/laban/laban_sequence_recognizer.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::fl::laban::column_definition);


//templates
%template (bone_vector) std::vector<mae::bone>;
%template (laban_sequence_sequence_recognizer) mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>;
%template (coldef_vector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;

// Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence_recognizer.hpp"
