/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class i_mov_vector {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected i_mov_vector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(i_mov_vector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaejavaJNI.delete_i_mov_vector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public i_mov_vector() {
    this(MaejavaJNI.new_i_mov_vector__SWIG_0(), true);
  }

  public i_mov_vector(long n) {
    this(MaejavaJNI.new_i_mov_vector__SWIG_1(n), true);
  }

  public long size() {
    return MaejavaJNI.i_mov_vector_size(swigCPtr, this);
  }

  public long capacity() {
    return MaejavaJNI.i_mov_vector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MaejavaJNI.i_mov_vector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return MaejavaJNI.i_mov_vector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    MaejavaJNI.i_mov_vector_clear(swigCPtr, this);
  }

  public void add(i_movement x) {
    MaejavaJNI.i_mov_vector_add(swigCPtr, this, i_movement.getCPtr(x), x);
  }

  public i_movement get(int i) {
    long cPtr = MaejavaJNI.i_mov_vector_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new i_movement(cPtr, true);
  }

  public void set(int i, i_movement val) {
    MaejavaJNI.i_mov_vector_set(swigCPtr, this, i, i_movement.getCPtr(val), val);
  }

}
