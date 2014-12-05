//-- e_space_direction.i - SWIG interface
 
//-- custom includes
//...

//-- global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_e_space_direction
%{
	#include "../../../src/mae/fl/laban/mv/e_space_direction.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_space_direction.hpp"

//-- templates
%template(IntVector) std::vector<int>;
%template(ESpaceDirectionVector) std::vector<mae::fl::laban::mv::e_space_direction>;
