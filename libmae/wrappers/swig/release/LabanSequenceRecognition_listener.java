/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class LabanSequenceRecognition_listener {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public LabanSequenceRecognition_listener(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(LabanSequenceRecognition_listener obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_LabanSequenceRecognition_listener(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void onRecognition(java.math.BigInteger timestamp, LabanSequenceVector sequences) {
    MaeJavaJNI.LabanSequenceRecognition_listener_onRecognition__SWIG_0(swigCPtr, this, timestamp, LabanSequenceVector.getCPtr(sequences), sequences);
  }

  public void onRecognition(java.math.BigInteger timestamp, StringVector title) {
    MaeJavaJNI.LabanSequenceRecognition_listener_onRecognition__SWIG_1(swigCPtr, this, timestamp, StringVector.getCPtr(title), title);
  }

}
