/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class e_time_unit_c {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_time_unit_c(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_time_unit_c obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_e_time_unit_c(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(e_time_unit unit) {
    return w_e_boneJNI.e_time_unit_c_str(unit.swigValue());
  }

  public static e_time_unit_vector vec() {
    return new e_time_unit_vector(w_e_boneJNI.e_time_unit_c_vec(), true);
  }

  public static e_time_unit parse(String str) {
    return e_time_unit.swigToEnum(w_e_boneJNI.e_time_unit_c_parse(str));
  }

  public e_time_unit_c() {
    this(w_e_boneJNI.new_e_time_unit_c(), true);
  }

}
