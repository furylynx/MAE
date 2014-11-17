package View;

import java.awt.LayoutManager;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JPanel;

import Model.SensorInfo;

public class SmartHomePanel extends JPanel implements Observer {

	public SmartHomePanel() {
		// TODO do stuff in here...
	}

	@Override
	public void update(Observable o, Object arg) {
		
		// update this window 
		
		if (o instanceof SensorInfo)
		{
			SensorInfo sensorInfo = (SensorInfo) o;
			
			//TODO handle the sensor info and display information...
		}
		
		
	}

}
