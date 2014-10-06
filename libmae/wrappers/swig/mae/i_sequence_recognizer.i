// i_sequence_recognizer.i - SWIG interface
 
%include "shared_ptr.i"
%include "std_vector.i"
#include "exception.i"

#include "bone.i"

%template (bone_vector) vector<bone>;
 
 %module i_sequence_recognizer
 %{
 #include "../../../src/mae/i_sequence_recognizer.hpp"
 %}
 
 // Parse the original header file
 %include "../../../src/mae/i_sequence_recognizer.hpp"
