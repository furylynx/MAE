//-- ini_reader.i - SWIG interface
 
//-- custom includes
//...
 
//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "exception.i"

//-- ignores
%ignore mae::ini_reader::get_value_nex;


//-- module definition
%module(directors="1") w_ini_reader
%{
	#include "../../../src/mae/ini_reader.hpp"
%}

//-- shared_ptr
//...

//-- Parse the original header file
%include "../../../src/mae/ini_reader.hpp"

//-- templates
//...
