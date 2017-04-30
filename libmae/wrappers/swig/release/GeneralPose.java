/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class GeneralPose {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public GeneralPose(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(GeneralPose obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_GeneralPose(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GeneralPose() {
    this(MaeJavaJNI.new_GeneralPose(), true);
  }

  public void setDirection(int body_part, int direction) {
    MaeJavaJNI.GeneralPose_setDirection(swigCPtr, this, body_part, direction);
  }

  public int getDirection(int body_part) {
    return MaeJavaJNI.GeneralPose_getDirection(swigCPtr, this, body_part);
  }

  public void setDistance(int body_part, int direction, double distance) {
    MaeJavaJNI.GeneralPose_setDistance(swigCPtr, this, body_part, direction, distance);
  }

  public double getDistance(int body_part, int direction) {
    return MaeJavaJNI.GeneralPose_getDistance(swigCPtr, this, body_part, direction);
  }

  public void setRotation(int body_part, double rotation) {
    MaeJavaJNI.GeneralPose_setRotation(swigCPtr, this, body_part, rotation);
  }

  public double getRotation(int body_part) {
    return MaeJavaJNI.GeneralPose_getRotation(swigCPtr, this, body_part);
  }

  public IntList getBodyParts() {
    return new IntList(MaeJavaJNI.GeneralPose_getBodyParts(swigCPtr, this), true);
  }

  public IntList getDirections() {
    return new IntList(MaeJavaJNI.GeneralPose_getDirections(swigCPtr, this), true);
  }

}
