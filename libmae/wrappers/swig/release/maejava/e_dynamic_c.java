/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class e_dynamic_c {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_dynamic_c(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_dynamic_c obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_e_dynamic_c(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(e_dynamic dynamic) {
    return w_e_boneJNI.e_dynamic_c_str(dynamic.swigValue());
  }

  public static e_dynamic_vector vec() {
    return new e_dynamic_vector(w_e_boneJNI.e_dynamic_c_vec(), true);
  }

  public static e_dynamic parse(String str) {
    return e_dynamic.swigToEnum(w_e_boneJNI.e_dynamic_c_parse(str));
  }

  public e_dynamic_c() {
    this(w_e_boneJNI.new_e_dynamic_c(), true);
  }

}
