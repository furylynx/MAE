// e_contact_hook.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_contact_hook
%{
	#include "../../../src/mae/fl/laban/mv/e_contact_hook.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/mv/e_contact_hook.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_contact_hook_vector) std::vector<mae::fl::laban::mv::e_contact_hook>;
