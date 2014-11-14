/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class laban_sequence_sequence_recognizer {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public laban_sequence_sequence_recognizer(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(laban_sequence_sequence_recognizer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaejavaJNI.delete_laban_sequence_sequence_recognizer(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void register_sequence(laban_sequence sequence) {
    MaejavaJNI.laban_sequence_sequence_recognizer_register_sequence(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence);
  }

  public boolean deregister_sequence(laban_sequence sequence) {
    return MaejavaJNI.laban_sequence_sequence_recognizer_deregister_sequence__SWIG_0(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence);
  }

  public boolean deregister_sequence(long list_index) {
    return MaejavaJNI.laban_sequence_sequence_recognizer_deregister_sequence__SWIG_1(swigCPtr, this, list_index);
  }

  public void clear_registered_sequences() {
    MaejavaJNI.laban_sequence_sequence_recognizer_clear_registered_sequences(swigCPtr, this);
  }

  public int get_sequence_length(laban_sequence sequence) {
    return MaejavaJNI.laban_sequence_sequence_recognizer_get_sequence_length(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence);
  }

  public laban_sequence_vector recognize_sequence(laban_sequence sequence, bone_vector body_parts) {
    return new laban_sequence_vector(MaejavaJNI.laban_sequence_sequence_recognizer_recognize_sequence(swigCPtr, this, laban_sequence.getCPtr(sequence), sequence, bone_vector.getCPtr(body_parts), body_parts), true);
  }

}
