package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.util.List;

import javax.swing.JPanel;

import model.PositionInfo;
import model.SensorInfo;

public class FloorPlanPanel extends JPanel {
	
	
	List<PositionInfo> positions;
	
	int maxXPos;
	int maxYPos;

	public FloorPlanPanel(List<PositionInfo> positions)
	{
		this.positions = positions;
		maxXPos = 0;
		maxYPos = 0;
		
		//max positions
		for (PositionInfo info : positions)
		{
			if (info.getXpos()+info.getWidth() > maxXPos)
			{
				maxXPos = info.getXpos()+info.getWidth();
			}
			
			if (info.getYpos()+info.getHeight() > maxYPos)
			{
				maxYPos = info.getYpos()+info.getHeight();
			}
		}
		
		setLayout(new BorderLayout());
		
		//TODO do things in here
		//draw floor plan, add user info(s) when updated
	}
	
	public void paintComponent(Graphics g) {
        super.paintComponent(g);       

        // Draw Text
        for (PositionInfo info : positions)
        {
        	//TODO select color
        	g.setColor(Color.GRAY.darker());
        	
        	//TODO make relative
        	g.fillRect(info.getXpos(), info.getYpos(), info.getWidth(), info.getHeight());
        }
    }  

	public void updateSensorInfo(SensorInfo sensorInfo) {
		//TODO update the floor plan
	}
}
