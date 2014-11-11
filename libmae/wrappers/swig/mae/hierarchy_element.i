// hierarchy_element.i - SWIG interface

//custom includes
//%import "hierarchy.i"

//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_hierarchy_element
%{
	#include "../../../src/mae/hierarchy_element.hpp"
%}

//shared_ptr
%shared_ptr(mae::hierarchy_element);


//templates
%template(hierarchy_element_vector) std::vector<std::shared_ptr<mae::hierarchy_element> >;

// Parse the original header file
%include "../../../src/mae/hierarchy_element.hpp"
