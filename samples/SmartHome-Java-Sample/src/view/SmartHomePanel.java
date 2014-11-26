package view;

import java.awt.BorderLayout;
import java.awt.LayoutManager;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import maejava.LabanSequence;
import maenitejava.DeviceInfo;
import model.PositionInfo;
import model.SensorInfo;

public class SmartHomePanel extends JPanel implements Observer {

	JTabbedPane tabPane;

	Map<String, SequencePanel> sequencePanelsMap;
	FloorPlanPanel floorPlanPanel;
	RegisteredMovementsPanel registeredMovementsPanel;

	public SmartHomePanel(List<DeviceInfo> devices, List<PositionInfo> positions, List<LabanSequence> registeredSequences) {
		
		sequencePanelsMap = new HashMap<String, SequencePanel>();
		tabPane = new JTabbedPane();

		floorPlanPanel = new FloorPlanPanel(positions);
		tabPane.addTab("Floor Plan", floorPlanPanel);
		
		registeredMovementsPanel = new RegisteredMovementsPanel(registeredSequences);
		tabPane.addTab("Registered Gestures", registeredMovementsPanel);

		if (!devices.isEmpty()) {
			for (DeviceInfo device : devices) {
				SequencePanel sequencePanel = new SequencePanel();
				sequencePanelsMap.put(device.getDeviceSerial(), sequencePanel);
				tabPane.addTab(device.getDeviceName(), sequencePanel);
			}
		} else {
			tabPane.addTab("--No Devices--", new NoDevicesPanel());
		}

		setLayout(new BorderLayout());
		add(tabPane, BorderLayout.CENTER);

	}

	@Override
	public void update(Observable o, Object arg) {

		// update this window
		if (o instanceof SensorInfo) {
			SensorInfo sensorInfo = (SensorInfo) o;

			if (sequencePanelsMap.get(sensorInfo.getDeviceInfo().getDeviceSerial()) != null) {

				// update sequence panel
				SequencePanel sequencePanel = sequencePanelsMap.get(sensorInfo.getDeviceInfo().getDeviceSerial());
				
				if (sensorInfo.getCurrentSequence() != null)
				{
					sequencePanel.update(sensorInfo.getCurrentSequence());
				}
			}

			// display information on floor plan
			floorPlanPanel.updateSensorInfo(sensorInfo);
		}
	}

}
