/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class int_list {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected int_list(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(int_list obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaejavaJNI.delete_int_list(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public int_list() {
    this(MaejavaJNI.new_int_list(), true);
  }

  public long size() {
    return MaejavaJNI.int_list_size(swigCPtr, this);
  }

  public boolean isEmpty() {
    return MaejavaJNI.int_list_isEmpty(swigCPtr, this);
  }

  public void clear() {
    MaejavaJNI.int_list_clear(swigCPtr, this);
  }

  public void add(int x) {
    MaejavaJNI.int_list_add(swigCPtr, this, x);
  }

  public int get(int i) {
    return MaejavaJNI.int_list_get(swigCPtr, this, i);
  }

}
