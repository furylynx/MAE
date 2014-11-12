/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class fl_skeleton extends general_skeleton {
  private long swigCPtr;

  protected fl_skeleton(long cPtr, boolean cMemoryOwn) {
    super(w_e_boneJNI.fl_skeleton_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(fl_skeleton obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_fl_skeleton(swigCPtr);
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
    w_e_boneJNI.fl_skeleton_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    w_e_boneJNI.fl_skeleton_change_ownership(this, swigCPtr, true);
  }

  public fl_skeleton() {
    this(w_e_boneJNI.new_fl_skeleton(), true);
    w_e_boneJNI.fl_skeleton_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public void set_torso_basis(basis torso_basis) {
    if (getClass() == fl_skeleton.class) w_e_boneJNI.fl_skeleton_set_torso_basis(swigCPtr, this, basis.getCPtr(torso_basis), torso_basis); else w_e_boneJNI.fl_skeleton_set_torso_basisSwigExplicitfl_skeleton(swigCPtr, this, basis.getCPtr(torso_basis), torso_basis);
  }

  public basis get_torso_basis() {
    long cPtr = (getClass() == fl_skeleton.class) ? w_e_boneJNI.fl_skeleton_get_torso_basis(swigCPtr, this) : w_e_boneJNI.fl_skeleton_get_torso_basisSwigExplicitfl_skeleton(swigCPtr, this);
    return (cPtr == 0) ? null : new basis(cPtr, true);
  }

  public void set_orig_skeleton(general_skeleton offset_skeleton) {
    if (getClass() == fl_skeleton.class) w_e_boneJNI.fl_skeleton_set_orig_skeleton(swigCPtr, this, general_skeleton.getCPtr(offset_skeleton), offset_skeleton); else w_e_boneJNI.fl_skeleton_set_orig_skeletonSwigExplicitfl_skeleton(swigCPtr, this, general_skeleton.getCPtr(offset_skeleton), offset_skeleton);
  }

  public general_skeleton get_orig_skeleton() {
    long cPtr = (getClass() == fl_skeleton.class) ? w_e_boneJNI.fl_skeleton_get_orig_skeleton(swigCPtr, this) : w_e_boneJNI.fl_skeleton_get_orig_skeletonSwigExplicitfl_skeleton(swigCPtr, this);
    return (cPtr == 0) ? null : new general_skeleton(cPtr, true);
  }

  public String str() {
    return (getClass() == fl_skeleton.class) ? w_e_boneJNI.fl_skeleton_str(swigCPtr, this) : w_e_boneJNI.fl_skeleton_strSwigExplicitfl_skeleton(swigCPtr, this);
  }

}
