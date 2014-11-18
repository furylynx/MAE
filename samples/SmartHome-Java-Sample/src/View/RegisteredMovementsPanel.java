package View;

import java.util.List;

import javax.swing.JPanel;

import maejava.LabanSequence;

public class RegisteredMovementsPanel extends JPanel {

	List<LabanSequence> registeredSequences;
	
	public RegisteredMovementsPanel(List<LabanSequence> registeredSequences)
	{
		this.registeredSequences = registeredSequences;
		
		//TODO selector + display for the sequences
	}
	
}
