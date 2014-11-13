/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class joint_part extends i_endpoint {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected joint_part(long cPtr, boolean cMemoryOwn) {
    super(MaejavaJNI.joint_part_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(joint_part obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaejavaJNI.delete_joint_part(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public joint_part(e_joint joint) {
    this(MaejavaJNI.new_joint_part(joint.swigValue()), true);
  }

  public e_joint get_joint() {
    return e_joint.swigToEnum(MaejavaJNI.joint_part_get_joint(swigCPtr, this));
  }

  public String xml(long indent, String namesp) {
    return MaejavaJNI.joint_part_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaejavaJNI.joint_part_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaejavaJNI.joint_part_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(String identifier, double posx, double posy, double width, double height, boolean left) {
    return MaejavaJNI.joint_part_svg__SWIG_0(swigCPtr, this, identifier, posx, posy, width, height, left);
  }

  public String svg(String identifier, double posx, double posy, double width, double height) {
    return MaejavaJNI.joint_part_svg__SWIG_1(swigCPtr, this, identifier, posx, posy, width, height);
  }

  public i_endpoint get_fixed_end() {
    long cPtr = MaejavaJNI.joint_part_get_fixed_end(swigCPtr, this);
    return (cPtr == 0) ? null : new i_endpoint(cPtr, true);
  }

  public boolean equals(i_part a) {
    return MaejavaJNI.joint_part_equals__SWIG_0(swigCPtr, this, i_part.getCPtr(a), a);
  }

  public boolean equals(i_endpoint a) {
    return MaejavaJNI.joint_part_equals__SWIG_1(swigCPtr, this, i_endpoint.getCPtr(a), a);
  }

}
