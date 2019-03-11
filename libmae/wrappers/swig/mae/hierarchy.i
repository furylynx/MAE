//-- hierarchy.i - SWIG interface
 
//-- custom includes
//%import "hierarchy_element.i"


//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module w_hierarchy
%{
	#include "../../../src/mae/hierarchy.hpp"
%}

//-- director
%feature("nodirector") mae::hierarchy;

//-- shared_ptr
%shared_ptr(mae::hierarchy_element);
%shared_ptr(mae::hierarchy);

//-- Parse the original header file
%include "../../../src/mae/hierarchy.hpp"

//-- templates
%template(HierarchyElementVector) std::vector<std::shared_ptr<mae::hierarchy_element> >;

