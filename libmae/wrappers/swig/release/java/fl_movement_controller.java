/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class fl_movement_controller extends fl_skel_laban_movement_controller {
  private long swigCPtr;

  protected fl_movement_controller(long cPtr, boolean cMemoryOwn) {
    super(w_e_boneJNI.fl_movement_controller_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(fl_movement_controller obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_fl_movement_controller(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public fl_movement_controller(long pose_buffer_size, double framerate, boolean debug) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_0(pose_buffer_size, framerate, debug), true);
  }

  public fl_movement_controller(long pose_buffer_size, double framerate) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_1(pose_buffer_size, framerate), true);
  }

  public fl_movement_controller(long pose_buffer_size) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_2(pose_buffer_size), true);
  }

  public fl_movement_controller() {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_3(), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size, long beats_per_measure, long beat_duration, e_time_unit time_unit, double framerate, boolean debug) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_4(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size, beats_per_measure, beat_duration, time_unit.swigValue(), framerate, debug), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size, long beats_per_measure, long beat_duration, e_time_unit time_unit, double framerate) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_5(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size, beats_per_measure, beat_duration, time_unit.swigValue(), framerate), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size, long beats_per_measure, long beat_duration, e_time_unit time_unit) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_6(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size, beats_per_measure, beat_duration, time_unit.swigValue()), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size, long beats_per_measure, long beat_duration) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_7(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size, beats_per_measure, beat_duration), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size, long beats_per_measure) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_8(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size, beats_per_measure), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions, long pose_buffer_size) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_9(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions, pose_buffer_size), true);
  }

  public fl_movement_controller(bone_vector body_parts, coldef_vector column_definitions) {
    this(w_e_boneJNI.new_fl_movement_controller__SWIG_10(bone_vector.getCPtr(body_parts), body_parts, coldef_vector.getCPtr(column_definitions), column_definitions), true);
  }

  public void next_frame(int timestamp, general_skeleton skeleton) {
    w_e_boneJNI.fl_movement_controller_next_frame(swigCPtr, this, timestamp, general_skeleton.getCPtr(skeleton), skeleton);
  }

  public void set_recognition_tolerance(double tolerance) {
    w_e_boneJNI.fl_movement_controller_set_recognition_tolerance(swigCPtr, this, tolerance);
  }

}
