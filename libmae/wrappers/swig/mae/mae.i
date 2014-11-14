 // mae.i - SWIG interface


%ignore operator<<;
//TODO uncomment and handle shared_ptr SWIG dummy classes...
//%feature("director"); 
#pragma SWIG nowarn=302  

//generate the top-level module
%module(directors="1") Maejava
%{

%}

//shared_ptr public
#define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...) SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)

//include all that is required
%include "fl/fl.i"

//TODO define renaming rules in here
//%rename("%(regex:/^([A-Z][a-z]+)+_(.*)/\\2/)s", %$isenumitem) "";
//http://stackoverflow.com/questions/21783689/swig-how-to-rename-generated-java-code-according-to-a-regex