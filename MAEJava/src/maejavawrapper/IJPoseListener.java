package maejavawrapper;

import maejava.GeneralPose;


public interface IJPoseListener {
	void onPose(int timestamp, GeneralPose pose);
}
