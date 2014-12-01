package model;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;

import maejava.GeneralSkeletonVector;
import maejava.LabanSequence;
import maejava.LabanSequenceVector;
import maenitejava.DeviceInfo;
import maenitejava.NiteFarm;

public class SensorInfo extends Observable {

	private PositionInfo position;

	private DeviceInfo deviceInfo;

	private GeneralSkeletonVector sensorData;

	private LabanSequence currentSequence;

	private LabanSequenceVector currentRecognition;

	List<Integer> bodyParts;
	Map<Integer, Double> movingRatePerBodyPart;
	
	private double movingRate;
	
	private int personsTracked;
	
	private long timestamp;


	/**
	 * Creates a new sensor info object.
	 * 
	 * @param position
	 *            The room position
	 * @param deviceInfo
	 *            The device info.
	 */
	public SensorInfo(PositionInfo position, DeviceInfo deviceInfo, List<Integer> bodyParts) {
		this.position = position;
		this.deviceInfo = deviceInfo;
		this.bodyParts = bodyParts;
		
		movingRatePerBodyPart = new HashMap<Integer, Double>();
	}

	/**
	 * Creates a new sensor info object.
	 * 
	 * @param position
	 *            The position info.
	 * @param serialNumber
	 *            The serial number of the device to be used.
	 */
	public SensorInfo(PositionInfo position, String serialNumber, List<Integer> bodyParts) {
		this.position = position;
		this.deviceInfo = NiteFarm.getDeviceInfo(serialNumber);
		this.bodyParts = bodyParts;
		
		movingRatePerBodyPart = new HashMap<Integer, Double>();
	}

	/**
	 * Processes the next frame of the sensor data.
	 * 
	 * @param sensorData
	 * @param currentSequence
	 * @param currentRecognition
	 */
	public void nextFrame(long timestamp, GeneralSkeletonVector sensorData,
			LabanSequence currentSequence,
			LabanSequenceVector currentRecognition) {

		this.timestamp = timestamp;
		this.sensorData = sensorData;
		this.currentSequence = currentSequence;
		this.currentRecognition = currentRecognition;

		//set number of tracked persons
		personsTracked = 0;
		for (int i = 0; i < sensorData.size(); i++)
		{
			if (sensorData.get(i) != null)
			{
				personsTracked++;
			}
		}
		
		// calculate the moving rate
		if (currentSequence != null)
		{
			movingRate = Math.round((double)currentSequence.getMovements().size()/(bodyParts.size()*currentSequence.getMeasures())*100.0)/100.0;
			
			for (Integer bodyPart : bodyParts)
			{
				movingRatePerBodyPart.put(bodyPart, Math.round((double)currentSequence.getColumnMovements(bodyPart).size()/currentSequence.getMeasures()*100.0)/100.0);
			}
		}
		else
		{
			movingRate = 0.0;
		}
		
		// notify observers
		setChanged();
		notifyObservers();
	}

	/**
	 * @return the position
	 */
	public PositionInfo getPosition() {
		return position;
	}

	/**
	 * @param position
	 *            the position to set
	 */
	public void setPosition(PositionInfo position) {
		this.position = position;
	}

	/**
	 * @return the deviceInfo
	 */
	public DeviceInfo getDeviceInfo() {
		return deviceInfo;
	}

	/**
	 * @param deviceInfo
	 *            the deviceInfo to set
	 */
	public void setDeviceInfo(DeviceInfo deviceInfo) {
		this.deviceInfo = deviceInfo;
	}

	/**
	 * @return the sensorData
	 */
	public GeneralSkeletonVector getSensorData() {
		return sensorData;
	}

	/**
	 * @param sensorData
	 *            the sensorData to set
	 */
	public void setSensorData(GeneralSkeletonVector sensorData) {
		this.sensorData = sensorData;
	}

	/**
	 * @return the currentSequence
	 */
	public LabanSequence getCurrentSequence() {
		return currentSequence;
	}

	/**
	 * @param currentSequence
	 *            the currentSequence to set
	 */
	public void setCurrentSequence(LabanSequence currentSequence) {
		this.currentSequence = currentSequence;
	}

	/**
	 * @return the currentRecognition
	 */
	public LabanSequenceVector getCurrentRecognition() {
		return currentRecognition;
	}

	/**
	 * @param currentRecognition
	 *            the currentRecognition to set
	 */
	public void setCurrentRecognition(LabanSequenceVector currentRecognition) {
		this.currentRecognition = currentRecognition;
	}

	/**
	 * @return the movingRate
	 */
	public double getMovingRate() {
		return movingRate;
	}

	/**
	 * @param movingRate
	 *            the movingRate to set
	 */
	public void setMovingRate(double movingRate) {
		this.movingRate = movingRate;
	}

	/**
	 * @return the personsTracked
	 */
	public int getPersonsTracked() {
		return personsTracked;
	}

	/**
	 * @param personsTracked the personsTracked to set
	 */
	public void setPersonsTracked(int personsTracked) {
		this.personsTracked = personsTracked;
	}

	/**
	 * @return the bodyParts
	 */
	public List<Integer> getBodyParts() {
		return bodyParts;
	}

	/**
	 * @param bodyParts the bodyParts to set
	 */
	public void setBodyParts(List<Integer> bodyParts) {
		this.bodyParts = bodyParts;
	}

	/**
	 * @return the movingRatePerBodyPart
	 */
	public Map<Integer, Double> getMovingRatePerBodyPart() {
		return movingRatePerBodyPart;
	}

	/**
	 * @param movingRatePerBodyPart the movingRatePerBodyPart to set
	 */
	public void setMovingRatePerBodyPart(Map<Integer, Double> movingRatePerBodyPart) {
		this.movingRatePerBodyPart = movingRatePerBodyPart;
	}

	/**
	 * Returns the timestamp of this frame used for the movement engine.
	 * 
	 * @return the timestamp
	 */
	public long getTimestamp() {
		return timestamp;
	}

	/**
	 * Sets the timestamp of this frame.
	 * 
	 * @param timestamp the timestamp to set
	 */
	public void setTimestamp(long timestamp) {
		this.timestamp = timestamp;
	}

}
