/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class LabanSequenceSequenceListener {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public LabanSequenceSequenceListener(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(LabanSequenceSequenceListener obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_LabanSequenceSequenceListener(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void onSequence(java.math.BigInteger timestamp, LabanSequence sequence) {
    MaeJavaJNI.LabanSequenceSequenceListener_onSequence(swigCPtr, this, timestamp, LabanSequence.getCPtr(sequence), sequence);
  }

}
