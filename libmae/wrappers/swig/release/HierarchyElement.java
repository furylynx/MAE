/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class HierarchyElement {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public HierarchyElement(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(HierarchyElement obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_HierarchyElement(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public HierarchyElement(int id, String name, boolean base_joint, boolean dummy) {
    this(MaeJavaJNI.new_HierarchyElement__SWIG_0(id, name, base_joint, dummy), true);
  }

  public HierarchyElement(int id, String name, boolean base_joint) {
    this(MaeJavaJNI.new_HierarchyElement__SWIG_1(id, name, base_joint), true);
  }

  public HierarchyElement(int id, String name) {
    this(MaeJavaJNI.new_HierarchyElement__SWIG_2(id, name), true);
  }

  public int getId() {
    return MaeJavaJNI.HierarchyElement_getId(swigCPtr, this);
  }

  public String getName() {
    return MaeJavaJNI.HierarchyElement_getName(swigCPtr, this);
  }

  public boolean isTorsoJoint() {
    return MaeJavaJNI.HierarchyElement_isTorsoJoint(swigCPtr, this);
  }

  public boolean isBaseJoint() {
    return MaeJavaJNI.HierarchyElement_isBaseJoint(swigCPtr, this);
  }

  public boolean isDummy() {
    return MaeJavaJNI.HierarchyElement_isDummy(swigCPtr, this);
  }

  public HierarchyElement getParent() {
    long cPtr = MaeJavaJNI.HierarchyElement_getParent(swigCPtr, this);
    return (cPtr == 0) ? null : new HierarchyElement(cPtr, true);
  }

  public boolean isParent() {
    return MaeJavaJNI.HierarchyElement_isParent(swigCPtr, this);
  }

  public boolean isParentOf(int element_id) {
    return MaeJavaJNI.HierarchyElement_isParentOf(swigCPtr, this, element_id);
  }

  public HierarchyElementVector getChildren() {
    return new HierarchyElementVector(MaeJavaJNI.HierarchyElement_getChildren(swigCPtr, this), true);
  }

  public void pushFront(HierarchyElement child, boolean fix_child) {
    MaeJavaJNI.HierarchyElement_pushFront__SWIG_0(swigCPtr, this, HierarchyElement.getCPtr(child), child, fix_child);
  }

  public void pushFront(HierarchyElement child) {
    MaeJavaJNI.HierarchyElement_pushFront__SWIG_1(swigCPtr, this, HierarchyElement.getCPtr(child), child);
  }

  public void insert(long pos, HierarchyElement child, boolean fix_child) {
    MaeJavaJNI.HierarchyElement_insert__SWIG_0(swigCPtr, this, pos, HierarchyElement.getCPtr(child), child, fix_child);
  }

  public void insert(long pos, HierarchyElement child) {
    MaeJavaJNI.HierarchyElement_insert__SWIG_1(swigCPtr, this, pos, HierarchyElement.getCPtr(child), child);
  }

  public void pushBack(HierarchyElement child, boolean fix_child) {
    MaeJavaJNI.HierarchyElement_pushBack__SWIG_0(swigCPtr, this, HierarchyElement.getCPtr(child), child, fix_child);
  }

  public void pushBack(HierarchyElement child) {
    MaeJavaJNI.HierarchyElement_pushBack__SWIG_1(swigCPtr, this, HierarchyElement.getCPtr(child), child);
  }

  public void erase(int element_id, boolean fix_child) {
    MaeJavaJNI.HierarchyElement_erase__SWIG_0(swigCPtr, this, element_id, fix_child);
  }

  public void erase(int element_id) {
    MaeJavaJNI.HierarchyElement_erase__SWIG_1(swigCPtr, this, element_id);
  }

  public void eraseAt(long i, boolean fix_child) {
    MaeJavaJNI.HierarchyElement_eraseAt__SWIG_0(swigCPtr, this, i, fix_child);
  }

  public void eraseAt(long i) {
    MaeJavaJNI.HierarchyElement_eraseAt__SWIG_1(swigCPtr, this, i);
  }

  public void clear(boolean fix_child) {
    MaeJavaJNI.HierarchyElement_clear__SWIG_0(swigCPtr, this, fix_child);
  }

  public void clear() {
    MaeJavaJNI.HierarchyElement_clear__SWIG_1(swigCPtr, this);
  }

  public HierarchyElementVector getElementSequence() {
    return new HierarchyElementVector(MaeJavaJNI.HierarchyElement_getElementSequence(swigCPtr, this), true);
  }

  public String str(int offset) {
    return MaeJavaJNI.HierarchyElement_str__SWIG_0(swigCPtr, this, offset);
  }

  public String str() {
    return MaeJavaJNI.HierarchyElement_str__SWIG_1(swigCPtr, this);
  }

}
