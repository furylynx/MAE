//-- sensor_farm.i - SWIG interface

//-- custom includes
%include "../general_skeleton.i"
%include "../general_skeleton_basis_pair.i"
%include "i_sensor.i"

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
%template (GeneralSkeletonVectorVector) std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > >;
%template (GeneralSkeletonVectorGeneralSkeletonVectorVectorPair) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > >;
