package view;

import java.awt.BorderLayout;
import java.awt.LayoutManager;
import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import maejava.LabanSequence;
import model.PositionInfo;
import model.SensorInfo;

public class SmartHomePanel extends JPanel implements Observer {

	JTabbedPane tabPane;

	List<SequencePanel> sequencePanels;
	FloorPlanPanel floorPlanPanel;
	RegisteredMovementsPanel registeredMovementsPanel;

	public SmartHomePanel(List<String> tabTitles, List<PositionInfo> positions, List<LabanSequence> registeredSequences) {
		
		sequencePanels = new ArrayList<SequencePanel>();
		tabPane = new JTabbedPane();

		floorPlanPanel = new FloorPlanPanel(positions);
		tabPane.addTab("Floor Plan", floorPlanPanel);
		
		registeredMovementsPanel = new RegisteredMovementsPanel(registeredSequences);
		tabPane.addTab("Registered Gestures", registeredMovementsPanel);

		if (!tabTitles.isEmpty()) {
			for (String str : tabTitles) {
				SequencePanel sequencePanel = new SequencePanel();
				sequencePanels.add(sequencePanel);
				tabPane.addTab(str, sequencePanel);
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

			if (sequencePanels.size() > sensorInfo.getPosition()
					.getPositionId()) {

				// update sequence panel
				SequencePanel sequencePanel = sequencePanels.get(sensorInfo
						.getPosition().getPositionId());
				
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
