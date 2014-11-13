/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class fl_skeleton_laban_sequence_movement_controller {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected fl_skeleton_laban_sequence_movement_controller(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(fl_skeleton_laban_sequence_movement_controller obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_fl_skeleton_laban_sequence_movement_controller(swigCPtr);
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
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_change_ownership(this, swigCPtr, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_laban_sequence_movement_detector imd, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size, double framerate, boolean debug) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_0(fl_skeleton_laban_sequence_movement_detector.getCPtr(imd), imd, laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size, framerate, debug), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_laban_sequence_movement_detector imd, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size, double framerate) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_1(fl_skeleton_laban_sequence_movement_detector.getCPtr(imd), imd, laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size, framerate), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_laban_sequence_movement_detector imd, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_2(fl_skeleton_laban_sequence_movement_detector.getCPtr(imd), imd, laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_laban_sequence_movement_detector imd, laban_sequence_sequence_recognizer isr, bone_vector body_parts) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_3(fl_skeleton_laban_sequence_movement_detector.getCPtr(imd), imd, laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_pose_detector ipd, laban_sequence_sequence_generator isg, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size, double framerate, boolean debug) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_4(fl_skeleton_pose_detector.getCPtr(ipd), laban_sequence_sequence_generator.getCPtr(isg), laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size, framerate, debug), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_pose_detector ipd, laban_sequence_sequence_generator isg, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size, double framerate) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_5(fl_skeleton_pose_detector.getCPtr(ipd), laban_sequence_sequence_generator.getCPtr(isg), laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size, framerate), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_pose_detector ipd, laban_sequence_sequence_generator isg, laban_sequence_sequence_recognizer isr, bone_vector body_parts, int pose_buffer_size) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_6(fl_skeleton_pose_detector.getCPtr(ipd), laban_sequence_sequence_generator.getCPtr(isg), laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts, pose_buffer_size), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public fl_skeleton_laban_sequence_movement_controller(fl_skeleton_pose_detector ipd, laban_sequence_sequence_generator isg, laban_sequence_sequence_recognizer isr, bone_vector body_parts) {
    this(w_e_boneJNI.new_fl_skeleton_laban_sequence_movement_controller__SWIG_7(fl_skeleton_pose_detector.getCPtr(ipd), laban_sequence_sequence_generator.getCPtr(isg), laban_sequence_sequence_recognizer.getCPtr(isr), bone_vector.getCPtr(body_parts), body_parts), true);
    w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public void next_frame(int timestamp, fl_skeleton skeleton) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_next_frame(swigCPtr, this, timestamp, fl_skeleton.getCPtr(skeleton), skeleton); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_next_frameSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, timestamp, fl_skeleton.getCPtr(skeleton), skeleton);
  }

  public void register_sequence(laban_sequence sequence) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_register_sequence(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_register_sequenceSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence);
  }

  public void deregister_sequence(laban_sequence sequence) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_deregister_sequence(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_deregister_sequenceSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence);
  }

  public void clear_registered_sequences() {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_registered_sequences(swigCPtr, this); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_registered_sequencesSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
  }

  public void set_no_buffer_size_update(boolean updates) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_set_no_buffer_size_update(swigCPtr, this, updates); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_set_no_buffer_size_updateSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, updates);
  }

  public void clear_buffer() {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_buffer(swigCPtr, this); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_bufferSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
  }

  public laban_sequence get_current_sequence() {
    long cPtr = (getClass() == fl_skeleton_laban_sequence_movement_controller.class) ? w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_current_sequence(swigCPtr, this) : w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_current_sequenceSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
    return (cPtr == 0) ? null : new laban_sequence(cPtr, true);
  }

  public void add_listener(i_pose_listener pose_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listener__SWIG_0(swigCPtr, this, i_pose_listener.getCPtr(pose_listener), pose_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_0(swigCPtr, this, i_pose_listener.getCPtr(pose_listener), pose_listener);
  }

  public void remove_listener(i_pose_listener pose_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listener__SWIG_0(swigCPtr, this, i_pose_listener.getCPtr(pose_listener), pose_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_0(swigCPtr, this, i_pose_listener.getCPtr(pose_listener), pose_listener);
  }

  public void add_listener(laban_sequence_sequence_listener sequence_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listener__SWIG_1(swigCPtr, this, laban_sequence_sequence_listener.getCPtr(sequence_listener), sequence_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_1(swigCPtr, this, laban_sequence_sequence_listener.getCPtr(sequence_listener), sequence_listener);
  }

  public void remove_listener(laban_sequence_sequence_listener sequence_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listener__SWIG_1(swigCPtr, this, laban_sequence_sequence_listener.getCPtr(sequence_listener), sequence_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_1(swigCPtr, this, laban_sequence_sequence_listener.getCPtr(sequence_listener), sequence_listener);
  }

  public void add_listener(laban_sequence_recognition_listener recognition_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listener__SWIG_2(swigCPtr, this, laban_sequence_recognition_listener.getCPtr(recognition_listener), recognition_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_add_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_2(swigCPtr, this, laban_sequence_recognition_listener.getCPtr(recognition_listener), recognition_listener);
  }

  public void remove_listener(laban_sequence_recognition_listener recognition_listener) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listener__SWIG_2(swigCPtr, this, laban_sequence_recognition_listener.getCPtr(recognition_listener), recognition_listener); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_remove_listenerSwigExplicitfl_skeleton_laban_sequence_movement_controller__SWIG_2(swigCPtr, this, laban_sequence_recognition_listener.getCPtr(recognition_listener), recognition_listener);
  }

  public void clear_listeners() {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_listeners(swigCPtr, this); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_clear_listenersSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
  }

  public void notify_sequence_listeners(int timestamp, laban_sequence sequence) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_notify_sequence_listeners(swigCPtr, this, timestamp, laban_sequence.getCPtr(sequence), sequence); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_notify_sequence_listenersSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, timestamp, laban_sequence.getCPtr(sequence), sequence);
  }

  public void notify_recognition_listeners(int timestamp, laban_sequence_vector sequences) {
    if (getClass() == fl_skeleton_laban_sequence_movement_controller.class) w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_notify_recognition_listeners(swigCPtr, this, timestamp, laban_sequence_vector.getCPtr(sequences), sequences); else w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_notify_recognition_listenersSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this, timestamp, laban_sequence_vector.getCPtr(sequences), sequences);
  }

  public fl_skeleton_laban_sequence_movement_detector get_movement_detector() {
    long cPtr = (getClass() == fl_skeleton_laban_sequence_movement_controller.class) ? w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_movement_detector(swigCPtr, this) : w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_movement_detectorSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
    return (cPtr == 0) ? null : new fl_skeleton_laban_sequence_movement_detector(cPtr, true);
  }

  public laban_sequence_sequence_recognizer get_sequence_recognizer() {
    long cPtr = (getClass() == fl_skeleton_laban_sequence_movement_controller.class) ? w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_sequence_recognizer(swigCPtr, this) : w_e_boneJNI.fl_skeleton_laban_sequence_movement_controller_get_sequence_recognizerSwigExplicitfl_skeleton_laban_sequence_movement_controller(swigCPtr, this);
    return (cPtr == 0) ? null : new laban_sequence_sequence_recognizer(cPtr, true);
  }

}
