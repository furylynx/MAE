//-- i_sequence_listener.i - SWIG interface

//-- custom includes
%include "fl/laban/laban_sequence.i"

//-- global includes
%include "std_shared_ptr_fix.i"
%include "stdint.i"

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
%feature("director") mae::i_sequence_listener;
#endif

//-- module definition
%module(directors="1") w_i_sequence_listener
%{
    #include "../../../src/mae/i_sequence_listener.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::i_sequence_listener);
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::i_sequence_listener<mae::fl::laban::laban_sequence>);

//-- typemaps to fix shared_ptr
#ifdef SWIGJAVA
%typemap(javadirectorin) std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> > "new $typemap(jstype, mae::i_sequence_listener<mae::fl::laban::laban_sequence>)($1,true)";
%typemap(directorin,descriptor="L$typemap(jstype, mae::i_sequence_listener<mae::fl::laban::laban_sequence>);") std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> > %{
    *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> > "$typemap(jstype, mae::i_sequence_listener<mae::fl::laban::laban_sequence>).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> > %{
    $&1_type tmp = NULL;
    *($&1_type*)&tmp = *($&1_type*)&$input;
    if (!tmp) {
        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
        return NULL;
    }
    $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<mae::fl::laban::laban_sequence> "new $typemap(jstype, mae::fl::laban::laban_sequence)($1,true)";
%typemap(directorin,descriptor="Lmaejava/LabanSequence;") std::shared_ptr<mae::fl::laban::laban_sequence> %{
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
%typemap(csdirectorin) std::shared_ptr<mae::i_sequence_listener<mae::fl::laban::laban_sequence> > "new NativeLabanSequenceSequenceListener($iminput, true)"
%typemap(csdirectorin) std::shared_ptr<mae::fl::laban::laban_sequence> "new LabanSequence($iminput, true)"
#endif

//-- Parse the original header file
%include "../../../src/mae/i_sequence_listener.hpp"

//-- templates
%template (NativeLabanSequenceSequenceListener) mae::i_sequence_listener<mae::fl::laban::laban_sequence>;

//-- Proxy for actual interface
%pragma(java) modulecode=%{
static class NativeLabanSequenceSequenceListenerProxy extends NativeLabanSequenceSequenceListener {
    private ILabanSequenceSequenceListener delegate;
    public NativeLabanSequenceSequenceListenerProxy(ILabanSequenceSequenceListener i) {
        delegate = i;
    }

    public void onSequence(java.math.BigInteger timestamp, LabanSequence sequence) {
        delegate.onSequence(timestamp, sequence);
    }
}

public static NativeLabanSequenceSequenceListener makeNative(ILabanSequenceSequenceListener i) {
    if (i instanceof NativeLabanSequenceSequenceListener) {
        // If it already *is* a NativeInterface don't bother wrapping it again
        return (NativeLabanSequenceSequenceListener)i;
    }
    return new NativeLabanSequenceSequenceListenerProxy(i);
    }
%}
