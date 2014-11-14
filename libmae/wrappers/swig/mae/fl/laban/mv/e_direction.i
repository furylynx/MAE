//-- e_direction.i - SWIG interface
 
//-- custom includes
//%import "../../e_fl_direction.i"
 
//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_e_direction
%{
	#include "../../../src/mae/fl/laban/mv/e_direction.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_direction.hpp"

//-- templates
%template(IntVector) std::vector<int>;
%template(EDirectionVector) std::vector<mae::fl::laban::mv::e_direction>;
