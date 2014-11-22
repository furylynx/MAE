package view;


import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.JPanel;
import maejava.LabanSequence;


public class SequencePanel extends JPanel {

	private JSVGPanel svgPanel;

	
	/**
	 * Creates a new sequence panel to prsent a laban sequence.
	 */
	public SequencePanel() {

		setLayout(new BorderLayout());
		setDoubleBuffered(true);

		svgPanel = new JSVGPanel();
		add(svgPanel, BorderLayout.CENTER);
		svgPanel.setBackground(Color.WHITE);
	}

	/**
	 * Updates the panel.
	 * 
	 * @param sequence The laban sequence.
	 */
	public void update(LabanSequence sequence) {

		svgPanel.update(sequence.svg(svgPanel.getWidth(), svgPanel.getHeight()));

	}

}
