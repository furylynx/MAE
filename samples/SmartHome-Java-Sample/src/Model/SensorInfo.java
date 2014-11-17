package Model;

import java.util.Observable;

import maejava.GeneralSkeletonVector;
import maejava.LabanSequence;
import maejava.LabanSequenceVector;
import maenitejava.DeviceInfo;

public class SensorInfo extends Observable {

	private PositionInfo position;

	private DeviceInfo deviceInfo;

	private GeneralSkeletonVector sensorData;

	private LabanSequence currentSequence;

	private LabanSequenceVector currentRecognition;

	private double movingRate;

	// TODO more useful info that can be displayed??

	/**
	 * Creates a new sensor info object.
	 * 
	 * @param position
	 *            The room position
	 * @param deviceInfo
	 *            The device info.
	 */
	public SensorInfo(PositionInfo position, DeviceInfo deviceInfo) {
		this.position = position;
		this.deviceInfo = deviceInfo;
	}

	/**
	 * Creates a new sensor info object.
	 * 
	 * @param position
	 *            The position info.
	 * @param serialNumber
	 *            The serial number of the corresponding device.
	 */
	public SensorInfo(PositionInfo position, String serialNumber) {
		this.position = position;

		// TODO do things; retrieve serial number etc
		// TODO requires the wrapper for the nite_farm !!!

	}

	/**
	 * Processses the next frame of the sensor data.
	 * 
	 * @param sensorData
	 * @param currentSequence
	 * @param currentRecognition
	 */
	public void nextFrame(GeneralSkeletonVector sensorData,
			LabanSequence currentSequence,
			LabanSequenceVector currentRecognition) {

		this.sensorData = sensorData;
		this.currentSequence = currentSequence;
		this.currentRecognition = currentRecognition;

		// TODO calculate the moving rate

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

}
