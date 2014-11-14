/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class EAreaVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected EAreaVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(EAreaVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_EAreaVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EAreaVector() {
    this(MaeJavaJNI.new_EAreaVector__SWIG_0(), true);
  }

  public EAreaVector(long n) {
    this(MaeJavaJNI.new_EAreaVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.EAreaVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.EAreaVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.EAreaVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.EAreaVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.EAreaVector_clear(swigCPtr, this);
  }

  public void pushBack(EArea x) {
    MaeJavaJNI.EAreaVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public EArea get(int i) {
    return EArea.swigToEnum(MaeJavaJNI.EAreaVector_get(swigCPtr, this, i));
  }

  public void set(int i, EArea val) {
    MaeJavaJNI.EAreaVector_set(swigCPtr, this, i, val.swigValue());
  }

}
