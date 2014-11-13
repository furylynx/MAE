 // mae.i - SWIG interface


%ignore operator<<;
%feature("director"); 
#pragma SWIG nowarn=302  

//generate the top-level module
%module(directors="1") mae
%{

%}

//include all that is required
%include "fl/fl.i"

//TODO define renaming rules in here
//%rename("%(regex:/^([A-Z][a-z]+)+_(.*)/\\2/)s", %$isenumitem) "";
//http://stackoverflow.com/questions/21783689/swig-how-to-rename-generated-java-code-according-to-a-regex