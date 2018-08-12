//-- hierarchy_element.i - SWIG interface

//-- custom includes
//%import "hierarchy.i"

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module w_hierarchy_element
%{
	#include "../../../src/mae/hierarchy_element.hpp"
%}

//-- director
%feature("nodirector") mae::hierarchy_element;

//-- shared_ptr
%shared_ptr(mae::hierarchy_element);

//-- Parse the original header file
%include "../../../src/mae/hierarchy_element.hpp"

//-- templates
%template(HierarchyElementVector) std::vector<std::shared_ptr<mae::hierarchy_element> >;
