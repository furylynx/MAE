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
%ignore mae::nite::nite_controller::initialize; 
%ignore mae::nite::nite_controller::file_exists; 
%ignore mae::nite::nite_controller::check_rc; 
%ignore mae::nite::nite_controller::cb_user_newuser; 
%ignore mae::nite::nite_controller::cb_user_lostuser; 
%ignore mae::nite::nite_controller::cb_userpose_posedetected; 
%ignore mae::nite::nite_controller::cb_usercalibration_calibrationstart; 
%ignore mae::nite::nite_controller::cb_usercalibration_calibrationcomplete; 
%ignore mae::nite::nite_controller::scb_user_newuser; 
%ignore mae::nite::nite_controller::scb_user_lostuser; 
%ignore mae::nite::nite_controller::scb_userpose_posedetected; 
%ignore mae::nite::nite_controller::scb_usercalibration_calibrationstart; 
%ignore mae::nite::nite_controller::scb_usercalibration_calibrationcomplete; 

//-- define MACRO in order to not have input errors
#define XN_CALLBACK_TYPE 

//-- define general_skeleton (we don't use it here directly)
%pragma(java) jniclassimports=%{
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
%}

%typemap(javaimports) mae::nite::nite_controller %{
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
%}

%typemap("javapackage") mae::general_skeleton, mae::general_skeleton *, mae::general_skeleton & "maejava.GeneralSkeleton";
%typemap("javapackage") std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::shared_ptr<mae::general_skeleton> > *, std::vector<std::shared_ptr<mae::general_skeleton> > & "maejava.GeneralSkeletonVector";

//-- general skeleton definition as well as the vector are required to be imported, not included! This forces swig to not create new classes for them.
%import "../../../../libmae/wrappers/swig/mae/general_skeleton.i"
%import "general_skeleton_vector.i"

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
//%template (GeneralSkeletonVector) std::vector<std::shared_ptr<mae::general_skeleton> >;
