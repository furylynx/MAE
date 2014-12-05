/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class GeneralSkeleton {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public GeneralSkeleton(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(GeneralSkeleton obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_GeneralSkeleton(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GeneralSkeleton() {
    this(MaeJavaJNI.new_GeneralSkeleton__SWIG_0(), true);
  }

  public GeneralSkeleton(Hierarchy hierarchy) {
    this(MaeJavaJNI.new_GeneralSkeleton__SWIG_1(Hierarchy.getCPtr(hierarchy), hierarchy), true);
  }

  public void setJoint(int body_part, GeneralJoint joint) {
    MaeJavaJNI.GeneralSkeleton_setJoint(swigCPtr, this, body_part, GeneralJoint.getCPtr(joint), joint);
  }

  public GeneralJoint getJoint(int body_part) {
    long cPtr = MaeJavaJNI.GeneralSkeleton_getJoint(swigCPtr, this, body_part);
    return (cPtr == 0) ? null : new GeneralJoint(cPtr, true);
  }

  public Hierarchy getHierarchy() {
    long cPtr = MaeJavaJNI.GeneralSkeleton_getHierarchy(swigCPtr, this);
    return (cPtr == 0) ? null : new Hierarchy(cPtr, true);
  }

  public void setHierarchy(Hierarchy hierarchy) {
    MaeJavaJNI.GeneralSkeleton_setHierarchy(swigCPtr, this, Hierarchy.getCPtr(hierarchy), hierarchy);
  }

  public void setTopDown(Bone top_down) {
    MaeJavaJNI.GeneralSkeleton_setTopDown(swigCPtr, this, Bone.getCPtr(top_down), top_down);
  }

  public Bone getTopDown() {
    long cPtr = MaeJavaJNI.GeneralSkeleton_getTopDown(swigCPtr, this);
    return (cPtr == 0) ? null : new Bone(cPtr, true);
  }

  public void setRightLeft(Bone right_left) {
    MaeJavaJNI.GeneralSkeleton_setRightLeft(swigCPtr, this, Bone.getCPtr(right_left), right_left);
  }

  public Bone getRightLeft() {
    long cPtr = MaeJavaJNI.GeneralSkeleton_getRightLeft(swigCPtr, this);
    return (cPtr == 0) ? null : new Bone(cPtr, true);
  }

  public void setWeight(Vec3d weight) {
    MaeJavaJNI.GeneralSkeleton_setWeight(swigCPtr, this, Vec3d.getCPtr(weight), weight);
  }

  public Vec3d getWeight() {
    long cPtr = MaeJavaJNI.GeneralSkeleton_getWeight(swigCPtr, this);
    return (cPtr == 0) ? null : new Vec3d(cPtr, true);
  }

  public String str() {
    return MaeJavaJNI.GeneralSkeleton_str(swigCPtr, this);
  }

  public String plyStr() {
    return MaeJavaJNI.GeneralSkeleton_plyStr(swigCPtr, this);
  }

  public void plyFile(String filename) {
    MaeJavaJNI.GeneralSkeleton_plyFile(swigCPtr, this, filename);
  }

}
