// general_pose.i - SWIG interface
 
%include "shared_ptr.i"
%include "std_list.i"
#include "std_unordered_map.i"
#include "exception.i"

%template (int_list) list<int>;
%template (int_int_double_map) unordered_map<int, unordered_map<int, double> >;
%template (int_int_map) unordered_map<int, int>;
 
 %module general_pose
 %{
 #include "../../../src/mae/general_pose.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/general_pose.hpp"
