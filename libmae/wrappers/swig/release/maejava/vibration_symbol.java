/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class vibration_symbol extends i_symbol {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected vibration_symbol(long cPtr, boolean cMemoryOwn) {
    super(w_e_boneJNI.vibration_symbol_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vibration_symbol obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        w_e_boneJNI.delete_vibration_symbol(swigCPtr);
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
    w_e_boneJNI.vibration_symbol_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    w_e_boneJNI.vibration_symbol_change_ownership(this, swigCPtr, true);
  }

  public vibration_symbol(pin displacement1, pin displacement2, i_dynamics_sign dynamics) {
    this(w_e_boneJNI.new_vibration_symbol__SWIG_0(pin.getCPtr(displacement1), displacement1, pin.getCPtr(displacement2), displacement2, i_dynamics_sign.getCPtr(dynamics), dynamics), true);
    w_e_boneJNI.vibration_symbol_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public vibration_symbol(pin displacement1, pin displacement2) {
    this(w_e_boneJNI.new_vibration_symbol__SWIG_1(pin.getCPtr(displacement1), displacement1, pin.getCPtr(displacement2), displacement2), true);
    w_e_boneJNI.vibration_symbol_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public i_dynamics_sign get_dynamics() {
    long cPtr = w_e_boneJNI.vibration_symbol_get_dynamics(swigCPtr, this);
    return (cPtr == 0) ? null : new i_dynamics_sign(cPtr, true);
  }

  public pin get_displacement1() {
    long cPtr = w_e_boneJNI.vibration_symbol_get_displacement1(swigCPtr, this);
    return (cPtr == 0) ? null : new pin(cPtr, true);
  }

  public pin get_displacement2() {
    long cPtr = w_e_boneJNI.vibration_symbol_get_displacement2(swigCPtr, this);
    return (cPtr == 0) ? null : new pin(cPtr, true);
  }

  public boolean equals(i_symbol a) {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_equals(swigCPtr, this, i_symbol.getCPtr(a), a) : w_e_boneJNI.vibration_symbol_equalsSwigExplicitvibration_symbol(swigCPtr, this, i_symbol.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_xml__SWIG_0(swigCPtr, this, indent, namesp) : w_e_boneJNI.vibration_symbol_xmlSwigExplicitvibration_symbol__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_xml__SWIG_1(swigCPtr, this, indent) : w_e_boneJNI.vibration_symbol_xmlSwigExplicitvibration_symbol__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_xml__SWIG_2(swigCPtr, this) : w_e_boneJNI.vibration_symbol_xmlSwigExplicitvibration_symbol__SWIG_2(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left) : w_e_boneJNI.vibration_symbol_svgSwigExplicitvibration_symbol__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height) : w_e_boneJNI.vibration_symbol_svgSwigExplicitvibration_symbol__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

  public String str() {
    return (getClass() == vibration_symbol.class) ? w_e_boneJNI.vibration_symbol_str(swigCPtr, this) : w_e_boneJNI.vibration_symbol_strSwigExplicitvibration_symbol(swigCPtr, this);
  }

}
