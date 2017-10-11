package maejavawrapper;

import java.math.BigInteger;

import maejava.LabanSequenceVector;
import maejava.StringVector;



public interface IJRecognitionListener {
	void onRecognition(BigInteger timestamp, LabanSequenceVector sequences);
	void onRecognition(BigInteger timestamp, StringVector sequenceTitles);
}
