/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public final class EPathType {
  public final static EPathType NONE_PATH_TYPE = new EPathType("NONE_PATH_TYPE");
  public final static EPathType STRAIGHT = new EPathType("STRAIGHT");
  public final static EPathType CIRCULAR_LEFT = new EPathType("CIRCULAR_LEFT");
  public final static EPathType CIRCULAR_RIGHT = new EPathType("CIRCULAR_RIGHT");
  public final static EPathType ANY = new EPathType("ANY");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static EPathType swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + EPathType.class + " with value " + swigValue);
  }

  private EPathType(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private EPathType(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private EPathType(String swigName, EPathType swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static EPathType[] swigValues = { NONE_PATH_TYPE, STRAIGHT, CIRCULAR_LEFT, CIRCULAR_RIGHT, ANY };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

