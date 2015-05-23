/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class LabanSequenceSequenceRecognizer {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public LabanSequenceSequenceRecognizer(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(LabanSequenceSequenceRecognizer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_LabanSequenceSequenceRecognizer(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void registerSequence(LabanSequence sequence) {
    MaeJavaJNI.LabanSequenceSequenceRecognizer_registerSequence(swigCPtr, this, LabanSequence.getCPtr(sequence), sequence);
  }

  public boolean deregisterSequence(LabanSequence sequence) {
    return MaeJavaJNI.LabanSequenceSequenceRecognizer_deregisterSequence__SWIG_0(swigCPtr, this, LabanSequence.getCPtr(sequence), sequence);
  }

  public boolean deregisterSequence(long list_index) {
    return MaeJavaJNI.LabanSequenceSequenceRecognizer_deregisterSequence__SWIG_1(swigCPtr, this, list_index);
  }

  public void clearRegisteredSequences() {
    MaeJavaJNI.LabanSequenceSequenceRecognizer_clearRegisteredSequences(swigCPtr, this);
  }

  public void clearBuffer() {
    MaeJavaJNI.LabanSequenceSequenceRecognizer_clearBuffer(swigCPtr, this);
  }

  public int getSequenceLength(LabanSequence sequence) {
    return MaeJavaJNI.LabanSequenceSequenceRecognizer_getSequenceLength(swigCPtr, this, LabanSequence.getCPtr(sequence), sequence);
  }

  public LabanSequenceVector recognizeSequence(double framerate, LabanSequence sequence, BoneVector body_parts) {
    return new LabanSequenceVector(MaeJavaJNI.LabanSequenceSequenceRecognizer_recognizeSequence(swigCPtr, this, framerate, LabanSequence.getCPtr(sequence), sequence, BoneVector.getCPtr(body_parts), body_parts), true);
  }

}
