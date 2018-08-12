//-- i_pose_listener.i - SWIG interface

//-- custom includes
%include "general_pose.i"

//-- shared_ptr
%shared_ptr(mae::general_pose);


%feature("director") mae::i_pose_listener;

//%typemap(javapackage) GeneralPose "maejava"
//%typemap(javapackage) mae::general_pose "maejava"
//%typemap(javapackage) std::shared_ptr<mae::general_pose> "maejava"

//%typemap(javapackage) std::shared_ptr<mae::general_pose>, std::shared_ptr<mae::general_pose> *, std::shared_ptr<mae::general_pose> & "maejava";
//%typemap(javapackage) mae::general_pose, mae::general_pose *, mae::general_pose & "maejava";

%typemap(javadirectorin) std::shared_ptr<mae::general_pose> "new $typemap(jstype, mae::general_pose)($1,true)";
%typemap(directorin,descriptor="L$typemap(jstype, mae::general_pose);") std::shared_ptr<mae::general_pose> %{
    *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<mae::general_pose> "$typemap(jstype, mae::general_pose).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<mae::general_pose> %{
    $&1_type tmp = NULL;
    *($&1_type*)&tmp = *($&1_type*)&$input;
    if (!tmp) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
        return NULL;
    }
    $result = *tmp;
%}

//-- global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "exception.i"
%include "stdint.i"


//-- module definition
%module(directors="1") w_i_pose_listener
%{
	#include "../../../src/mae/i_pose_listener.hpp"
%}



//-- Parse the original header file
%include "../../../src/mae/i_pose_listener.hpp"

//-- templates
//...
