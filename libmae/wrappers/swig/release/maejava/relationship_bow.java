/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class relationship_bow extends i_movement {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  public relationship_bow(long cPtr, boolean cMemoryOwn) {
    super(MaeJavaJNI.relationship_bow_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(relationship_bow obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaeJavaJNI.delete_relationship_bow(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public relationship_bow(e_relationship_type type, boolean grasping, boolean passing, boolean hold, long measure, double beat, relationship_endpoint left_endpoint, relationship_endpoint right_endpoint) {
    this(MaeJavaJNI.new_relationship_bow(type.swigValue(), grasping, passing, hold, measure, beat, relationship_endpoint.getCPtr(left_endpoint), left_endpoint, relationship_endpoint.getCPtr(right_endpoint), right_endpoint), true);
  }

  public e_relationship_type get_type() {
    return e_relationship_type.swigToEnum(MaeJavaJNI.relationship_bow_get_type(swigCPtr, this));
  }

  public boolean get_grasping() {
    return MaeJavaJNI.relationship_bow_get_grasping(swigCPtr, this);
  }

  public boolean get_passing() {
    return MaeJavaJNI.relationship_bow_get_passing(swigCPtr, this);
  }

  public boolean get_hold() {
    return MaeJavaJNI.relationship_bow_get_hold(swigCPtr, this);
  }

  public relationship_endpoint get_left_endpoint() {
    long cPtr = MaeJavaJNI.relationship_bow_get_left_endpoint(swigCPtr, this);
    return (cPtr == 0) ? null : new relationship_endpoint(cPtr, true);
  }

  public relationship_endpoint get_right_endpoint() {
    long cPtr = MaeJavaJNI.relationship_bow_get_right_endpoint(swigCPtr, this);
    return (cPtr == 0) ? null : new relationship_endpoint(cPtr, true);
  }

  public int get_column() {
    return MaeJavaJNI.relationship_bow_get_column(swigCPtr, this);
  }

  public long get_measure() {
    return MaeJavaJNI.relationship_bow_get_measure(swigCPtr, this);
  }

  public double get_beat() {
    return MaeJavaJNI.relationship_bow_get_beat(swigCPtr, this);
  }

  public double get_duration() {
    return MaeJavaJNI.relationship_bow_get_duration(swigCPtr, this);
  }

  public boolean equals(i_movement a) {
    return MaeJavaJNI.relationship_bow_equals(swigCPtr, this, i_movement.getCPtr(a), a);
  }

  public boolean symbol_equals(i_movement a) {
    return MaeJavaJNI.relationship_bow_symbol_equals(swigCPtr, this, i_movement.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return MaeJavaJNI.relationship_bow_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaeJavaJNI.relationship_bow_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaeJavaJNI.relationship_bow_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(long im_width, long im_height, long max_column, long measures, long beats_per_measure) {
    return MaeJavaJNI.relationship_bow_svg(swigCPtr, this, im_width, im_height, max_column, measures, beats_per_measure);
  }

  public i_movement recreate(int_int_map column_mapping, long measure, double beat, double duration) {
    long cPtr = MaeJavaJNI.relationship_bow_recreate(swigCPtr, this, int_int_map.getCPtr(column_mapping), column_mapping, measure, beat, duration);
    return (cPtr == 0) ? null : new i_movement(cPtr, true);
  }

  public String str() {
    return MaeJavaJNI.relationship_bow_str(swigCPtr, this);
  }

}
