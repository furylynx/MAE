
#if SWIG_VERSION >= 0x040000
	%include "std_shared_ptr.i"
#elif defined(SWIGJAVA)
	%include "std_shared_ptr_java_fix.i"
#else
	%include "std_shared_ptr.i"
#endif

