//-- relationship_endpoint.i - SWIG interface

//-- custom includes
%include "i_dynamics_sign.i"
%include "../ps/i_pre_sign.i"

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_map.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_relationship_endpoint
%{
	#include "../../../src/mae/fl/laban/mv/relationship_endpoint.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::relationship_endpoint);
%shared_ptr(mae::fl::laban::mv::i_dynamics_sign);
%shared_ptr(mae::fl::laban::ps::i_pre_sign);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/relationship_endpoint.hpp"

//-- templates
%template (IntIntMap) std::map<int, int>;
