/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class digit_part extends i_endpoint {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  public digit_part(long cPtr, boolean cMemoryOwn) {
    super(MaejavaJNI.digit_part_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(digit_part obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaejavaJNI.delete_digit_part(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public digit_part(e_digit digit, long knuckle) {
    this(MaejavaJNI.new_digit_part(digit.swigValue(), knuckle), true);
  }

  public e_digit get_digit() {
    return e_digit.swigToEnum(MaejavaJNI.digit_part_get_digit(swigCPtr, this));
  }

  public long get_knuckle() {
    return MaejavaJNI.digit_part_get_knuckle(swigCPtr, this);
  }

  public String xml(long indent, String namesp) {
    return MaejavaJNI.digit_part_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaejavaJNI.digit_part_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaejavaJNI.digit_part_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return MaejavaJNI.digit_part_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return MaejavaJNI.digit_part_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

  public i_endpoint get_fixed_end() {
    long cPtr = MaejavaJNI.digit_part_get_fixed_end(swigCPtr, this);
    return (cPtr == 0) ? null : new i_endpoint(cPtr, true);
  }

  public boolean equals(i_part a) {
    return MaejavaJNI.digit_part_equals__SWIG_0(swigCPtr, this, i_part.getCPtr(a), a);
  }

  public boolean equals(i_endpoint a) {
    return MaejavaJNI.digit_part_equals__SWIG_1(swigCPtr, this, i_endpoint.getCPtr(a), a);
  }

}
