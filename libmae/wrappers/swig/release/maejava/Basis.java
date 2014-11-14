/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class Basis {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Basis(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Basis obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_Basis(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Basis() {
    this(MaeJavaJNI.new_Basis__SWIG_0(), true);
  }

  public Basis(Vec3d position_vector, Vec3d u, Vec3d r, Vec3d t) {
    this(MaeJavaJNI.new_Basis__SWIG_1(Vec3d.getCPtr(position_vector), position_vector, Vec3d.getCPtr(u), u, Vec3d.getCPtr(r), r, Vec3d.getCPtr(t), t), true);
  }

  public Vec3d getU() {
    long cPtr = MaeJavaJNI.Basis_getU(swigCPtr, this);
    return (cPtr == 0) ? null : new Vec3d(cPtr, true);
  }

  public Vec3d getR() {
    long cPtr = MaeJavaJNI.Basis_getR(swigCPtr, this);
    return (cPtr == 0) ? null : new Vec3d(cPtr, true);
  }

  public Vec3d getT() {
    long cPtr = MaeJavaJNI.Basis_getT(swigCPtr, this);
    return (cPtr == 0) ? null : new Vec3d(cPtr, true);
  }

  public Vec3d getPositionVector() {
    long cPtr = MaeJavaJNI.Basis_getPositionVector(swigCPtr, this);
    return (cPtr == 0) ? null : new Vec3d(cPtr, true);
  }

  public void setU(Vec3d u) {
    MaeJavaJNI.Basis_setU(swigCPtr, this, Vec3d.getCPtr(u), u);
  }

  public void setR(Vec3d r) {
    MaeJavaJNI.Basis_setR(swigCPtr, this, Vec3d.getCPtr(r), r);
  }

  public void setT(Vec3d t) {
    MaeJavaJNI.Basis_setT(swigCPtr, this, Vec3d.getCPtr(t), t);
  }

  public void setPositionVector(Vec3d position_vector) {
    MaeJavaJNI.Basis_setPositionVector(swigCPtr, this, Vec3d.getCPtr(position_vector), position_vector);
  }

  public String str() {
    return MaeJavaJNI.Basis_str(swigCPtr, this);
  }

}
