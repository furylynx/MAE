//-- sensor_info.i - SWIG interface

//-- custom includes
//...

//-- global includes
%include "std_shared_ptr.i"
//%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//-- module definition
%module(directors="1") w_sensor_info
%{
	#include "../../../src/mae/sensor/sensor_info.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::sensor::sensor_info)

//-- Parse the original header file
%include "../../../src/mae/sensor/sensor_info.hpp"

//-- templates
%template (SensorInfoVector) std::vector<std::shared_ptr<mae::sensor::sensor_info> >;
