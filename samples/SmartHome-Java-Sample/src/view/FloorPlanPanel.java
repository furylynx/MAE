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
	Map<PositionInfo, Double> lightIntensities;
	Map<PositionInfo, Double> musicIntensities;

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
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		synchronized (mutex) {

			// get scale factor
			double scaleFactor = (double) getWidth() / (maxXPos + 20);

			if ((double) getHeight() / (maxYPos + 20) < scaleFactor) {
				scaleFactor = (double) getHeight() / (maxYPos + 20);
			}

			// Draw Text
			for (PositionInfo info : positions) {

				// draw rect; set color according to light intensity
				double pLightIntensity = (lightIntensities.get(info) == null) ? 0.0
						: lightIntensities.get(info);
				g.setColor(new Color((int) (100 + 155 * pLightIntensity),
						(int) (100 + 155 * pLightIntensity),
						(int) (100 + 155 * pLightIntensity)));

				int rectXPos = (int) ((info.getXpos() + 10) * scaleFactor);
				int rectYPos = (int) ((info.getYpos() + 10) * scaleFactor);
				int rectWidth = (int) (info.getWidth() * scaleFactor);
				int rectHeight = (int) (info.getHeight() * scaleFactor);

				g.fillRect(rectXPos, rectYPos, rectWidth, rectHeight);

				g.setColor(Color.BLACK);
				g.drawRect(rectXPos, rectYPos, rectWidth, rectHeight);

				// -- draw tracked persons
				List<SensorInfo> sensorInfos = getSensorInfos(info
						.getPositionId());
				if (!sensorInfos.isEmpty()) {

					// handle tracked persons
					int personsTracked = 0;

					for (SensorInfo sensorInfo : sensorInfos) {
						personsTracked += sensorInfo.getPersonsTracked();
					}

					// draw persons
					for (int i = 0; i < personsTracked; i++) {
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
				}

				// -- draw music
				double pMusicIntensity = (musicIntensities.get(info) == null) ? 0.0
						: musicIntensities.get(info);
				// TODO draw other things
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
