/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class BoneVector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected BoneVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(BoneVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_BoneVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public BoneVector() {
    this(MaeJavaJNI.new_BoneVector__SWIG_0(), true);
  }

  public BoneVector(long n) {
    this(MaeJavaJNI.new_BoneVector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.BoneVector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.BoneVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.BoneVector_reserve(swigCPtr, this, n);
  }

  public boolean empty() {
    return MaeJavaJNI.BoneVector_empty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.BoneVector_clear(swigCPtr, this);
  }

  public void pushBack(Bone x) {
    MaeJavaJNI.BoneVector_pushBack(swigCPtr, this, Bone.getCPtr(x), x);
  }

  public Bone get(int i) {
    return new Bone(MaeJavaJNI.BoneVector_get(swigCPtr, this, i), true);
  }

  public void set(int i, Bone val) {
    MaeJavaJNI.BoneVector_set(swigCPtr, this, i, Bone.getCPtr(val), val);
  }

}
