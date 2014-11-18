package Main;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;

import maejava.Bone;
import maejava.BoneVector;
import maejava.ColumnDefinition;
import maejava.ColumnDefinitionVector;
import maejava.EBone;
import maejava.EBoneC;
import maejava.IniReader;
import maejava.LabanSequence;
import maejava.LabanSequenceReader;
import maenitejava.DeviceInfo;
import maenitejava.NiteFarm;
import Controller.SensorThread;
import Model.PositionInfo;
import Model.SensorInfo;
import View.SmartHomePanel;

public class SmartHomeJavaSample {

	public static void main(String[] args) {
		long timestampAtStartup = System.currentTimeMillis();

		// -- read configuration file
		IniReader iniReader = new IniReader("config.ini");

		// read room and device info
		int roomCount = 0;
		int deviceCount = 0;
		try {
			roomCount = Integer.parseInt(iniReader.getValue("general",
					"roomcount"));
			deviceCount = Integer.parseInt(iniReader.getValue("general",
					"devicecount"));
		} catch (Exception e) {
			e.printStackTrace();
		}

		List<PositionInfo> posList = new ArrayList<PositionInfo>();
		for (int i = 0; i < roomCount; i++) {
			try {
				int positionId = i;
				String positionName = iniReader.getValue("room" + i,
						"positionname");
				int xpos = Integer.parseInt(iniReader.getValue("room" + i,
						"xpos"));
				int ypos = Integer.parseInt(iniReader.getValue("room" + i,
						"ypos"));
				int width = Integer.parseInt(iniReader.getValue("room" + i,
						"width"));
				int height = Integer.parseInt(iniReader.getValue("room" + i,
						"height"));

				posList.add(new PositionInfo(positionId, positionName, xpos,
						ypos, width, height));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		List<SensorInfo> deviceList = new ArrayList<SensorInfo>();
		List<String> deviceStrings = new ArrayList<String>();
		for (int i = 0; i < deviceCount; i++) {
			try {
				int positionId = Integer.parseInt(iniReader.getValue("device"
						+ i, "positionid"));
				String serialNumber = iniReader.getValue("device" + i,
						"serialnumber");

				DeviceInfo deviceInfo = NiteFarm.getDeviceInfo(serialNumber);

				deviceStrings.add(deviceInfo.getDeviceName());

				deviceList.add(new SensorInfo(posList.get(positionId),
						deviceInfo));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		// read tolerance and bodyparts

		double tolerance = 2.0;
		String bodyPartsString = "";
		String sequencesDir = "sequences" + File.separator;
		try {
			tolerance = Double.parseDouble(iniReader.getValue("general",
					"tolerance"));
			bodyPartsString = iniReader.getValue("general", "bodyparts");
		} catch (Exception e) {
			e.printStackTrace();
		}

		BoneVector bodyParts = Bone.defaultBones();
		ColumnDefinitionVector columnDefinitions = ColumnDefinition
				.defaultDefinitions();

		if (bodyPartsString.length() > 0) {
			String[] bodyPartsSplit = bodyPartsString.split(",");

			for (String str : bodyPartsSplit) {
				try {
					EBone eb = EBoneC.parse(str.trim());
					Bone b = new Bone(eb);
					bodyParts.pushBack(b);

					if (Math.abs(b.getId()) != 1 && Math.abs(b.getId()) != 2
							&& Math.abs(b.getId()) != 4) {
						// generate column definition for the bone
						columnDefinitions.pushBack(new ColumnDefinition(eb));
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		// read the sequences to be registered
		List<LabanSequence> sequencesToRegister = new ArrayList<LabanSequence>();
		LabanSequenceReader labanReader = new LabanSequenceReader();

		for (File file : new File(sequencesDir).listFiles()) {
			if (file.isFile() && file.getName().endsWith(".laban")) {
				try {
					LabanSequence sequence = labanReader.readSequenceFile(file
							.getPath());

					if (sequence != null) {
						System.out.println("Registering sequence: "
								+ sequence.getTitle());
						sequencesToRegister.add(sequence);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		// -- Initialize the GUI --

		// initialize the panel
		SmartHomePanel smartHomePanel = new SmartHomePanel(deviceStrings,
				posList, sequencesToRegister);

		// register panel as observer to all sensor infos
		for (SensorInfo sensorInfo : deviceList) {
			sensorInfo.addObserver(smartHomePanel);
		}

		// initialize the window
		JFrame frame = new JFrame("SmartHome - Movement Analysis Engine");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		frame.getContentPane().add(smartHomePanel, BorderLayout.CENTER);
		frame.setMinimumSize(new Dimension(640, 360));

		frame.pack();
		frame.setVisible(true);

		// -- Initialize the threads --
		for (SensorInfo sensorInfo : deviceList) {
			(new Thread(new SensorThread(sensorInfo, timestampAtStartup,
					tolerance, bodyParts, columnDefinitions,
					sequencesToRegister))).start();
		}

	}

}
