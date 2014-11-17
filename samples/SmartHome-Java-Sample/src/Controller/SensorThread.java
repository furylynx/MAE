package Controller;

import maejava.Bone;
import maejava.ColumnDefinition;
import maejava.GeneralSkeletonVector;
import maejava.LabanSequence;
import maejava.LabanSequenceVector;
import maejavawrapper.WrappedMovementController;
import maenitejava.NiteController;
import Model.SensorInfo;

public class SensorThread implements Runnable {

	private SensorInfo info;
	
	private NiteController niteController;
	private WrappedMovementController movementController;
	
	private boolean running;
	
	private long startingTimeStamp;
	
	/**
	 * Creates a new thread that handles sensor input.
	 * 
	 * @param info The sensor info object to which the data will be written.
	 * @param startingTimeStamp The starting time stamp.
	 */
	public SensorThread(SensorInfo info, long startingTimeStamp) {
		this.setInfo(info);
		this.running = false;
		
		niteController = new NiteController(info.getDeviceInfo(), "SamplesConfig.xml");
		
		movementController = new WrappedMovementController(Bone.defaultBones(), ColumnDefinition.defaultDefinitions());
	}

	@Override
	public void run() {

		while (running)
		{
			//retrieve sensor data
			GeneralSkeletonVector sensorData = niteController.waitForUpdate();
			
			LabanSequence currentSequence = null;
			LabanSequenceVector currentRecognition = null;
			
			//for simplification, the movement data is only analysed for the first user
			if (!sensorData.empty() && sensorData.get(0) != null)
			{
				//process sensor data
				int timestamp = (int)(System.currentTimeMillis() - startingTimeStamp);
				movementController.nextFrame(timestamp, sensorData.get(0));
			}
			
			//handle sensor data
			info.nextFrame(sensorData, currentSequence, currentRecognition);
		}
	}
	

	/**
	 * Returns true if this thread is still running.
	 * 
	 * @return True if running.
	 */
	public boolean isRunning() {
		return running;
	}
	
	/**
	 * Stops this thread.
	 */
	public void stop()
	{
		running = false;
	}

	/**
	 * Returns the sensor information.
	 * 
	 * @return the sensor info.
	 */
	public SensorInfo getInfo() {
		return info;
	}

	/**
	 * Sets the sensor information.
	 * 
	 * @param info the sensor info to set
	 */
	public void setInfo(SensorInfo info) {
		this.info = info;
	}

}
