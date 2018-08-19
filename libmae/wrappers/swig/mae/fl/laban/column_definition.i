//-- column_definition.i - SWIG interface

//-- custom includes
%include "../../e_bone.i"
%include "ps/i_pre_sign.i"

//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_column_definition
%{
	#include "../../../src/mae/fl/laban/column_definition.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::ps::i_pre_sign);
%shared_ptr(mae::fl::laban::column_definition);

//-- Parse the original header file
%include "../../../src/mae/fl/laban/column_definition.hpp"

//-- templates
%template (ColumnDefinitionVector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;
