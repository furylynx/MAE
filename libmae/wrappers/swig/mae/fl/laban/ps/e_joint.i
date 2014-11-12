// e_joint.i - SWIG interface

//custom includes

//global includes
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"


//module definition
%module(directors="1") w_e_joint
%{
	#include "../../../src/mae/fl/laban/ps/e_joint.hpp"
%}

//shared_ptr
//...

// Parse the original header file
%include "../../../src/mae/fl/laban/ps/e_joint.hpp"

//templates
%template(int_vector) std::vector<int>;
%template(e_joint_vector) std::vector<mae::fl::laban::ps::e_joint>;
