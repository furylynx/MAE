//-- nite_controller.i - SWIG interface

//-- custom includes
%include "device_info.i"

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

//-- define methods that are to be ignored
%ignore nite_controller::initialize; 
%ignore nite_controller::file_exists; 
%ignore nite_controller::check_rc; 
%ignore nite_controller::cb_user_newuser; 
%ignore nite_controller::cb_user_lostuser; 
%ignore nite_controller::cb_userpose_posedetected; 
%ignore nite_controller::cb_usercalibration_calibrationstart; 
%ignore nite_controller::cb_usercalibration_calibrationcomplete; 
%ignore nite_controller::scb_user_newuser; 
%ignore nite_controller::scb_user_lostuser; 
%ignore nite_controller::scb_userpose_posedetected; 
%ignore nite_controller::scb_usercalibration_calibrationstart; 
%ignore nite_controller::scb_usercalibration_calibrationcomplete; 

//-- define MACRO in order to not have input errors
#define XN_CALLBACK_TYPE 

//-- define general_skeleton (we don't know anything about it here
class mae::general_skeleton {};
%nodefaultctor mae::general_skeleton; 
%nodefaultdtor mae::general_skeleton; 

//-- module definition
%module(directors="1") w_nite_controller
%{
	#include "../../../src/mae/nite/nite_controller.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::nite::device_info);
%shared_ptr(mae::nite::nite_controller);

//-- Parse the original header file
%include "../../../src/mae/nite/nite_controller.hpp"

//-- templates
%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
