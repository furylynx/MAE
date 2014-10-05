 // maewrapper.i - SWIG interface
 
%include "stl.i"
%include "std_string.i"
%include "std_vector.i"
 
 //include all .i files required to make the movement controller work
 
 %module maewrapper
 %{
 #include "../../../src/mae/fl/fl_movement_controller.hpp"
 %}     
 
 // Parse the original header file
 %include "../../../src/mae/fl/fl_movement_controller.hpp"
 
%template(FooInt) Foo<int>;
%template(FooString) Foo<string>;
%template(FooVectorInt) Foo<vector<int> >;
