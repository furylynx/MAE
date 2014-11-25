package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JPanel;

import model.PositionInfo;
import model.SensorInfo;

public class FloorPlanPanel extends JPanel {

	List<PositionInfo> positions;
	Map<String, SensorInfo> sensorInfosMap;

	Map<Integer, Double> lightIntensities;
	Map<Integer, Long> lightIntensitiesAnimationTimestamp;

	Map<Integer, Double> musicIntensities;
	Map<Integer, Long> musicIntensitiesAnimationTimestamp;

	Object mutex;

	int maxXPos;
	int maxYPos;

	public FloorPlanPanel(List<PositionInfo> positions) {
		this.positions = positions;
		maxXPos = 0;
		maxYPos = 0;

		mutex = new Object();

		sensorInfosMap = new HashMap<String, SensorInfo>();
		lightIntensities = new HashMap<Integer, Double>();
		musicIntensities = new HashMap<Integer, Double>();
		lightIntensitiesAnimationTimestamp = new HashMap<Integer, Long>();
		musicIntensitiesAnimationTimestamp = new HashMap<Integer, Long>();

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

	@Override
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
				double pLightIntensity = (lightIntensities.get(info.getPositionId()) == null) ? 0.0
						: lightIntensities.get(info.getPositionId());

				if (lightIntensitiesAnimationTimestamp.get(info.getPositionId()) != null) {
					long timestampBegin = lightIntensitiesAnimationTimestamp
							.get(info.getPositionId());
					long timestampNow = System.currentTimeMillis();

					if ((timestampNow - timestampBegin) >= 1000) {
						lightIntensitiesAnimationTimestamp.remove(info.getPositionId());
					} else {
						pLightIntensity = (timestampNow - timestampBegin)
								/ 1000.0 * pLightIntensity;
					}
				}

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
					List<Integer> offsetList = new LinkedList<Integer>();

					for (SensorInfo sensorInfo : sensorInfos) {
						offsetList.add(personsTracked);
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
					
					Iterator<SensorInfo> sensorInfoIterator = sensorInfos.iterator();
					Iterator<Integer> offsetListIterator = offsetList.iterator();
					while(offsetListIterator.hasNext() && sensorInfoIterator.hasNext())
					{
						int offsetIndex = offsetListIterator.next();
						SensorInfo sensorInfo = sensorInfoIterator.next();
								
						
						//TODO good color?
						g.setColor(Color.ORANGE);
						//TODO FONT?
						g.drawString("M "+sensorInfo.getMovingRate(), (int) ((info.getXpos() + 10 + 10 + offsetIndex * 20) * scaleFactor), (int) ((info.getYpos() + 10 + 10 + 20) * scaleFactor));
					}
				}

				// -- draw music
				double pMusicIntensity = (musicIntensities.get(info.getPositionId()) == null) ? 0.0
						: musicIntensities.get(info.getPositionId());
				// TODO draw other things
			}
		}
	}

	/**
	 * Updates the sensor info for the next frame.
	 * 
	 * @param sensorInfo The sensor Info.
	 */
	public void updateSensorInfo(SensorInfo sensorInfo) {

		synchronized (mutex) {
			sensorInfosMap.put(sensorInfo.getDeviceInfo().getDeviceSerial(),
					sensorInfo);

			// check recognized sequences and do actions
			if (sensorInfo.getCurrentRecognition() != null) {
				for (int i = 0; i < sensorInfo.getCurrentRecognition().size(); i++) {
					if ("LightsOn".equals(sensorInfo.getCurrentRecognition()
							.get(i).getTitle().trim())) {
						lightIntensities.put(sensorInfo.getPosition().getPositionId(), 1.0);
						lightIntensitiesAnimationTimestamp.put(
								sensorInfo.getPosition().getPositionId(),
								System.currentTimeMillis());
					} else if ("LightsOff".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {
						lightIntensities.put(sensorInfo.getPosition().getPositionId(), 0.0);
						lightIntensitiesAnimationTimestamp.put(
								sensorInfo.getPosition().getPositionId(),
								System.currentTimeMillis());
					} else if ("DimDown".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {
						
						//TODO
						lightIntensities.put(sensorInfo.getPosition().getPositionId(), 0.0);
					} else if ("DimUp".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {
						
						//TODO
						lightIntensities.put(sensorInfo.getPosition().getPositionId(), 0.0);

					}

					// TODO dim and stuff
				}
			}
		}

		revalidate();
		repaint();
	}

	/**
	 * Returns the sensor info related to the room with the position ID.
	 * 
	 * @param positionId The position ID.
	 * @return The sensor information.
	 */
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
