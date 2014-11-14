/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class e_limb_side_vector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_limb_side_vector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_limb_side_vector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_e_limb_side_vector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public e_limb_side_vector() {
    this(MaeJavaJNI.new_e_limb_side_vector__SWIG_0(), true);
  }

  public e_limb_side_vector(long n) {
    this(MaeJavaJNI.new_e_limb_side_vector__SWIG_1(n), true);
  }

  public long size() {
    return MaeJavaJNI.e_limb_side_vector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaeJavaJNI.e_limb_side_vector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaeJavaJNI.e_limb_side_vector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return MaeJavaJNI.e_limb_side_vector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    MaeJavaJNI.e_limb_side_vector_clear(swigCPtr, this);
  }

  public void add(e_limb_side x) {
    MaeJavaJNI.e_limb_side_vector_add(swigCPtr, this, x.swigValue());
  }

  public e_limb_side get(int i) {
    return e_limb_side.swigToEnum(MaeJavaJNI.e_limb_side_vector_get(swigCPtr, this, i));
  }

  public void set(int i, e_limb_side val) {
    MaeJavaJNI.e_limb_side_vector_set(swigCPtr, this, i, val.swigValue());
  }

}
