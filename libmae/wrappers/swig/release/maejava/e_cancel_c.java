/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class e_cancel_c {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_cancel_c(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_cancel_c obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_e_cancel_c(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(e_cancel cancel) {
    return w_e_boneJNI.e_cancel_c_str(cancel.swigValue());
  }

  public static e_cancel_vector vec() {
    return new e_cancel_vector(w_e_boneJNI.e_cancel_c_vec(), true);
  }

  public static e_cancel parse(String str) {
    return e_cancel.swigToEnum(w_e_boneJNI.e_cancel_c_parse(str));
  }

  public e_cancel_c() {
    this(w_e_boneJNI.new_e_cancel_c(), true);
  }

}
