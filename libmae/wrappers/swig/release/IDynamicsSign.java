/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class IDynamicsSign {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public IDynamicsSign(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IDynamicsSign obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_IDynamicsSign(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public boolean equals(IDynamicsSign a) {
    return MaeJavaJNI.IDynamicsSign_equals(swigCPtr, this, IDynamicsSign.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return MaeJavaJNI.IDynamicsSign_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaeJavaJNI.IDynamicsSign_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaeJavaJNI.IDynamicsSign_xml__SWIG_2(swigCPtr, this);
  }

}
