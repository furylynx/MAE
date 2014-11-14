/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class IMovementVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected IMovementVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IMovementVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_IMovementVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public IMovementVector() {
    this(MaeJavaJNI.new_IMovementVector__SWIG_0(), true);
  }

  public IMovementVector(long n) {
    this(MaeJavaJNI.new_IMovementVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.IMovementVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.IMovementVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.IMovementVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.IMovementVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.IMovementVector_clear(swigCPtr, this);
  }

  public void pushBack(IMovement x) {
    MaeJavaJNI.IMovementVector_pushBack(swigCPtr, this, IMovement.getCPtr(x), x);
  }

  public IMovement get(int i) {
    long cPtr = MaeJavaJNI.IMovementVector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new IMovement(cPtr, true);
  }

  public void set(int i, IMovement val) {
    MaeJavaJNI.IMovementVector_set(swigCPtr, this, i, IMovement.getCPtr(val), val);
  }

}
