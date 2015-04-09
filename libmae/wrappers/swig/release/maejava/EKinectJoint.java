/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public final class EKinectJoint {
  public final static EKinectJoint INVALID_KINECTJOINT = new EKinectJoint("INVALID_KINECTJOINT", MaeJavaJNI.INVALID_KINECTJOINT_get());
  public final static EKinectJoint WAIST = new EKinectJoint("WAIST");
  public final static EKinectJoint TORSO = new EKinectJoint("TORSO");
  public final static EKinectJoint NECK = new EKinectJoint("NECK");
  public final static EKinectJoint HEAD = new EKinectJoint("HEAD");
  public final static EKinectJoint LEFT_SHOULDER = new EKinectJoint("LEFT_SHOULDER");
  public final static EKinectJoint LEFT_ELBOW = new EKinectJoint("LEFT_ELBOW");
  public final static EKinectJoint LEFT_WRIST = new EKinectJoint("LEFT_WRIST");
  public final static EKinectJoint LEFT_HAND = new EKinectJoint("LEFT_HAND");
  public final static EKinectJoint RIGHT_SHOULDER = new EKinectJoint("RIGHT_SHOULDER");
  public final static EKinectJoint RIGHT_ELBOW = new EKinectJoint("RIGHT_ELBOW");
  public final static EKinectJoint RIGHT_WRIST = new EKinectJoint("RIGHT_WRIST");
  public final static EKinectJoint RIGHT_HAND = new EKinectJoint("RIGHT_HAND");
  public final static EKinectJoint LEFT_HIP = new EKinectJoint("LEFT_HIP");
  public final static EKinectJoint LEFT_KNEE = new EKinectJoint("LEFT_KNEE");
  public final static EKinectJoint LEFT_ANKLE = new EKinectJoint("LEFT_ANKLE");
  public final static EKinectJoint LEFT_FOOT = new EKinectJoint("LEFT_FOOT");
  public final static EKinectJoint RIGHT_HIP = new EKinectJoint("RIGHT_HIP");
  public final static EKinectJoint RIGHT_KNEE = new EKinectJoint("RIGHT_KNEE");
  public final static EKinectJoint RIGHT_ANKLE = new EKinectJoint("RIGHT_ANKLE");
  public final static EKinectJoint RIGHT_FOOT = new EKinectJoint("RIGHT_FOOT");
  public final static EKinectJoint WRH = new EKinectJoint("WRH");
  public final static EKinectJoint WLH = new EKinectJoint("WLH");
  public final static EKinectJoint WT = new EKinectJoint("WT");
  public final static EKinectJoint NLS = new EKinectJoint("NLS");
  public final static EKinectJoint NRS = new EKinectJoint("NRS");
  public final static EKinectJoint NH = new EKinectJoint("NH");
  public final static EKinectJoint END_LH = new EKinectJoint("END_LH");
  public final static EKinectJoint END_RH = new EKinectJoint("END_RH");
  public final static EKinectJoint END_LF = new EKinectJoint("END_LF");
  public final static EKinectJoint END_RF = new EKinectJoint("END_RF");
  public final static EKinectJoint END_H = new EKinectJoint("END_H");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static EKinectJoint swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + EKinectJoint.class + " with value " + swigValue);
  }

  private EKinectJoint(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private EKinectJoint(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private EKinectJoint(String swigName, EKinectJoint swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static EKinectJoint[] swigValues = { INVALID_KINECTJOINT, WAIST, TORSO, NECK, HEAD, LEFT_SHOULDER, LEFT_ELBOW, LEFT_WRIST, LEFT_HAND, RIGHT_SHOULDER, RIGHT_ELBOW, RIGHT_WRIST, RIGHT_HAND, LEFT_HIP, LEFT_KNEE, LEFT_ANKLE, LEFT_FOOT, RIGHT_HIP, RIGHT_KNEE, RIGHT_ANKLE, RIGHT_FOOT, WRH, WLH, WT, NLS, NRS, NH, END_LH, END_RH, END_LF, END_RF, END_H };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

