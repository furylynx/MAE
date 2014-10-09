/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public final class e_turn_direction {
  public final static e_turn_direction NONE = new e_turn_direction("NONE");
  public final static e_turn_direction COUNTER_CLOCKWISE = new e_turn_direction("COUNTER_CLOCKWISE");
  public final static e_turn_direction CLOCKWISE = new e_turn_direction("CLOCKWISE");
  public final static e_turn_direction ANY = new e_turn_direction("ANY");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static e_turn_direction swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + e_turn_direction.class + " with value " + swigValue);
  }

  private e_turn_direction(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private e_turn_direction(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private e_turn_direction(String swigName, e_turn_direction swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static e_turn_direction[] swigValues = { NONE, COUNTER_CLOCKWISE, CLOCKWISE, ANY };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

