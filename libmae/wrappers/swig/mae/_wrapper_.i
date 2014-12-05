//-- ignore the shift operator used to implement the toString method in C++
%ignore operator<<;

//-- TODO currently SWIG does not support shared_ptr with java directors and thus polymorphism is not available for smart pointer objects
//--  "Note: There is currently no support for %shared_ptr and the director feature."
//-- 		- http://www.swig.org/Doc3.0/Library.html#Library_std_shared_ptr
//-- 
//--  see also: http://stackoverflow.com/questions/23333446/using-shared-ptr-with-swig-directors-for-java
//%feature("director");

//-- turn off all renaming warnings (there are plenty of it due to the usage of the same templated objects) 
#pragma SWIG nowarn=302  

//-- generate the top-level module (resulting in an empty class)
%module(directors="1") MaeJava
%{

%}

//-- load library automatically
%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("mae");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

//-- set shared_ptr contructor to public
#define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...) SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)

//-- renaming rules for camel case
%rename("%(camelcase)s", %$isclass) "";
%rename("%(camelcase)s", %$isenum) "";

%rename("%(uppercase)s", %$isenumitem) "";

%rename("%(lowercamelcase)s", %$isfunction) "";
%rename("%(lowercamelcase)s", %$isvariable) "";

//-- public methods
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE);
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE);

//-- exception
%include "exception.i"
%exception { 
    try {
        $action
    } catch (std::exception &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (...) {
        SWIG_exception(SWIG_RuntimeError, "unknown exception");
    }
}

//-- include definitions that are required
%include "mae.i"
