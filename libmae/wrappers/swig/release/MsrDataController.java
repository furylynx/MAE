/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package maejava;

public class MsrDataController {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public MsrDataController(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(MsrDataController obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MaeJavaJNI.delete_MsrDataController(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public MsrDataController() {
    this(MaeJavaJNI.new_MsrDataController(), true);
  }

  public MsrData readMsrFile(String filename, MsrSpec spec) {
    long cPtr = MaeJavaJNI.MsrDataController_readMsrFile__SWIG_0(swigCPtr, this, filename, MsrSpec.getCPtr(spec), spec);
    return (cPtr == 0) ? null : new MsrData(cPtr, true);
  }

  public MsrData readMsrFile(String filename, MsrSpec spec, long begin_frame, long end_frame) {
    long cPtr = MaeJavaJNI.MsrDataController_readMsrFile__SWIG_1(swigCPtr, this, filename, MsrSpec.getCPtr(spec), spec, begin_frame, end_frame);
    return (cPtr == 0) ? null : new MsrData(cPtr, true);
  }

  public MsrData readMsrStr(String msr_str, MsrSpec spec) {
    long cPtr = MaeJavaJNI.MsrDataController_readMsrStr__SWIG_0(swigCPtr, this, msr_str, MsrSpec.getCPtr(spec), spec);
    return (cPtr == 0) ? null : new MsrData(cPtr, true);
  }

  public MsrData readMsrStr(String msr_str, MsrSpec spec, long begin_frame, long end_frame) {
    long cPtr = MaeJavaJNI.MsrDataController_readMsrStr__SWIG_1(swigCPtr, this, msr_str, MsrSpec.getCPtr(spec), spec, begin_frame, end_frame);
    return (cPtr == 0) ? null : new MsrData(cPtr, true);
  }

  public String msrStr(GeneralSkeletonVector data) {
    return MaeJavaJNI.MsrDataController_msrStr__SWIG_0(swigCPtr, this, GeneralSkeletonVector.getCPtr(data), data);
  }

  public String msrStr(GeneralSkeleton data) {
    return MaeJavaJNI.MsrDataController_msrStr__SWIG_1(swigCPtr, this, GeneralSkeleton.getCPtr(data), data);
  }

  public void printMsrFile(String filename, GeneralSkeletonVector data) {
    MaeJavaJNI.MsrDataController_printMsrFile__SWIG_0(swigCPtr, this, filename, GeneralSkeletonVector.getCPtr(data), data);
  }

  public void printMsrFile(String filename, GeneralSkeleton data) {
    MaeJavaJNI.MsrDataController_printMsrFile__SWIG_1(swigCPtr, this, filename, GeneralSkeleton.getCPtr(data), data);
  }

}
