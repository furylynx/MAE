//-- e_relationship_type.i - SWIG interface
 
//-- custom includes
//...
 
//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_e_relationship_type
%{
	#include "../../../src/mae/fl/laban/e_relationship_type.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/e_relationship_type.hpp"

//-- templates
%template(IntVector) std::vector<int>;
%template(ERelationshipTypeVector) std::vector<mae::fl::laban::e_relationship_type>;
