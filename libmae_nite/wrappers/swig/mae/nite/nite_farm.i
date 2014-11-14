//-- nite_farm.i - SWIG interface

//-- custom includes
%include "device_info.i"
%include "nite_controller.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "exception.i"

//-- define methods that are to be ignored
%ignore nite_farm::list_available_devices;
%ignore nite_farm::get_node_info;
%ignore nite_farm::set_merger;
%ignore nite_farm::get_merger;

//-- define general_skeleton (we don't know anything about it here
class mae::general_skeleton {};
%nodefaultctor mae::general_skeleton; 
%nodefaultdtor mae::general_skeleton; 

//-- module definition
%module(directors="1") w_nite_farm
%{
	#include "../../../../src/mae/nite/nite_farm.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::nite::device_info);
%shared_ptr(mae::nite::nite_controller);
%shared_ptr(mae::nite::nite_farm);

//-- Parse the original header file
%include "../../../../src/mae/nite/nite_farm.hpp"

//-- templates
%template (GeneralSkeletonVectorVector) std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > >;
%template (GeneralSkeletonVectorGeneralSkeletonVectorVectorPair) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > >;
%template (NiteControllerVector) std::vector<std::shared_ptr<nite_controller> >;
%template (StringVector) std::vector<std::string>;
%template (DeviceInfoVector) std::vector<std::shared_ptr<device_info> >;
