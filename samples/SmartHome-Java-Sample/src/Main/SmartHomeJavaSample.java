package Main;

import java.awt.BorderLayout;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.prefs.Preferences;

import javax.swing.JFrame;
import javax.swing.text.Position;

import maejava.IniReader;
import maenitejava.NiteFarm;
import Controller.SensorThread;
import Model.PositionInfo;
import Model.SensorInfo;
import View.SmartHomePanel;

public class SmartHomeJavaSample {

	public static void main(String[] args) {
		long timestampAtStartup = System.currentTimeMillis();

		//-- read configuration file
		IniReader iniReader = new IniReader("config.ini");
		
		int roomCount = 0;
		int deviceCount = 0;
		try{
			roomCount = Integer.parseInt(iniReader.getValue("general", "roomcount"));
			deviceCount = Integer.parseInt(iniReader.getValue("general", "devicecount"));
		}catch(Exception e)
		{
			e.printStackTrace();
		}
		

		
		List<PositionInfo> posList = new ArrayList<PositionInfo>();
		for (int i = 0; i < roomCount; i++)
		{
			try
			{
				
				int positionId = i;
				String positionName = iniReader.getValue("room"+i, "positionname");
				int xpos = Integer.parseInt(iniReader.getValue("room"+i, "xpos"));
				int ypos = Integer.parseInt(iniReader.getValue("room"+i, "ypos"));
				int width = Integer.parseInt(iniReader.getValue("room"+i, "width"));
				int height = Integer.parseInt(iniReader.getValue("room"+i, "height"));
				
				posList.add(new PositionInfo(positionId, positionName, xpos, ypos, width, height));
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
		
		List<SensorInfo> deviceList = new ArrayList<SensorInfo>();
		for (int i = 0; i < deviceCount; i++)
		{
			try
			{
				int positionId = Integer.parseInt(iniReader.getValue("device"+i, "positionid"));
				String serialNumber = iniReader.getValue("device"+i, "serialnumber");
				
				deviceList.add(new SensorInfo(posList.get(positionId), NiteFarm.getDeviceInfo(serialNumber)));
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
		
		//-- Initialize the GUI --
		
		//initialize the panel
		SmartHomePanel smartHomePanel = new SmartHomePanel();

		//register panel as observer to all sensor infos
		for (SensorInfo sensorInfo : deviceList)
		{
			sensorInfo.addObserver(smartHomePanel);
		}
		
		//initialize the window
		JFrame frame = new JFrame("SmartHome - Movement Analysis Engine");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(smartHomePanel, BorderLayout.CENTER);

		frame.pack();
		frame.setVisible(true);
		
		//-- Initialize the threads --
		for (SensorInfo sensorInfo : deviceList)
		{
			(new Thread(new SensorThread(sensorInfo, timestampAtStartup))).start();
		}

	}

}
