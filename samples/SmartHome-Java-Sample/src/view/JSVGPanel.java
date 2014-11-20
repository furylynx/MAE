package view;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.io.IOException;
import java.io.StringReader;
import java.net.URI;

import javax.swing.JPanel;

import org.apache.batik.dom.svg.SAXSVGDocumentFactory;
import org.apache.batik.util.XMLResourceDescriptor;
import org.w3c.dom.svg.SVGDocument;

import com.kitfox.svg.SVGDiagram;
import com.kitfox.svg.SVGException;
import com.kitfox.svg.SVGUniverse;

public class JSVGPanel extends JPanel{

	SVGDiagram svg;
	
	public JSVGPanel()
	{
		
	}
	
	public void update(SVGDiagram diagram)
	{
		System.out.println("DIAGRAM!");
		this.svg = diagram;
		revalidate();
		repaint();
	}
	
	public void update(String svgString)
	{
		SVGUniverse svgUniverse = new SVGUniverse();
		
		StringReader reader = new StringReader(svgString);
		
		URI uri = svgUniverse.loadSVG(reader, "SVG");
		SVGDiagram diagram = svgUniverse.getDiagram(uri);
		
		update(diagram);
	}
	
	@Override
	public void paintComponent(Graphics g)
    {
		super.paintComponent(g);

        final int width = getWidth();
        final int height = getHeight();
        
        g.setColor(getBackground());
        g.fillRect(0, 0, width, height);
        
        if (svg != null)
        {
        	try {
				svg.render((Graphics2D) g);
			} catch (SVGException e) {
				e.printStackTrace();
			}
        }
    }
}
