/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class dynamic_sign extends i_dynamics_sign {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected dynamic_sign(long cPtr, boolean cMemoryOwn) {
    super(MaejavaJNI.dynamic_sign_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(dynamic_sign obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaejavaJNI.delete_dynamic_sign(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public dynamic_sign(e_dynamic dynamic) {
    this(MaejavaJNI.new_dynamic_sign(dynamic.swigValue()), true);
  }

  public e_dynamic get_dynamic() {
    return e_dynamic.swigToEnum(MaejavaJNI.dynamic_sign_get_dynamic(swigCPtr, this));
  }

  public boolean equals(i_dynamics_sign a) {
    return MaejavaJNI.dynamic_sign_equals(swigCPtr, this, i_dynamics_sign.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return MaejavaJNI.dynamic_sign_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaejavaJNI.dynamic_sign_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaejavaJNI.dynamic_sign_xml__SWIG_2(swigCPtr, this);
  }

}
