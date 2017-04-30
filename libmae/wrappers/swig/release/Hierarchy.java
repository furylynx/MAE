/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class Hierarchy {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Hierarchy(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Hierarchy obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_Hierarchy(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Hierarchy() {
    this(MaeJavaJNI.new_Hierarchy__SWIG_0(), true);
  }

  public Hierarchy(HierarchyElement root) {
    this(MaeJavaJNI.new_Hierarchy__SWIG_1(HierarchyElement.getCPtr(root), root), true);
  }

  public HierarchyElement getRoot() {
    long cPtr = MaeJavaJNI.Hierarchy_getRoot(swigCPtr, this);
    return (cPtr == 0) ? null : new HierarchyElement(cPtr, true);
  }

  public void setRoot(HierarchyElement root) {
    MaeJavaJNI.Hierarchy_setRoot(swigCPtr, this, HierarchyElement.getCPtr(root), root);
  }

  public HierarchyElementVector getElementSequence() {
    return new HierarchyElementVector(MaeJavaJNI.Hierarchy_getElementSequence(swigCPtr, this), true);
  }

  public HierarchyElementVector getSortedElementSequence() {
    return new HierarchyElementVector(MaeJavaJNI.Hierarchy_getSortedElementSequence(swigCPtr, this), true);
  }

  public HierarchyElement at(int element_id) {
    long cPtr = MaeJavaJNI.Hierarchy_at(swigCPtr, this, element_id);
    return (cPtr == 0) ? null : new HierarchyElement(cPtr, true);
  }

  public static boolean compareElements(HierarchyElement lhs, HierarchyElement rhs) {
    return MaeJavaJNI.Hierarchy_compareElements(HierarchyElement.getCPtr(lhs), lhs, HierarchyElement.getCPtr(rhs), rhs);
  }

  public String str() {
    return MaeJavaJNI.Hierarchy_str(swigCPtr, this);
  }

  public static Hierarchy defaultHierarchy() {
    long cPtr = MaeJavaJNI.Hierarchy_defaultHierarchy();
    return (cPtr == 0) ? null : new Hierarchy(cPtr, true);
  }

  public static Hierarchy defaultHandHierarchy(boolean is_left) {
    long cPtr = MaeJavaJNI.Hierarchy_defaultHandHierarchy(is_left);
    return (cPtr == 0) ? null : new Hierarchy(cPtr, true);
  }

  public static Hierarchy defaultKinectHierarchy() {
    long cPtr = MaeJavaJNI.Hierarchy_defaultKinectHierarchy();
    return (cPtr == 0) ? null : new Hierarchy(cPtr, true);
  }

}
