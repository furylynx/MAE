package View;

import java.awt.BorderLayout;
import java.awt.LayoutManager;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import Model.SensorInfo;

public class SmartHomePanel extends JPanel implements Observer {

	JTabbedPane tabPane;
	
	SequencePanel room01SequencePanel;
	
	public SmartHomePanel() {
		tabPane = new JTabbedPane();
		
		room01SequencePanel = new SequencePanel();
		tabPane.add(room01SequencePanel);
		
		add(tabPane, BorderLayout.CENTER);
		
	}

	@Override
	public void update(Observable o, Object arg) {
		
		// update this window 
		
		if (o instanceof SensorInfo)
		{
			SensorInfo sensorInfo = (SensorInfo) o;
			
			if (sensorInfo.getPosition().getPositionId() == 1)
			{
				//TODO check size ok
				room01SequencePanel.updateSVG(sensorInfo.getCurrentSequence().svg(room01SequencePanel.getWidth(), room01SequencePanel.getHeight()));
			}
			
			//TODO handle the sensor info and display information...
		}
		
		
	}

}
