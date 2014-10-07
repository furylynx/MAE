/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class e_bone_vector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_bone_vector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_bone_vector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_e_bone_vector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public e_bone_vector() {
    this(w_e_boneJNI.new_e_bone_vector__SWIG_0(), true);
  }

  public e_bone_vector(long n) {
    this(w_e_boneJNI.new_e_bone_vector__SWIG_1(n), true);
  }

  public long size() {
    return w_e_boneJNI.e_bone_vector_size(swigCPtr, this);
  }

  public long capacity() {
    return w_e_boneJNI.e_bone_vector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    w_e_boneJNI.e_bone_vector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return w_e_boneJNI.e_bone_vector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    w_e_boneJNI.e_bone_vector_clear(swigCPtr, this);
  }

  public void add(int x) {
    w_e_boneJNI.e_bone_vector_add(swigCPtr, this, x);
  }

  public int get(int i) {
    return w_e_boneJNI.e_bone_vector_get(swigCPtr, this, i);
  }

  public void set(int i, int val) {
    w_e_boneJNI.e_bone_vector_set(swigCPtr, this, i, val);
  }

}
