/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class e_joint_c {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected e_joint_c(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(e_joint_c obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaejavaJNI.delete_e_joint_c(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(e_joint joint) {
    return MaejavaJNI.e_joint_c_str(joint.swigValue());
  }

  public static e_joint_vector vec() {
    return new e_joint_vector(MaejavaJNI.e_joint_c_vec(), true);
  }

  public static e_joint parse(String str) {
    return e_joint.swigToEnum(MaejavaJNI.e_joint_c_parse(str));
  }

  public e_joint_c() {
    this(MaejavaJNI.new_e_joint_c(), true);
  }

}
