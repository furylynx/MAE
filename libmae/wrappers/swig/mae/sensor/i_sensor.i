//-- i_sensor.i - SWIG interface

//-- custom includes
%include "../general_skeleton.i"
%include "../general_skeleton_basis_pair.i"

//-- global includes
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_i_sensor
%{
	#include "../../../src/mae/sensor/i_sensor.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::sensor::i_sensor)
 
//-- Parse the original header file
%include "../../../src/mae/sensor/i_sensor.hpp"
 
//-- templates
%template (ISensorVector) std::vector<std::shared_ptr<mae::sensor::i_sensor> >;

