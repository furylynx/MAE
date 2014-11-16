/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class StringVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public StringVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(StringVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_StringVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public StringVector() {
    this(MaeJavaJNI.new_StringVector__SWIG_0(), true);
  }

  public StringVector(long n) {
    this(MaeJavaJNI.new_StringVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.StringVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.StringVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.StringVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.StringVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.StringVector_clear(swigCPtr, this);
  }

  public void pushBack(String x) {
    MaeJavaJNI.StringVector_pushBack(swigCPtr, this, x);
  }

  public String get(int i) {
    return MaeJavaJNI.StringVector_get(swigCPtr, this, i);
  }

  public void set(int i, String val) {
    MaeJavaJNI.StringVector_set(swigCPtr, this, i, val);
  }

}
