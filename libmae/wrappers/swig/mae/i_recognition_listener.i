 // i_recognition_listener.i - SWIG interface
 
%include "shared_ptr.i"
 
 %module i_recognition_listener
 %{
 #include "../../../src/mae/i_recognition_listener.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_recognition_listener.hpp"
