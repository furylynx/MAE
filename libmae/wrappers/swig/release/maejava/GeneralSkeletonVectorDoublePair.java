/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class GeneralSkeletonVectorDoublePair {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public GeneralSkeletonVectorDoublePair(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(GeneralSkeletonVectorDoublePair obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_GeneralSkeletonVectorDoublePair(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GeneralSkeletonVectorDoublePair() {
    this(MaeJavaJNI.new_GeneralSkeletonVectorDoublePair__SWIG_0(), true);
  }

  public GeneralSkeletonVectorDoublePair(GeneralSkeletonVector first, double second) {
    this(MaeJavaJNI.new_GeneralSkeletonVectorDoublePair__SWIG_1(GeneralSkeletonVector.getCPtr(first), first, second), true);
  }

  public GeneralSkeletonVectorDoublePair(GeneralSkeletonVectorDoublePair p) {
    this(MaeJavaJNI.new_GeneralSkeletonVectorDoublePair__SWIG_2(GeneralSkeletonVectorDoublePair.getCPtr(p), p), true);
  }

  public void setFirst(GeneralSkeletonVector value) {
    MaeJavaJNI.GeneralSkeletonVectorDoublePair_first_set(swigCPtr, this, GeneralSkeletonVector.getCPtr(value), value);
  }

  public GeneralSkeletonVector getFirst() {
    long cPtr = MaeJavaJNI.GeneralSkeletonVectorDoublePair_first_get(swigCPtr, this);
    return (cPtr == 0) ? null : new GeneralSkeletonVector(cPtr, false);
  }

  public void setSecond(double value) {
    MaeJavaJNI.GeneralSkeletonVectorDoublePair_second_set(swigCPtr, this, value);
  }

  public double getSecond() {
    return MaeJavaJNI.GeneralSkeletonVectorDoublePair_second_get(swigCPtr, this);
  }

}