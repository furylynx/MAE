/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class pin extends i_degree_sign {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected pin(long cPtr, boolean cMemoryOwn) {
    super(w_e_boneJNI.pin_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(pin obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        w_e_boneJNI.delete_pin(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    w_e_boneJNI.pin_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    w_e_boneJNI.pin_change_ownership(this, swigCPtr, true);
  }

  public pin(e_level level, int horizontal) {
    this(w_e_boneJNI.new_pin(level.swigValue(), horizontal), true);
    w_e_boneJNI.pin_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public e_level get_level() {
    return e_level.swigToEnum(w_e_boneJNI.pin_get_level(swigCPtr, this));
  }

  public int get_horizontal() {
    return w_e_boneJNI.pin_get_horizontal(swigCPtr, this);
  }

  public boolean equals(i_degree_sign a) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_equals(swigCPtr, this, i_degree_sign.getCPtr(a), a) : w_e_boneJNI.pin_equalsSwigExplicitpin(swigCPtr, this, i_degree_sign.getCPtr(a), a);
  }

  public String xml(long indent, String namesp, boolean print_type) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_xml__SWIG_0(swigCPtr, this, indent, namesp, print_type) : w_e_boneJNI.pin_xmlSwigExplicitpin__SWIG_0(swigCPtr, this, indent, namesp, print_type);
  }

  public String xml(long indent, String namesp) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_xml__SWIG_1(swigCPtr, this, indent, namesp) : w_e_boneJNI.pin_xmlSwigExplicitpin__SWIG_1(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_xml__SWIG_2(swigCPtr, this, indent) : w_e_boneJNI.pin_xmlSwigExplicitpin__SWIG_2(swigCPtr, this, indent);
  }

  public String xml() {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_xml__SWIG_3(swigCPtr, this) : w_e_boneJNI.pin_xmlSwigExplicitpin__SWIG_3(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left) : w_e_boneJNI.pin_svgSwigExplicitpin__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return (getClass() == pin.class) ? w_e_boneJNI.pin_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height) : w_e_boneJNI.pin_svgSwigExplicitpin__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

}
