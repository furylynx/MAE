/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public final class e_level {
  public final static e_level NONE_LEVEL = new e_level("NONE_LEVEL");
  public final static e_level HIGH = new e_level("HIGH");
  public final static e_level MIDDLE = new e_level("MIDDLE");
  public final static e_level LOW = new e_level("LOW");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static e_level swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + e_level.class + " with value " + swigValue);
  }

  private e_level(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private e_level(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private e_level(String swigName, e_level swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static e_level[] swigValues = { NONE_LEVEL, HIGH, MIDDLE, LOW };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
