/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class VibrationSymbol extends ISymbol {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  public VibrationSymbol(long cPtr, boolean cMemoryOwn) {
    super(MaeJavaJNI.VibrationSymbol_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(VibrationSymbol obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaeJavaJNI.delete_VibrationSymbol(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public VibrationSymbol(Pin displacement1, Pin displacement2, IDynamicsSign dynamics) {
    this(MaeJavaJNI.new_VibrationSymbol__SWIG_0(Pin.getCPtr(displacement1), displacement1, Pin.getCPtr(displacement2), displacement2, IDynamicsSign.getCPtr(dynamics), dynamics), true);
  }

  public VibrationSymbol(Pin displacement1, Pin displacement2) {
    this(MaeJavaJNI.new_VibrationSymbol__SWIG_1(Pin.getCPtr(displacement1), displacement1, Pin.getCPtr(displacement2), displacement2), true);
  }

  public IDynamicsSign getDynamics() {
    long cPtr = MaeJavaJNI.VibrationSymbol_getDynamics(swigCPtr, this);
    return (cPtr == 0) ? null : new IDynamicsSign(cPtr, true);
  }

  public Pin getDisplacement1() {
    long cPtr = MaeJavaJNI.VibrationSymbol_getDisplacement1(swigCPtr, this);
    return (cPtr == 0) ? null : new Pin(cPtr, true);
  }

  public Pin getDisplacement2() {
    long cPtr = MaeJavaJNI.VibrationSymbol_getDisplacement2(swigCPtr, this);
    return (cPtr == 0) ? null : new Pin(cPtr, true);
  }

  public boolean equals(ISymbol a) {
    return MaeJavaJNI.VibrationSymbol_equals(swigCPtr, this, ISymbol.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return MaeJavaJNI.VibrationSymbol_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaeJavaJNI.VibrationSymbol_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaeJavaJNI.VibrationSymbol_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return MaeJavaJNI.VibrationSymbol_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return MaeJavaJNI.VibrationSymbol_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

  public String str() {
    return MaeJavaJNI.VibrationSymbol_str(swigCPtr, this);
  }

  public static VibrationSymbol castToVibrationSymbol(ISymbol base) {
    long cPtr = MaeJavaJNI.VibrationSymbol_castToVibrationSymbol(ISymbol.getCPtr(base), base);
    return (cPtr == 0) ? null : new VibrationSymbol(cPtr, true);
  }

}
