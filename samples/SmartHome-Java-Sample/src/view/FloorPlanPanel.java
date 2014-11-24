package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JPanel;

import model.PositionInfo;
import model.SensorInfo;

public class FloorPlanPanel extends JPanel {

	List<PositionInfo> positions;
	Map<String, SensorInfo> sensorInfosMap;
	Map<PositionInfo, Double> lightIntensity;
	Map<PositionInfo, Double> musicIntensity;

	Object mutex;

	int maxXPos;
	int maxYPos;

	public FloorPlanPanel(List<PositionInfo> positions) {
		this.positions = positions;
		maxXPos = 0;
		maxYPos = 0;

		mutex = new Object();

		sensorInfosMap = new HashMap<String, SensorInfo>();

		// max positions
		for (PositionInfo info : positions) {
			if ((info.getXpos() + info.getWidth()) > maxXPos) {
				maxXPos = info.getXpos() + info.getWidth();
			}

			if ((info.getYpos() + info.getHeight()) > maxYPos) {
				maxYPos = info.getYpos() + info.getHeight();
			}
		}

		setLayout(new BorderLayout());

		// TODO do things in here
		// draw floor plan, add user info(s) when updated
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		synchronized (mutex) {

			// Draw Text
			for (PositionInfo info : positions) {

				double scaleFactor = (double) getWidth() / (maxXPos + 20);

				if ((double) getHeight() / (maxYPos + 20) < scaleFactor) {
					scaleFactor = (double) getHeight() / (maxYPos + 20);
				}

				// TODO select color
				g.setColor(Color.GRAY.brighter());

				// TODO make relative
				g.fillRect((int) ((info.getXpos() + 10) * scaleFactor),
						(int) ((info.getYpos() + 10) * scaleFactor),
						(int) (info.getWidth() * scaleFactor),
						(int) (info.getHeight() * scaleFactor));

				List<SensorInfo> sensorInfos = getSensorInfos(info
						.getPositionId());
				if (!sensorInfos.isEmpty()) {
					
					
					//handle tracked persons
					int personsTracked = 0;
					
					for (SensorInfo sensorInfo : sensorInfos)
					{
						personsTracked += sensorInfo.getPersonsTracked();
					}

					// draw persons
					for (int i = 0; i < personsTracked; i++) {
						// TODO make relative
						g.setColor(Color.BLUE.brighter());
						g.fillRect(
								(int) ((info.getXpos() + 10 + 10 + i * 20) * scaleFactor),
								(int) ((info.getYpos() + 10 + 10) * scaleFactor),
								(int) (16 * scaleFactor),
								(int) (4 * scaleFactor));
						g.fillOval(
								(int) ((info.getXpos() + 10 + 10 + i * 20 + 4) * scaleFactor),
								(int) ((info.getYpos() + 10 + 8) * scaleFactor),
								(int) (8 * scaleFactor),
								(int) (8 * scaleFactor));
					}

					// TODO draw other things

				}
			}
		}
	}

	public void updateSensorInfo(SensorInfo sensorInfo) {
		synchronized (mutex) {
			sensorInfosMap.put(sensorInfo.getDeviceInfo().getDeviceSerial(),
					sensorInfo);
		}

		revalidate();
		repaint();
	}

	public List<SensorInfo> getSensorInfos(int positionId) {
		List<SensorInfo> result = new ArrayList<SensorInfo>();

		for (Entry<String, SensorInfo> set : sensorInfosMap.entrySet()) {
			if (set.getValue() != null && set.getValue().getPosition() != null) {
				if (set.getValue().getPosition().getPositionId() == positionId) {
					result.add(set.getValue());
				}
			}
		}

		return result;
	}
}
