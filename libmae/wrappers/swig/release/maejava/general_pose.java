/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class general_pose {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public general_pose(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(general_pose obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_general_pose(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public general_pose() {
    this(MaeJavaJNI.new_general_pose(), true);
  }

  public void set_direction(int body_part, int direction) {
    MaeJavaJNI.general_pose_set_direction(swigCPtr, this, body_part, direction);
  }

  public int get_direction(int body_part) {
    return MaeJavaJNI.general_pose_get_direction(swigCPtr, this, body_part);
  }

  public void set_distance(int body_part, int direction, double distance) {
    MaeJavaJNI.general_pose_set_distance(swigCPtr, this, body_part, direction, distance);
  }

  public double get_distance(int body_part, int direction) {
    return MaeJavaJNI.general_pose_get_distance(swigCPtr, this, body_part, direction);
  }

  public void set_rotation(int body_part, double rotation) {
    MaeJavaJNI.general_pose_set_rotation(swigCPtr, this, body_part, rotation);
  }

  public double get_rotation(int body_part) {
    return MaeJavaJNI.general_pose_get_rotation(swigCPtr, this, body_part);
  }

  public int_list get_body_parts() {
    return new int_list(MaeJavaJNI.general_pose_get_body_parts(swigCPtr, this), true);
  }

  public int_list get_directions() {
    return new int_list(MaeJavaJNI.general_pose_get_directions(swigCPtr, this), true);
  }

}
