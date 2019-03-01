//-- laban_sequence.i - SWIG interface
 
//-- custom includes
%include "column_definition.i"
%include "i_movement.i"
%include "e_time_unit.i"
%include "draw_laban_rect.i"
%include "svg_style.i"

//--global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_laban_sequence
%{
	#include "../../../src/mae/fl/laban/laban_sequence.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::column_definition);
%shared_ptr(mae::fl::laban::i_movement);
%shared_ptr(mae::fl::laban::laban_sequence);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/laban_sequence.hpp"

//-- templates
%template (StringVector) std::vector<std::string>;
%template (ColumnDefinitionVector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;
%template (IMovementVector) std::vector<std::shared_ptr<mae::fl::laban::i_movement> >;
%template (IntVector) std::vector<int>;
