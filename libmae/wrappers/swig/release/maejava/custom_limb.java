/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class custom_limb extends i_limb {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected custom_limb(long cPtr, boolean cMemoryOwn) {
    super(MaejavaJNI.custom_limb_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(custom_limb obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaejavaJNI.delete_custom_limb(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public custom_limb(i_endpoint extremity, i_endpoint fixed_end) {
    this(MaejavaJNI.new_custom_limb__SWIG_0(i_endpoint.getCPtr(extremity), extremity, i_endpoint.getCPtr(fixed_end), fixed_end), true);
  }

  public custom_limb(i_endpoint extremity) {
    this(MaejavaJNI.new_custom_limb__SWIG_1(i_endpoint.getCPtr(extremity), extremity), true);
  }

  public i_endpoint get_fixed_end() {
    long cPtr = MaejavaJNI.custom_limb_get_fixed_end(swigCPtr, this);
    return (cPtr == 0) ? null : new i_endpoint(cPtr, true);
  }

  public i_endpoint get_extremity() {
    long cPtr = MaejavaJNI.custom_limb_get_extremity(swigCPtr, this);
    return (cPtr == 0) ? null : new i_endpoint(cPtr, true);
  }

  public String xml(long indent, String namesp) {
    return MaejavaJNI.custom_limb_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaejavaJNI.custom_limb_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaejavaJNI.custom_limb_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return MaejavaJNI.custom_limb_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return MaejavaJNI.custom_limb_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

  public boolean equals(i_part a) {
    return MaejavaJNI.custom_limb_equals__SWIG_0(swigCPtr, this, i_part.getCPtr(a), a);
  }

  public boolean equals(i_limb a) {
    return MaejavaJNI.custom_limb_equals__SWIG_1(swigCPtr, this, i_limb.getCPtr(a), a);
  }

}
