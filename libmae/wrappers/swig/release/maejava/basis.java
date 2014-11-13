/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class basis {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected basis(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(basis obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaejavaJNI.delete_basis(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public basis() {
    this(MaejavaJNI.new_basis__SWIG_0(), true);
  }

  public basis(vec3d position_vector, vec3d u, vec3d r, vec3d t) {
    this(MaejavaJNI.new_basis__SWIG_1(vec3d.getCPtr(position_vector), position_vector, vec3d.getCPtr(u), u, vec3d.getCPtr(r), r, vec3d.getCPtr(t), t), true);
  }

  public vec3d get_u() {
    long cPtr = MaejavaJNI.basis_get_u(swigCPtr, this);
    return (cPtr == 0) ? null : new vec3d(cPtr, true);
  }

  public vec3d get_r() {
    long cPtr = MaejavaJNI.basis_get_r(swigCPtr, this);
    return (cPtr == 0) ? null : new vec3d(cPtr, true);
  }

  public vec3d get_t() {
    long cPtr = MaejavaJNI.basis_get_t(swigCPtr, this);
    return (cPtr == 0) ? null : new vec3d(cPtr, true);
  }

  public vec3d get_position_vector() {
    long cPtr = MaejavaJNI.basis_get_position_vector(swigCPtr, this);
    return (cPtr == 0) ? null : new vec3d(cPtr, true);
  }

  public void set_u(vec3d u) {
    MaejavaJNI.basis_set_u(swigCPtr, this, vec3d.getCPtr(u), u);
  }

  public void set_r(vec3d r) {
    MaejavaJNI.basis_set_r(swigCPtr, this, vec3d.getCPtr(r), r);
  }

  public void set_t(vec3d t) {
    MaejavaJNI.basis_set_t(swigCPtr, this, vec3d.getCPtr(t), t);
  }

  public void set_position_vector(vec3d position_vector) {
    MaejavaJNI.basis_set_position_vector(swigCPtr, this, vec3d.getCPtr(position_vector), position_vector);
  }

  public String str() {
    return MaejavaJNI.basis_str(swigCPtr, this);
  }

}
