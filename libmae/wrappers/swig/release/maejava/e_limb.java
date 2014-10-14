/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public final class e_limb {
  public final static e_limb NONE_LIMB = new e_limb("NONE_LIMB");
  public final static e_limb ARM = new e_limb("ARM");
  public final static e_limb LEG = new e_limb("LEG");
  public final static e_limb NECK = new e_limb("NECK");
  public final static e_limb UPPER_ARM = new e_limb("UPPER_ARM");
  public final static e_limb LOWER_ARM = new e_limb("LOWER_ARM");
  public final static e_limb THIGH = new e_limb("THIGH");
  public final static e_limb LOWER_LEG = new e_limb("LOWER_LEG");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static e_limb swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + e_limb.class + " with value " + swigValue);
  }

  private e_limb(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private e_limb(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private e_limb(String swigName, e_limb swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static e_limb[] swigValues = { NONE_LIMB, ARM, LEG, NECK, UPPER_ARM, LOWER_ARM, THIGH, LOWER_LEG };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
