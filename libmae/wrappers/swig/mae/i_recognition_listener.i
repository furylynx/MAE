//-- i_recognition_listener.i - SWIG interface

//-- custom includes
%include "fl/laban/laban_sequence.i"

//-- global includes
%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "std_vector.i"
%include "stdint.i"

%feature("director") mae::i_recognition_listener;

//-- module definition
%module(directors="1") w_i_recognition_listener
%{
	#include "../../../src/mae/i_recognition_listener.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::i_recognition_listener);
%shared_ptr(mae::i_recognition_listener<mae::fl::laban::laban_sequence>);

//-- typemaps to fix shared_ptr
#ifdef SWIGJAVA
%typemap(javadirectorin) std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> > "new $typemap(jstype, mae::i_recognition_listener<mae::fl::laban::laban_sequence>)($1,true)";
%typemap(directorin,descriptor="L$typemap(jstype, mae::i_recognition_listener<mae::fl::laban::laban_sequence>);") std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> > %{
	*($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> > "$typemap(jstype, mae::i_recognition_listener<mae::fl::laban::laban_sequence>).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> > %{
	$&1_type tmp = NULL;
	*($&1_type*)&tmp = *($&1_type*)&$input;
	if (!tmp) {
		SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
		return NULL;
	}
	$result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<mae::fl::laban::laban_sequence> "new $typemap(jstype, mae::fl::laban::laban_sequence)($1,true)";
%typemap(directorin,descriptor="L$typemap(jstype, mae::fl::laban::laban_sequence);") std::shared_ptr<mae::fl::laban::laban_sequence> %{
	*($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<mae::fl::laban::laban_sequence> "$typemap(jstype, mae::fl::laban::laban_sequence).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<mae::fl::laban::laban_sequence> %{
	$&1_type tmp = NULL;
	*($&1_type*)&tmp = *($&1_type*)&$input;
	if (!tmp) {
		SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
		return NULL;
	}
	$result = *tmp;
%}
#elif defined(SWIGCSHARP)
%typemap(csdirectorin) std::shared_ptr<mae::i_recognition_listener<mae::fl::laban::laban_sequence> > "new NativeLabanSequenceRecognitionListener($iminput, true)"
%typemap(csdirectorin) std::shared_ptr<mae::fl::laban::laban_sequence> "new LabanSequence($iminput, true)"
#endif

//-- Parse the original header file
%include "../../../src/mae/i_recognition_listener.hpp"

//-- templates
%template(StringVector) std::vector<std::string>;
%template (LabanSequenceVector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;
%template (NativeLabanSequenceRecognitionListener) mae::i_recognition_listener<mae::fl::laban::laban_sequence>;

//-- Proxy for actual interface
%pragma(java) modulecode=%{
static class NativeLabanSequenceRecognitionListenerProxy extends NativeLabanSequenceRecognitionListener {
	private ILabanSequenceRecognitionListener delegate;
	public NativeLabanSequenceRecognitionListenerProxy(ILabanSequenceRecognitionListener i) {
		delegate = i;
	}

	public void onRecognition(java.math.BigInteger timestamp, LabanSequenceVector sequences) {
		delegate.onRecognition(timestamp, sequences);
	}

	public void onRecognition(java.math.BigInteger timestamp, StringVector title) {
		delegate.onRecognition(timestamp, title);
	}
}

public static NativeLabanSequenceRecognitionListener makeNative(ILabanSequenceRecognitionListener i) {
	if (i instanceof NativeLabanSequenceRecognitionListener) {
		// If it already *is* a NativeInterface don't bother wrapping it again
		return (NativeLabanSequenceRecognitionListener)i;
	}
	return new NativeLabanSequenceRecognitionListenerProxy(i);
}
%}
