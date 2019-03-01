//-- i_decision_maker.i - SWIG interface
 
//-- custom includes
//...
 
//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_i_decision_maker
%{
	#include "../../../src/mae/fl/laban/i_decision_maker.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::i_decision_maker<mae::fl::laban::i_movement>);
%shared_ptr(mae::fl::laban::i_movement);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/i_decision_maker.hpp"

//-- templates
%template (IMovementDecisionMaker) mae::fl::laban::i_decision_maker<mae::fl::laban::i_movement>;
