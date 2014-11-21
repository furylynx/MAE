package view;


import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.JPanel;
import maejava.LabanSequence;


public class SequencePanel extends JPanel {

	private JSVGPanel svgPanel;
	private Object mutex;

	public SequencePanel() {
		mutex = new Object();

		setLayout(new BorderLayout());
		setDoubleBuffered(true);

		svgPanel = new JSVGPanel();
		add(svgPanel, BorderLayout.CENTER);
		svgPanel.setBackground(Color.WHITE);
	}

	public void update(LabanSequence sequence) {

		svgPanel.update(sequence.svg(svgPanel.getWidth(), svgPanel.getHeight()));

	}

}
