 // i_sequence_listener.i - SWIG interface
 
%include "shared_ptr.i"
 
 %module i_sequence_listener
 %{
 #include "../../../src/mae/i_sequence_listener.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_sequence_listener.hpp"
