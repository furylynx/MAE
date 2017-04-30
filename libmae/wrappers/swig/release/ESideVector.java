/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ESideVector {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public ESideVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ESideVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ESideVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ESideVector() {
    this(MaeJavaJNI.new_ESideVector__SWIG_0(), true);
  }

  public ESideVector(long n) {
    this(MaeJavaJNI.new_ESideVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.ESideVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.ESideVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.ESideVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.ESideVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.ESideVector_clear(swigCPtr, this);
  }

  public void pushBack(ESide x) {
    MaeJavaJNI.ESideVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public ESide get(int i) {
    return ESide.swigToEnum(MaeJavaJNI.ESideVector_get(swigCPtr, this, i));
  }

  public void set(int i, ESide val) {
    MaeJavaJNI.ESideVector_set(swigCPtr, this, i, val.swigValue());
  }

}
