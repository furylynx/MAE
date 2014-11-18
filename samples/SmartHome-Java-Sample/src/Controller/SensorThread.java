package Controller;

import java.util.List;

import maejava.Bone;
import maejava.BoneVector;
import maejava.ColumnDefinition;
import maejava.ColumnDefinitionVector;
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
	 * @param tolerance The tolerance to be set. Tolerance is given in beats (1 beat is 200ms).
	 * @param bodyParts The body parts to be used.
	 * @param columnDefinitions The column definitions to be used.
	 * @param sequencesToRegister The sequence to be registered.
	 */
	public SensorThread(SensorInfo info, long startingTimeStamp, double tolerance, BoneVector bodyParts, ColumnDefinitionVector columnDefinitions, List<LabanSequence> sequencesToRegister) {
		this.setInfo(info);
		this.running = true;
		
		niteController = new NiteController(info.getDeviceInfo(), "SamplesConfig.xml");
		
		//framerate is assumed to be 30fps, pose buffer is set to 300 frames = 10 s
		movementController = new WrappedMovementController(bodyParts, columnDefinitions, 300);
		movementController.setRecognitionTolerance(tolerance);
		
		//register all sequences
		for (LabanSequence sequence : sequencesToRegister)
		{
			movementController.registerSequence(sequence);
		}
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
				System.out.println(">> SensorThread.run - Sensor data received");
				
				//process sensor data
				int timestamp = (int)(System.currentTimeMillis() - startingTimeStamp);
				movementController.nextFrame(timestamp, sensorData.get(0));
				
				currentSequence = movementController.getCurrentSequence();
				currentRecognition = movementController.getCurrentRecognition();
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
