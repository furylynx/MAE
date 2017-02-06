package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.math.BigInteger;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JPanel;

import maejava.LabanSequence;
import maejava.LabanSequenceVector;

public class RecognitionPanel extends JPanel {

	JList<String> recognitionList;
	DefaultListModel<String> recognitionListModel;
	int maxSize;
	
	public RecognitionPanel()
	{
		super();
		
		maxSize = 20;
		
		initialize();
	}
	
	public RecognitionPanel(int maxSize)
	{
		super();
		
		this.maxSize = maxSize;

		initialize();
	}
	
	private void initialize()
	{
		setBackground(Color.WHITE);
		
		recognitionListModel = new DefaultListModel<String>();
		recognitionList = new JList<String>(recognitionListModel);
		
		add(recognitionList, BorderLayout.CENTER);
	}
	
	public void addRecognition(BigInteger timestamp, LabanSequence recognizedSequence)
	{
		if (recognizedSequence != null)
		{
			Date date = new Date(timestamp.longValue());
			DateFormat format = new SimpleDateFormat("HH:mm:ss");
			
			recognitionListModel.addElement(format.format(date)+" "+recognizedSequence.getTitle());
			
			while (recognitionListModel.size() > maxSize)
			{
				recognitionListModel.remove(0);
			}
		}
	}
	
	public void addRecognition(BigInteger timestamp, LabanSequenceVector recognizedSequences)
	{
		for(int i = 0; i < recognizedSequences.size(); i++)
		{
			addRecognition(timestamp, recognizedSequences.get(i));
		}
	}
}
