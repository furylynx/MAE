package maejavasample;

import maejava.laban_sequence;
import maejava.laban_sequence_sequence_listener;

public class SequenceListener extends laban_sequence_sequence_listener {

	public SequenceListener() 
	{
		
	}
	
	@Override
	public void on_sequence(int timestamp, laban_sequence sequence)
	{
		System.out.println("Received a sequence.");
	}

}
