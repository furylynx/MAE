//-- general_pose.i - SWIG interface
 
//-- custom includes
 
//-- global includes
//%include "stl.i"
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_list.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_general_pose
%{
	#include "../../../src/mae/general_pose.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_pose);

//%typemap(javadirectorin) std::shared_ptr<mae::general_pose> "new $typemap(javapackage, mae::general_pose).$typemap(jstype, mae::general_pose)($1,true)";
//%typemap(directorin,descriptor="L$typemap(javapackage, mae::general_pose)/$typemap(jstype, mae::general_pose);") std::shared_ptr<mae::general_pose> %{
//    std::cout << "din1" << std::endl;
//    *($&1_type*)&j$1 = new $1_type($1);
//    std::cout << "din2" << std::endl;
//%}
//
//%typemap(javadirectorout) std::shared_ptr<mae::general_pose> "$typemap(jstype, mae::general_pose).getCPtr($javacall)";
//%typemap(directorout) std::shared_ptr<mae::general_pose> %{
//    $&1_type tmp = NULL;
//    *($&1_type*)&tmp = *($&1_type*)&$input;
//    if (!tmp) {
//        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
//        return NULL;
//    }
//    $result = *tmp;
//%}

//%typemap(javapackage) GeneralPose, GeneralPose *, GeneralPose & "maejava"
//%typemap(javapackage) mae::general_pose, mae::general_pose *, mae::general_pose & "maejava"
//%typemap(javapackage) std::shared_ptr<mae::general_pose>, std::shared_ptr<mae::general_pose> *, std::shared_ptr<mae::general_pose> & "maejava"
//%typemap(javapackage) std::shared_ptr<general_pose>, std::shared_ptr<general_pose> *, std::shared_ptr<general_pose> & "maejava"

//-- Parse the original header file
%include "../../../src/mae/general_pose.hpp"

//-- templates
%template (IntList) std::list<int>;


