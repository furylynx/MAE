//-- rewriting_rules_reader.i - SWIG interface
 
//-- custom includes
%include "i_movement.i"
%include "decision_value.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_rewriting_rules_reader
%{
	#include "../../../src/mae/fl/laban/rewriting_rules_reader.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >);
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::rewriting_rules_reader);
%shared_ptr(std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > >);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/rewriting_rules_reader.hpp"

//-- templates
%template (IMovementVectorVector) std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > >;
%template (IMovementVector) std::vector<std::shared_ptr<mae::fl::laban::i_movement> >;
%template (IMovementVectorVectorDecisionValue) mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > >;
%template (IMovementVectorVectorDecisionValueVector) std::vector<std::shared_ptr<mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > > >;
