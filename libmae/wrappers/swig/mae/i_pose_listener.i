//-- i_pose_listener.i - SWIG interface
 
//-- custom includes
%include "general_pose.i"
 
//-- global includes

%include "std_shared_ptr_fix.i"
%include "exception.i"
%include "stdint.i"

%feature("director") mae::i_pose_listener;

//-- module definition
%module(directors="1") w_i_pose_listener
%{
	#include "../../../src/mae/i_pose_listener.hpp"
%}

//-- Rename the original interface class
%rename(NativePoseListener) mae::i_pose_listener;

//-- shared_ptr 
%shared_ptr(mae::general_pose);
%shared_ptr(mae::i_pose_listener);

//-- typemaps to fix shared_ptr
%typemap(javadirectorin) std::shared_ptr<mae::i_pose_listener> "new $typemap(jstype, mae::i_pose_listener)($1,true)";
%typemap(directorin,descriptor="L$typemap(jstype, mae::i_pose_listener);") std::shared_ptr<mae::i_pose_listener> %{
	*($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<mae::i_pose_listener> "$typemap(jstype, mae::i_pose_listener).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<mae::i_pose_listener> %{
	$&1_type tmp = NULL;
	*($&1_type*)&tmp = *($&1_type*)&$input;
	if (!tmp) {
		SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
		return NULL;
	}
	$result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<mae::general_pose> "new $typemap(jstype, mae::general_pose)($1,true)";
%typemap(directorin,descriptor="Lmaejava/GeneralPose;") std::shared_ptr<mae::general_pose> %{
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

//-- Parse the original header file
%include "../../../src/mae/i_pose_listener.hpp"

//-- templates
//...
		 
//-- Proxy for actual interface
%pragma(java) modulecode=%{
static class NativePoseListenerProxy extends NativePoseListener {
	private IPoseListener delegate;
	public NativePoseListenerProxy(IPoseListener i) {
		delegate = i;
	}

	public void onPose(java.math.BigInteger timestamp, GeneralPose pose) {
		delegate.onPose(timestamp, pose);
	}
}

public static NativePoseListener makeNative(IPoseListener i) {
	if (i instanceof NativePoseListener) {
		// If it already *is* a NativeInterface don't bother wrapping it again
		return (NativePoseListener)i;
	}
	return new NativePoseListenerProxy(i);
}
%}
