/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class laban_sequence_sequence_generator {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected laban_sequence_sequence_generator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(laban_sequence_sequence_generator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_laban_sequence_sequence_generator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    w_e_boneJNI.laban_sequence_sequence_generator_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    w_e_boneJNI.laban_sequence_sequence_generator_change_ownership(this, swigCPtr, true);
  }

  public laban_sequence generate_sequence(double framerate, enriched_pose_list keyPoses, bone_vector bodyParts) {
    long cPtr = w_e_boneJNI.laban_sequence_sequence_generator_generate_sequence(swigCPtr, this, framerate, enriched_pose_list.getCPtr(keyPoses), keyPoses, bone_vector.getCPtr(bodyParts), bodyParts);
    return (cPtr == 0) ? null : new laban_sequence(cPtr, true);
  }

  public laban_sequence_sequence_generator() {
    this(w_e_boneJNI.new_laban_sequence_sequence_generator(), true);
    w_e_boneJNI.laban_sequence_sequence_generator_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
