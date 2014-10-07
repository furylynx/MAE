// laban_sequence.i - SWIG interface
 
//custom includes
%include "column_definition.i"
%include "i_movement.i"
%include "e_time_unit.i"


//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module w_laban_sequence
%{
	#include "../../../src/mae/fl/laban/laban_sequence.hpp"
%}

//shared_ptr
%shared_ptr(column_definition);
%shared_ptr(i_movement);

//templates
%template (string_vector) std::vector<std::string>;
%template (coldef_vector) std::vector<std::shared_ptr<column_definition> >;
%template (i_mov_vector) std::vector<std::shared_ptr<i_movement> >
%template (int_vector) std::vector<int>;


// Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence.hpp"
