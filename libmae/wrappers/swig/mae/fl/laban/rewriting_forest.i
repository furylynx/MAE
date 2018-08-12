//-- rewriting_forest.i - SWIG interface

//-- custom includes
%include "../../bone.i"

%include "laban_sequence.i"
%include "column_definition.i"
%include "i_movement.i"

%include "i_decision_maker.i"
%include "decision_value.i"
%include "rewriting_forest.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_rewriting_forest
%{
	#include "../../../src/mae/fl/laban/rewriting_forest.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >);
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::rewriting_forest);
%shared_ptr(std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > >);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/rewriting_forest.hpp"

//-- templates
%template (IMovementVectorVector) std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > >;
%template (IMovementVector) std::vector<std::shared_ptr<mae::fl::laban::i_movement> >;
%template (IMovementVectorVectorDecisionValue) mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >;
%template (IMovementVectorVectorDecisionValueVector) std::vector<std::shared_ptr<mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > > >;
