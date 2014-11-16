/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class EAreaC {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EAreaC(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EAreaC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_EAreaC(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(EArea area) {
    return MaeJavaJNI.EAreaC_str(area.swigValue());
  }

  public static EAreaVector vec() {
    return new EAreaVector(MaeJavaJNI.EAreaC_vec(), true);
  }

  public static EArea parse(String str) {
    return EArea.swigToEnum(MaeJavaJNI.EAreaC_parse(str));
  }

  public EAreaC() {
    this(MaeJavaJNI.new_EAreaC(), true);
  }

}
