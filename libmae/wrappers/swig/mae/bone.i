 // bone.i - SWIG interface

%include "std_string.i"
%include "std_vector.i"
%include "except.i"

%include "e_bone.i"

%template(vector_bone) vector<bone>;

%module bone
%{
 #include "../../../src/mae/bone.hpp"
%}     
 
// Parse the original header file
%include "../../../src/mae/bone.hpp"