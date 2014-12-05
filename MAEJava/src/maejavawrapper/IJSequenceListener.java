package maejavawrapper;

import java.math.BigInteger;

import maejava.LabanSequence;


public interface IJSequenceListener {

	void onSequence(BigInteger timestamp, LabanSequence sequence);
}
