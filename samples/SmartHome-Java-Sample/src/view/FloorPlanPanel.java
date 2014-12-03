package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JPanel;

import model.PoseInfo;
import model.PositionInfo;
import model.PositionType;
import model.SensorInfo;

public class FloorPlanPanel extends JPanel {

	List<PositionInfo> positions;
	Map<String, SensorInfo> sensorInfosMap;
	Map<String, PoseInfo> dimmingUpPoses;
	Map<String, PoseInfo> dimmingDownPoses;

	Map<Integer, Double> lightIntensities;
	Map<Integer, Long> lightIntensitiesAnimationTimestamp;

	Map<Integer, Double> musicIntensities;
	Map<Integer, Long> musicIntensitiesAnimationTimestamp;

	Object mutex;

	int maxXPos;
	int maxYPos;

	int minXPos;
	int minYPos;

	/**
	 * Creates a new floor plan panel.
	 * 
	 * @param positions
	 *            The position info for all rooms.
	 */
	public FloorPlanPanel(List<PositionInfo> positions) {
		this.positions = positions;
		maxXPos = 0;
		maxYPos = 0;
		minXPos = Integer.MAX_VALUE;
		minYPos = Integer.MAX_VALUE;

		mutex = new Object();

		sensorInfosMap = new HashMap<String, SensorInfo>();
		lightIntensities = new HashMap<Integer, Double>();
		musicIntensities = new HashMap<Integer, Double>();
		lightIntensitiesAnimationTimestamp = new HashMap<Integer, Long>();
		musicIntensitiesAnimationTimestamp = new HashMap<Integer, Long>();

		dimmingUpPoses = new HashMap<String, PoseInfo>();
		dimmingDownPoses = new HashMap<String, PoseInfo>();

		// max positions
		for (PositionInfo info : positions) {

			if (info.getPositionType() != PositionType.TERRACE) {

				if ((info.getXpos() + info.getWidth()) > maxXPos) {
					maxXPos = info.getXpos() + info.getWidth();
				}

				if ((info.getYpos() + info.getHeight()) > maxYPos) {
					maxYPos = info.getYpos() + info.getHeight();
				}

				if (info.getXpos() < minXPos) {
					minXPos = info.getXpos();
				}

				if (info.getYpos() < minYPos) {
					minYPos = info.getYpos();
				}
			}
		}

		setLayout(new BorderLayout());
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Graphics2D g2d = (Graphics2D) g;
		g.setColor(Color.GREEN.darker().darker().darker());
		g.fillRect(g.getClipBounds().x, g.getClipBounds().y,
				g.getClipBounds().width, g.getClipBounds().height);

		// get scale factor
		double scaleFactor = (double) getWidth() / (maxXPos + 20);

		if ((double) getHeight() / (maxYPos + 20) < scaleFactor) {
			scaleFactor = (double) getHeight() / (maxYPos + 20);
		}

		g.setColor(Color.GRAY.brighter());
		g.fillRect((int) Math.round((minXPos - 3 + 10) * scaleFactor),
				(int) Math.round((minYPos - 3 + 10) * scaleFactor),
				(int) Math.round((maxXPos - minXPos + 6) * scaleFactor),
				(int) Math.round((maxYPos - minYPos + 6) * scaleFactor));

		synchronized (mutex) {

			// Draw Text
			for (PositionInfo info : positions) {

				// draw rect; set color according to light intensity
				double pLightIntensity = (lightIntensities.get(info
						.getPositionId()) == null) ? 0.0 : lightIntensities
						.get(info.getPositionId());

				if (lightIntensitiesAnimationTimestamp
						.get(info.getPositionId()) != null) {
					long timestampBegin = lightIntensitiesAnimationTimestamp
							.get(info.getPositionId());
					long timestampNow = System.currentTimeMillis();

					if ((timestampNow - timestampBegin) >= 1000) {
						lightIntensitiesAnimationTimestamp.remove(info
								.getPositionId());
					} else {
						pLightIntensity = (timestampNow - timestampBegin)
								/ 1000.0 * pLightIntensity;
					}
				}

				if (info.getPositionType() != PositionType.TERRACE) {
					g.setColor(new Color((int) (100 + 155 * pLightIntensity),
							(int) (100 + 155 * pLightIntensity),
							(int) (100 + 155 * pLightIntensity)));
				} else {
					g.setColor(Color.GRAY);
				}

				int rectXPos = (int) Math.round((info.getXpos() + 10)
						* scaleFactor);
				int rectYPos = (int) Math.round((info.getYpos() + 10)
						* scaleFactor);
				int rectWidth = (int) Math.round(info.getWidth() * scaleFactor);
				int rectHeight = (int) Math.round(info.getHeight()
						* scaleFactor);

				g.fillRect(rectXPos, rectYPos, rectWidth, rectHeight);

				// door
				g.setColor(new Color(139, 69, 19, 255).darker());

				g.fillRect(
						(int) Math.round((info.getXdoor() + 10) * scaleFactor),
						(int) Math.round((info.getYdoor() + 10) * scaleFactor),
						(int) Math.round(info.getWidthdoor() * scaleFactor),
						(int) Math.round(info.getHeightdoor() * scaleFactor));

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
						g.setColor(Color.BLACK);
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

					Iterator<SensorInfo> sensorInfoIterator = sensorInfos
							.iterator();
					Iterator<Integer> offsetListIterator = offsetList
							.iterator();
					while (offsetListIterator.hasNext()
							&& sensorInfoIterator.hasNext()) {
						int offsetIndex = offsetListIterator.next();
						SensorInfo sensorInfo = sensorInfoIterator.next();

						if (sensorInfo.getPersonsTracked() > 0) {

							g.setColor(Color.ORANGE);
							g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN,
									(int) (4 * scaleFactor)));
							g.drawString(
									"M " + sensorInfo.getMovingRate(),
									(int) ((info.getXpos() + 10 + 10 + offsetIndex * 20) * scaleFactor),
									(int) ((info.getYpos() + 10 + 10 + 20) * scaleFactor));
						}
					}
				}

