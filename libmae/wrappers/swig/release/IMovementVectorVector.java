/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class IMovementVectorVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public IMovementVectorVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IMovementVectorVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_IMovementVectorVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public IMovementVectorVector() {
    this(MaeJavaJNI.new_IMovementVectorVector__SWIG_0(), true);
  }

  public IMovementVectorVector(long n) {
    this(MaeJavaJNI.new_IMovementVectorVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.IMovementVectorVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.IMovementVectorVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.IMovementVectorVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.IMovementVectorVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.IMovementVectorVector_clear(swigCPtr, this);
  }

  public void pushBack(IMovementVector x) {
    MaeJavaJNI.IMovementVectorVector_pushBack(swigCPtr, this, IMovementVector.getCPtr(x), x);
  }

  public IMovementVector get(int i) {
    return new IMovementVector(MaeJavaJNI.IMovementVectorVector_get(swigCPtr, this, i), false);
  }

  public void set(int i, IMovementVector val) {
    MaeJavaJNI.IMovementVectorVector_set(swigCPtr, this, i, IMovementVector.getCPtr(val), val);
  }

}
