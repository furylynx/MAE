package maejavawrapper;

import maejava.general_pose;


public interface IJPoseListener {
	void onPose(int timestamp, general_pose pose);
}
