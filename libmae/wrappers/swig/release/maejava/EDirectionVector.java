/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class EDirectionVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EDirectionVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EDirectionVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_EDirectionVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EDirectionVector() {
    this(MaeJavaJNI.new_EDirectionVector__SWIG_0(), true);
  }

  public EDirectionVector(long n) {
    this(MaeJavaJNI.new_EDirectionVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.EDirectionVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.EDirectionVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.EDirectionVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.EDirectionVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.EDirectionVector_clear(swigCPtr, this);
  }

  public void pushBack(EDirection x) {
    MaeJavaJNI.EDirectionVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public EDirection get(int i) {
    return EDirection.swigToEnum(MaeJavaJNI.EDirectionVector_get(swigCPtr, this, i));
  }

  public void set(int i, EDirection val) {
    MaeJavaJNI.EDirectionVector_set(swigCPtr, this, i, val.swigValue());
  }

}
