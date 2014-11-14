package maejavawrapper;

import maejava.LabanSequenceVector;
import maejava.StringVector;



public interface IJRecognitionListener {
	void onRecognition(int timestamp, LabanSequenceVector sequences);
	void onRecognition(int timestamp, StringVector sequenceTitles);
}
