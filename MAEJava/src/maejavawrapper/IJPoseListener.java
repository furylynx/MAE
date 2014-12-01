package maejavawrapper;

import java.math.BigInteger;

import maejava.GeneralPose;


public interface IJPoseListener {
	void onPose(BigInteger timestamp, GeneralPose pose);
}
