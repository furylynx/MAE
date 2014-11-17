/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class EContactHookVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EContactHookVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EContactHookVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_EContactHookVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EContactHookVector() {
    this(MaeJavaJNI.new_EContactHookVector__SWIG_0(), true);
  }

  public EContactHookVector(long n) {
    this(MaeJavaJNI.new_EContactHookVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.EContactHookVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.EContactHookVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.EContactHookVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.EContactHookVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.EContactHookVector_clear(swigCPtr, this);
  }

  public void pushBack(EContactHook x) {
    MaeJavaJNI.EContactHookVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public EContactHook get(int i) {
    return EContactHook.swigToEnum(MaeJavaJNI.EContactHookVector_get(swigCPtr, this, i));
  }

  public void set(int i, EContactHook val) {
    MaeJavaJNI.EContactHookVector_set(swigCPtr, this, i, val.swigValue());
  }

}