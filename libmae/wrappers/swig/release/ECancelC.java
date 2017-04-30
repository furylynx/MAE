/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ECancelC {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public ECancelC(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ECancelC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ECancelC(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(ECancel cancel) {
    return MaeJavaJNI.ECancelC_str(cancel.swigValue());
  }

  public static ECancelVector vec() {
    return new ECancelVector(MaeJavaJNI.ECancelC_vec(), true);
  }

  public static ECancel parse(String str) {
    return ECancel.swigToEnum(MaeJavaJNI.ECancelC_parse(str));
  }

  public ECancelC() {
    this(MaeJavaJNI.new_ECancelC(), true);
  }

}
