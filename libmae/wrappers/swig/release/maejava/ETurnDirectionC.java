/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ETurnDirectionC {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ETurnDirectionC(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ETurnDirectionC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ETurnDirectionC(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(ETurnDirection turn) {
    return MaeJavaJNI.ETurnDirectionC_str(turn.swigValue());
  }

  public static ETurnDirectionVector vec() {
    return new ETurnDirectionVector(MaeJavaJNI.ETurnDirectionC_vec(), true);
  }

  public static ETurnDirection parse(String str) {
    return ETurnDirection.swigToEnum(MaeJavaJNI.ETurnDirectionC_parse(str));
  }

  public ETurnDirectionC() {
    this(MaeJavaJNI.new_ETurnDirectionC(), true);
  }

}