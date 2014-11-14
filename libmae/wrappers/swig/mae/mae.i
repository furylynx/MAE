 // mae.i - SWIG interface

//-- ignore the shift operator used to implement the toString method in C++
%ignore operator<<;

//-- TODO currently SWIG does not support shared_ptr with java directors and thus polymorphism is not available for smart pointer objects
//--  "Note: There is currently no support for %shared_ptr and the director feature."
//-- 		- http://www.swig.org/Doc3.0/Library.html#Library_std_shared_ptr
//-- 
//--  see also: http://stackoverflow.com/questions/23333446/using-shared-ptr-with-swig-directors-for-java
//%feature("director");

//-- turn off all renaming warnings (there are plenty of it due to the usage of the same templated objects) 
#pragma SWIG nowarn=302  

//-- generate the top-level module (resulting in an empty class)
%module(directors="1") MaeJava
%{

%}

//-- set shared_ptr contructor to public
#define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...) SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)

//-- include definitions that are required
%include "fl/fl.i"

//-- TODO define renaming rules in here
//%rename("%(regex:/^([A-Z][a-z]+)+_(.*)/\\2/)s", %$isenumitem) "";
//http://stackoverflow.com/questions/21783689/swig-how-to-rename-generated-java-code-according-to-a-regex