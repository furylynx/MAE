//-- laban_sequence_recognizer.i - SWIG interface
 
//-- custom includes
%include "../../bone.i"
%include "../../i_sequence_recognizer.i"

%include "laban_sequence.i"
%include "column_definition.i"
%include "decision_forest.i"
 
//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- pre-definitions for templates
%shared_ptr(mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>);
%template (LabanSequenceSequenceRecognizer) mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>;

//-- module definition
%module(directors="1") w_laban_sequence_recognizer
%{
	#include "../../../src/mae/fl/laban/laban_sequence_recognizer.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::decision_forest);
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::fl::laban::column_definition);
%shared_ptr(mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence_recognizer);
%shared_ptr(laban_sequence_sequence_recognizer);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence_recognizer.hpp"

//-- templates
%template (BoneVector) std::vector<mae::bone>;
%template (ColumnDefinitionVector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;
%template (LabanSequenceVector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;