				drawLamp(g, scaleFactor, info);

				// -- draw music
				drawMusicNote(g, scaleFactor, info);

			}
		}
	}

	/**
	 * Draws the light bulb symbol in the center of the enlightened room.
	 * 
	 * @param g
	 * @param scaleFactor
	 * @param info
	 */
	private void drawLamp(Graphics g, double scaleFactor, PositionInfo info) {

		// TODO draw light bulb
		double pLightIntensity = (lightIntensities.get(info.getPositionId()) == null) ? 0.0
				: lightIntensities.get(info.getPositionId());

		if (pLightIntensity > 0.0) {

			g.setColor(Color.WHITE);
			g.fillOval(
					(int) ((info.getXpos() + 5 + info.getWidth() / 2.0) * scaleFactor),
					(int) ((info.getYpos() + 5 + info.getHeight() / 2.0) * scaleFactor),
					(int) (10 * scaleFactor), (int) (10 * scaleFactor));

			g.setColor(Color.BLACK);
			g.drawOval(
					(int) ((info.getXpos() + 5 + info.getWidth() / 2.0) * scaleFactor),
					(int) ((info.getYpos() + 5 + info.getHeight() / 2.0) * scaleFactor),
					(int) (10 * scaleFactor), (int) (10 * scaleFactor));

			g.setColor(Color.GRAY.brighter());
			g.fillRect(
					(int) ((info.getXpos() + 5 + info.getWidth() / 2.0 + 2.5) * scaleFactor),
					(int) ((info.getYpos() + 5 + info.getHeight() / 2.0 + 9) * scaleFactor),
					(int) (5 * scaleFactor), (int) (5 * scaleFactor));
			
			g.setColor(Color.BLACK);
			g.drawRect(
					(int) ((info.getXpos() + 5 + info.getWidth() / 2.0 + 2.5) * scaleFactor),
					(int) ((info.getYpos() + 5 + info.getHeight() / 2.0 + 9) * scaleFactor),
					(int) (5 * scaleFactor), (int) (5 * scaleFactor));
			
			g.fillRect(
					(int) ((info.getXpos() + 5 + info.getWidth() / 2.0 + 4) * scaleFactor),
					(int) ((info.getYpos() + 5 + info.getHeight() / 2.0 + 14) * scaleFactor),
					(int) (2 * scaleFactor), (int) (1 * scaleFactor));
		}

	}
	

	/**
	 * @param g
	 * @param scaleFactor
	 * @param info
	 */
	private void drawMusicNote(Graphics g, double scaleFactor, PositionInfo info) {

		double pMusicIntensity = (musicIntensities.get(info.getPositionId()) == null) ? 0.0
				: musicIntensities.get(info.getPositionId());

		if (pMusicIntensity > 0.0) {
			g.setColor(Color.BLACK);
			g.drawOval(
					(int) ((info.getXpos() + info.getWidth() - 24) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 26) * scaleFactor),
					(int) (20 * scaleFactor), (int) (20 * scaleFactor));

			g.setColor(Color.WHITE);
			g.fillOval(
					(int) ((info.getXpos() + info.getWidth() - 24) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 26) * scaleFactor),
					(int) (20 * scaleFactor), (int) (20 * scaleFactor));

			g.setColor(Color.BLACK);
			g.fillOval(
					(int) ((info.getXpos() + info.getWidth() - 21) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 17) * scaleFactor),
					(int) (5 * scaleFactor), (int) (5 * scaleFactor));

			g.fillOval(
					(int) ((info.getXpos() + info.getWidth() - 14) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 15) * scaleFactor),
					(int) (5 * scaleFactor), (int) (5 * scaleFactor));

			g.fillRect(
					(int) ((info.getXpos() + info.getWidth() - 10) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 22) * scaleFactor),
					(int) (1 * scaleFactor), (int) (10 * scaleFactor));
			g.fillRect(
					(int) ((info.getXpos() + info.getWidth() - 17) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 22) * scaleFactor),
					(int) (1 * scaleFactor), (int) (8 * scaleFactor));
			g.fillRect(
					(int) ((info.getXpos() + info.getWidth() - 17) * scaleFactor),
					(int) ((info.getYpos() + info.getHeight() - 22) * scaleFactor),
					(int) (8 * scaleFactor), (int) (1 * scaleFactor));
		}
	}

	/**
	 * Updates the sensor info for the next frame.
	 * 
	 * @param sensorInfo
	 *            The sensor Info.
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

						if (lightIntensities.get(sensorInfo.getPosition()
								.getPositionId()) == null
								|| lightIntensities.get(sensorInfo
										.getPosition().getPositionId()) == 0.0) {
							lightIntensities.put(sensorInfo.getPosition()
									.getPositionId(), 1.0);
							lightIntensitiesAnimationTimestamp.put(sensorInfo
									.getPosition().getPositionId(), System
									.currentTimeMillis());
						}
					} else if ("LightsOff".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {

						if (lightIntensities.get(sensorInfo.getPosition()
								.getPositionId()) == null
								|| lightIntensities.get(sensorInfo
										.getPosition().getPositionId()) > 0.0) {
							lightIntensities.put(sensorInfo.getPosition()
									.getPositionId(), 0.0);
							lightIntensitiesAnimationTimestamp.put(sensorInfo
									.getPosition().getPositionId(), System
									.currentTimeMillis());
						}

					} else if ("DimDown".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {

						if (dimmingDownPoses.get(sensorInfo.getDeviceInfo()
								.getDeviceSerial()) == null) {
							dimmingDownPoses.put(sensorInfo.getDeviceInfo()
									.getDeviceSerial(), new PoseInfo(sensorInfo
									.getCurrentRecognition().get(i)));
						}

					} else if ("DimUp".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {

						if (dimmingUpPoses.get(sensorInfo.getDeviceInfo()
								.getDeviceSerial()) == null) {
							dimmingUpPoses.put(sensorInfo.getDeviceInfo()
									.getDeviceSerial(), new PoseInfo(sensorInfo
									.getCurrentRecognition().get(i)));
						}

					} else if ("MusicOn".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {
						
						musicIntensities.put(sensorInfo.getPosition()
								.getPositionId(), 1.0);
					} else if ("MusicOff".equals(sensorInfo
							.getCurrentRecognition().get(i).getTitle().trim())) {
						
						musicIntensities.put(sensorInfo.getPosition()
								.getPositionId(), 0.0);
					}

				}
			}

			// dim the lights if pose is held
			if (dimmingUpPoses
					.get(sensorInfo.getDeviceInfo().getDeviceSerial()) != null) {

				PoseInfo poseInfo = dimmingUpPoses.get(sensorInfo
						.getDeviceInfo().getDeviceSerial());
				if (poseInfo.matchingPose(sensorInfo.getCurrentSequence())) {
					if (lightIntensities.get(sensorInfo.getPosition()
							.getPositionId()) != null) {
						double intensity = lightIntensities.get(sensorInfo
								.getPosition().getPositionId());
						if (intensity > 0.995) {
							intensity = 1.0;
						} else {
							intensity += 0.005;
						}

						lightIntensities.put(sensorInfo.getPosition()
								.getPositionId(), intensity);
					} else {
						lightIntensities.put(sensorInfo.getPosition()
								.getPositionId(), 0.0);
					}
				} else {

					dimmingUpPoses.remove(sensorInfo.getDeviceInfo()
							.getDeviceSerial());
				}
			}

			if (dimmingDownPoses.get(sensorInfo.getDeviceInfo()
					.getDeviceSerial()) != null) {
				PoseInfo poseInfo = dimmingDownPoses.get(sensorInfo
						.getDeviceInfo().getDeviceSerial());
				if (poseInfo.matchingPose(sensorInfo.getCurrentSequence())) {
					if (lightIntensities.get(sensorInfo.getPosition()
							.getPositionId()) != null) {
						double intensity = lightIntensities.get(sensorInfo
								.getPosition().getPositionId());
						if (intensity < 0.005) {
							intensity = 0.0;
						} else {
							intensity -= 0.005;
						}

						lightIntensities.put(sensorInfo.getPosition()
								.getPositionId(), intensity);
					} else {
						lightIntensities.put(sensorInfo.getPosition()
								.getPositionId(), 0.0);
					}
				} else {
					dimmingDownPoses.remove(sensorInfo.getDeviceInfo()
							.getDeviceSerial());
				}
			}
		}

		revalidate();
		repaint();
	}

	/**
	 * Returns the sensor info related to the room with the position ID.
	 * 
	 * @param positionId
	 *            The position ID.
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
