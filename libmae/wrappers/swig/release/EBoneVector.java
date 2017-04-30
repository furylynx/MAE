/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class EBoneVector {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public EBoneVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EBoneVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_EBoneVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EBoneVector() {
    this(MaeJavaJNI.new_EBoneVector__SWIG_0(), true);
  }

  public EBoneVector(long n) {
    this(MaeJavaJNI.new_EBoneVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.EBoneVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.EBoneVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.EBoneVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.EBoneVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.EBoneVector_clear(swigCPtr, this);
  }

  public void pushBack(EBone x) {
    MaeJavaJNI.EBoneVector_pushBack(swigCPtr, this, x.swigValue());
  }

  public EBone get(int i) {
    return EBone.swigToEnum(MaeJavaJNI.EBoneVector_get(swigCPtr, this, i));
  }

  public void set(int i, EBone val) {
    MaeJavaJNI.EBoneVector_set(swigCPtr, this, i, val.swigValue());
  }

}
