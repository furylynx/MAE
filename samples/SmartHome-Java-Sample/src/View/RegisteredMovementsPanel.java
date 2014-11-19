package View;

import java.awt.BorderLayout;
import java.util.List;

import javax.swing.JComboBox;
import javax.swing.JPanel;

import org.apache.batik.swing.JSVGCanvas;
import org.apache.batik.swing.JSVGScrollPane;

import maejava.LabanSequence;

public class RegisteredMovementsPanel extends JPanel {

	List<LabanSequence> registeredSequences;
	JComboBox<String> comboBox;
	List<JSVGScrollPane> svgPanels;
	
	public RegisteredMovementsPanel(List<LabanSequence> registeredSequences)
	{
		this.registeredSequences = registeredSequences;
		
		comboBox = new JComboBox<String>();
		
		//TODO selector + display for the sequences
		
		setLayout(new BorderLayout());
		add(comboBox, BorderLayout.WEST);
		
	}
	
}
