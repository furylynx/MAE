//-- string_vector.i - SWIG interface
//-- This file is necessary in order to suppress the creation of a new class for the vector

//-- global include
%include "std_string.i"
%include "std_vector.i"

//-- create the vector for the class
%template (StringVector) std::vector<std::string>;
