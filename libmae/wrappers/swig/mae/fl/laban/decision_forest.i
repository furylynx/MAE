// decision_forest.i - SWIG interface
 
//custom includes
%include "../../bone.i"

%include "laban_sequence.i"
%include "column_definition.i"
%include "i_movement.i"

%include "i_decision_maker.i"
%include "decision_value.i"
%include "rewriting_forest.i"
 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_decision_forest
%{
	#include "../../../src/mae/fl/laban/decision_forest.hpp"
%}

//shared_ptr
%shared_ptr(mae::fl::laban::decision_forest);
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::fl::laban::column_definition);
%shared_ptr(mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >);
%shared_ptr(mae::fl::laban::rewriting_forest);
%shared_ptr(mae::fl::laban::i_decision_maker<mae::fl::laban::i_movement>);

//templates
%template (bone_vector) std::vector<mae::bone>;
%template (i_mov_vector_vector) std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > >;
%template (i_mov_vector) std::vector<std::shared_ptr<mae::fl::laban::i_movement> >;
%template (i_mov_vector_vector_dec_val) mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >;
%template (i_dec_maker) mae::fl::laban::i_decision_maker<mae::fl::laban::i_movement>;
%template (coldef_vector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;

// Parse the original header file
%include "../../../src/mae/fl/laban/decision_forest.hpp"
