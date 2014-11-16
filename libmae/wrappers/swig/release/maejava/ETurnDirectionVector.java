/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ETurnDirectionVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ETurnDirectionVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ETurnDirectionVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ETurnDirectionVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ETurnDirectionVector() {
    this(MaeJavaJNI.new_ETurnDirectionVector__SWIG_0(), true);
  }

  public ETurnDirectionVector(long n) {
    this(MaeJavaJNI.new_ETurnDirectionVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.ETurnDirectionVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.ETurnDirectionVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.ETurnDirectionVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.ETurnDirectionVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.ETurnDirectionVector_clear(swigCPtr, this);
  }

  public void pushBack(ETurnDirection x) {
    MaeJavaJNI.ETurnDirectionVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public ETurnDirection get(int i) {
    return ETurnDirection.swigToEnum(MaeJavaJNI.ETurnDirectionVector_get(swigCPtr, this, i));
  }

  public void set(int i, ETurnDirection val) {
    MaeJavaJNI.ETurnDirectionVector_set(swigCPtr, this, i, val.swigValue());
  }

}
