/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ELimbC {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public ELimbC(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ELimbC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ELimbC(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(ELimb limb) {
    return MaeJavaJNI.ELimbC_str(limb.swigValue());
  }

  public static ELimbVector vec() {
    return new ELimbVector(MaeJavaJNI.ELimbC_vec(), true);
  }

  public static ELimb parse(String str) {
    return ELimb.swigToEnum(MaeJavaJNI.ELimbC_parse(str));
  }

  public ELimbC() {
    this(MaeJavaJNI.new_ELimbC(), true);
  }

}
