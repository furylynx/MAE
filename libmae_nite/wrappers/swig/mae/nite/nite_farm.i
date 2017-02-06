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
%ignore mae::nite::nite_farm::list_available_devices;
%ignore mae::nite::nite_farm::get_node_info;
%ignore mae::nite::nite_farm::set_merger;
%ignore mae::nite::nite_farm::get_merger;

//-- define general_skeleton (we don't use it here directly)
%pragma(java) jniclassimports=%{
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
import maejava.StringVector;
%}

%typemap(javaimports) mae::nite::nite_farm %{
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
import maejava.StringVector;
%}

%typemap(javaimports) mae::nite::nite_farm %{
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
import maejava.StringVector;
%}

%typemap(javaimports) std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > %{
import maejava.GeneralSkeletonVector;
%}

%typemap(javaimports) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > > %{
import maejava.GeneralSkeletonVector;
%}

%typemap("javapackage") mae::general_skeleton, mae::general_skeleton *, mae::general_skeleton & "maejava.GeneralSkeleton";
%typemap("javapackage") std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::shared_ptr<mae::general_skeleton> > *, std::vector<std::shared_ptr<mae::general_skeleton> > & "maejava.GeneralSkeletonVector";
%typemap("javapackage") std::vector<std::string>, std::vector<std::string> *, std::vector<std::string> & "maejava.StringVector";

//-- general skeleton definition as well as the vector are required to be imported, not included! This forces swig to not create new classes for them.
%import "../../../../libmae/wrappers/swig/mae/general_skeleton.i"
%import "general_skeleton_vector.i"
%import "string_vector.i"

//-- module definition
%module(directors="1") w_nite_farm
%{
	#include "../../../src/mae/nite/nite_farm.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::nite::device_info);
%shared_ptr(mae::nite::nite_controller);
%shared_ptr(mae::nite::nite_farm);

//-- Parse the original header file
%include "../../../src/mae/nite/nite_farm.hpp"

//-- templates
%template (GeneralSkeletonVectorVector) std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > >;
%template (GeneralSkeletonVectorGeneralSkeletonVectorVectorPair) std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, std::vector<std::vector<std::shared_ptr<mae::general_skeleton> > > >;
%template (NiteControllerVector) std::vector<std::shared_ptr<mae::nite::nite_controller> >;
//%template (StringVector) std::vector<std::string>;
%template (DeviceInfoVector) std::vector<std::shared_ptr<mae::nite::device_info> >;
