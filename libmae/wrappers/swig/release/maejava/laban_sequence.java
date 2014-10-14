/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class laban_sequence {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected laban_sequence(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(laban_sequence obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        w_e_boneJNI.delete_laban_sequence(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public laban_sequence() {
    this(w_e_boneJNI.new_laban_sequence__SWIG_0(), true);
  }

  public laban_sequence(String title, String author, long measures, e_time_unit time_unit, long beat_duration, long beats) {
    this(w_e_boneJNI.new_laban_sequence__SWIG_1(title, author, measures, time_unit.swigValue(), beat_duration, beats), true);
  }

  public String get_version() {
    return w_e_boneJNI.laban_sequence_get_version(swigCPtr, this);
  }

  public void set_authors(string_vector authors) {
    w_e_boneJNI.laban_sequence_set_authors(swigCPtr, this, string_vector.getCPtr(authors), authors);
  }

  public void add_author(String author) {
    w_e_boneJNI.laban_sequence_add_author(swigCPtr, this, author);
  }

  public string_vector get_authors() {
    return new string_vector(w_e_boneJNI.laban_sequence_get_authors(swigCPtr, this), true);
  }

  public void set_title(String title) {
    w_e_boneJNI.laban_sequence_set_title(swigCPtr, this, title);
  }

  public String get_title() {
    return w_e_boneJNI.laban_sequence_get_title(swigCPtr, this);
  }

  public void set_description(String description) {
    w_e_boneJNI.laban_sequence_set_description(swigCPtr, this, description);
  }

  public String get_description() {
    return w_e_boneJNI.laban_sequence_get_description(swigCPtr, this);
  }

  public void set_measures(long measures) {
    w_e_boneJNI.laban_sequence_set_measures(swigCPtr, this, measures);
  }

  public long get_measures() {
    return w_e_boneJNI.laban_sequence_get_measures(swigCPtr, this);
  }

  public void set_time_unit(e_time_unit time_unit) {
    w_e_boneJNI.laban_sequence_set_time_unit(swigCPtr, this, time_unit.swigValue());
  }

  public e_time_unit get_time_unit() {
    return e_time_unit.swigToEnum(w_e_boneJNI.laban_sequence_get_time_unit(swigCPtr, this));
  }

  public void set_beat_duration(long beat_duration) {
    w_e_boneJNI.laban_sequence_set_beat_duration(swigCPtr, this, beat_duration);
  }

  public long get_beat_duration() {
    return w_e_boneJNI.laban_sequence_get_beat_duration(swigCPtr, this);
  }

  public void set_beats(long beats) {
    w_e_boneJNI.laban_sequence_set_beats(swigCPtr, this, beats);
  }

  public long get_beats() {
    return w_e_boneJNI.laban_sequence_get_beats(swigCPtr, this);
  }

  public void set_column_definitions(coldef_vector col_defs) {
    w_e_boneJNI.laban_sequence_set_column_definitions(swigCPtr, this, coldef_vector.getCPtr(col_defs), col_defs);
  }

  public void add_column_definition(column_definition col_def) {
    w_e_boneJNI.laban_sequence_add_column_definition(swigCPtr, this, column_definition.getCPtr(col_def), col_def);
  }

  public coldef_vector get_column_definitions() {
    return new coldef_vector(w_e_boneJNI.laban_sequence_get_column_definitions(swigCPtr, this), true);
  }

  public column_definition get_column_definition(int column_index) {
    long cPtr = w_e_boneJNI.laban_sequence_get_column_definition(swigCPtr, this, column_index);
    return (cPtr == 0) ? null : new column_definition(cPtr, true);
  }

  public void clear_column_definitions() {
    w_e_boneJNI.laban_sequence_clear_column_definitions(swigCPtr, this);
  }

  public int_vector get_columns() {
    return new int_vector(w_e_boneJNI.laban_sequence_get_columns(swigCPtr, this), true);
  }

  public void set_movements(i_mov_vector movements) {
    w_e_boneJNI.laban_sequence_set_movements(swigCPtr, this, i_mov_vector.getCPtr(movements), movements);
  }

  public i_mov_vector get_movements() {
    return new i_mov_vector(w_e_boneJNI.laban_sequence_get_movements(swigCPtr, this), true);
  }

  public void add_movement(i_movement i_mov) {
    w_e_boneJNI.laban_sequence_add_movement(swigCPtr, this, i_movement.getCPtr(i_mov), i_mov);
  }

  public i_mov_vector get_column_movements(int column) {
    return new i_mov_vector(w_e_boneJNI.laban_sequence_get_column_movements(swigCPtr, this, column), true);
  }

  public i_movement get_last_movement() {
    long cPtr = w_e_boneJNI.laban_sequence_get_last_movement(swigCPtr, this);
    return (cPtr == 0) ? null : new i_movement(cPtr, true);
  }

  public void clear_movements() {
    w_e_boneJNI.laban_sequence_clear_movements(swigCPtr, this);
  }

  public String xml(boolean no_header, long indent, String namesp) {
    return w_e_boneJNI.laban_sequence_xml__SWIG_0(swigCPtr, this, no_header, indent, namesp);
  }

  public String xml(boolean no_header, long indent) {
    return w_e_boneJNI.laban_sequence_xml__SWIG_1(swigCPtr, this, no_header, indent);
  }

  public String xml(boolean no_header) {
    return w_e_boneJNI.laban_sequence_xml__SWIG_2(swigCPtr, this, no_header);
  }

  public String xml() {
    return w_e_boneJNI.laban_sequence_xml__SWIG_3(swigCPtr, this);
  }

  public String xml_namespace_header(String namesp) {
    return w_e_boneJNI.laban_sequence_xml_namespace_header__SWIG_0(swigCPtr, this, namesp);
  }

  public String xml_namespace_header() {
    return w_e_boneJNI.laban_sequence_xml_namespace_header__SWIG_1(swigCPtr, this);
  }

  public String xml_schema_location() {
    return w_e_boneJNI.laban_sequence_xml_schema_location(swigCPtr, this);
  }

  public String xml_namespace_uri() {
    return w_e_boneJNI.laban_sequence_xml_namespace_uri(swigCPtr, this);
  }

  public String str() {
    return w_e_boneJNI.laban_sequence_str(swigCPtr, this);
  }

  public static long default_beat_duration() {
    return w_e_boneJNI.laban_sequence_default_beat_duration();
  }

  public static long default_beats_per_measure() {
    return w_e_boneJNI.laban_sequence_default_beats_per_measure();
  }

  public static e_time_unit default_time_unit() {
    return e_time_unit.swigToEnum(w_e_boneJNI.laban_sequence_default_time_unit());
  }

  public static int_vector default_columns() {
    return new int_vector(w_e_boneJNI.laban_sequence_default_columns(), true);
  }

}