package Main;

import java.awt.BorderLayout;

import javax.swing.JFrame;

import Controller.SensorThread;
import Model.SensorInfo;
import View.SmartHomePanel;

public class SmartHomeJavaSample {

	public static void main(String[] args) {
		long timestampAtStartup = System.currentTimeMillis();

		//TODO initialize the MAE threads to run
		
		
		SensorInfo firstSensorInfo = null;
		//TODO get sensor info for first device
		//TODO get sensor info for all devices...
		//use IniReader for this...
		
		//-- Initialize the GUI --
		
		//initialize the panel
		SmartHomePanel smartHomePanel = new SmartHomePanel();
		firstSensorInfo.addObserver(smartHomePanel);
		//TODO make smartHomePanel observe all SensorInfos
		
		//initialize the window
		JFrame frame = new JFrame("SmartHome - Movement Analysis Engine");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(smartHomePanel, BorderLayout.CENTER);

		frame.pack();
		frame.setVisible(true);
		
		//-- Initialize the threads --
		SensorThread firstSensorThread = new SensorThread(firstSensorInfo, timestampAtStartup);
		//TODO initialize threads for all SensorInfos
		
		//run the threads
		 (new Thread(firstSensorThread)).start();
		
	}

}
