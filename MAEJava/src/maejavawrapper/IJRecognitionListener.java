package maejavawrapper;

import maejava.laban_sequence_vector;
import maejava.string_vector;


public interface IJRecognitionListener {
	void onRecognition(int timestamp, laban_sequence_vector sequences);
	void onRecognition(int timestamp, string_vector sequenceTitles);
}
