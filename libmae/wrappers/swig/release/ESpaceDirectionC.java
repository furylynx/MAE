/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class ESpaceDirectionC {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public ESpaceDirectionC(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ESpaceDirectionC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_ESpaceDirectionC(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String str(ESpaceDirection space_direction) {
    return MaeJavaJNI.ESpaceDirectionC_str(space_direction.swigValue());
  }

  public static ESpaceDirectionVector vec() {
    return new ESpaceDirectionVector(MaeJavaJNI.ESpaceDirectionC_vec(), true);
  }

  public static ESpaceDirection parse(String str) {
    return ESpaceDirection.swigToEnum(MaeJavaJNI.ESpaceDirectionC_parse(str));
  }

  public ESpaceDirectionC() {
    this(MaeJavaJNI.new_ESpaceDirectionC(), true);
  }

}
