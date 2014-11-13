/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class room_direction extends i_movement {
  private long swigCPtr;
  private boolean swigCMemOwnDerived;

  protected room_direction(long cPtr, boolean cMemoryOwn) {
    super(MaejavaJNI.room_direction_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(room_direction obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        MaejavaJNI.delete_room_direction(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public room_direction(long measure, double beat, pin direction) {
    this(MaejavaJNI.new_room_direction(measure, beat, pin.getCPtr(direction), direction), true);
  }

  public int get_column() {
    return MaejavaJNI.room_direction_get_column(swigCPtr, this);
  }

  public long get_measure() {
    return MaejavaJNI.room_direction_get_measure(swigCPtr, this);
  }

  public double get_beat() {
    return MaejavaJNI.room_direction_get_beat(swigCPtr, this);
  }

  public double get_duration() {
    return MaejavaJNI.room_direction_get_duration(swigCPtr, this);
  }

  public pin get_direction() {
    long cPtr = MaejavaJNI.room_direction_get_direction(swigCPtr, this);
    return (cPtr == 0) ? null : new pin(cPtr, true);
  }

  public boolean equals(i_movement a) {
    return MaejavaJNI.room_direction_equals(swigCPtr, this, i_movement.getCPtr(a), a);
  }

  public boolean symbol_equals(i_movement a) {
    return MaejavaJNI.room_direction_symbol_equals(swigCPtr, this, i_movement.getCPtr(a), a);
  }

  public String xml(long indent, String namesp) {
    return MaejavaJNI.room_direction_xml__SWIG_0(swigCPtr, this, indent, namesp);
  }

  public String xml(long indent) {
    return MaejavaJNI.room_direction_xml__SWIG_1(swigCPtr, this, indent);
  }

  public String xml() {
    return MaejavaJNI.room_direction_xml__SWIG_2(swigCPtr, this);
  }

  public String svg(long im_width, long im_height, long max_column, long measures, long beats_per_measure) {
    return MaejavaJNI.room_direction_svg(swigCPtr, this, im_width, im_height, max_column, measures, beats_per_measure);
  }

  public i_movement recreate(int_int_map column_mapping, long measure, double beat, double duration) {
    long cPtr = MaejavaJNI.room_direction_recreate(swigCPtr, this, int_int_map.getCPtr(column_mapping), column_mapping, measure, beat, duration);
    return (cPtr == 0) ? null : new i_movement(cPtr, true);
  }

  public String str() {
    return MaejavaJNI.room_direction_str(swigCPtr, this);
  }

}
