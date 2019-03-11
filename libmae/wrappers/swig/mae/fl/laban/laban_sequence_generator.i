//-- laban_sequence_generator.i - SWIG interface
 
//-- custom includes
%include "../../bone.i"
%include "../../general_enriched_pose.i"
%include "../../i_sequence_generator.i"
%include "../e_fl_direction.i"

%include "laban_sequence.i"
%include "column_definition.i"
 
//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- pre-definitions for templates
%shared_ptr(mae::i_sequence_generator<mae::fl::laban::laban_sequence>);
%template (LabanSequenceSequenceGenerator) mae::i_sequence_generator<mae::fl::laban::laban_sequence>;

//-- module definition
%module(directors="1") w_laban_sequence_generator
%{
	#include "../../../src/mae/fl/laban/laban_sequence_generator.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::fl::laban::column_definition);
%shared_ptr(mae::general_enriched_pose);
%shared_ptr(mae::i_sequence_generator<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence_generator);
%shared_ptr(laban_sequence_sequence_generator);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence_generator.hpp"

//-- templates
%template (BoneVector) std::vector<mae::bone>;
%template (ColumnDefinitionVector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;
