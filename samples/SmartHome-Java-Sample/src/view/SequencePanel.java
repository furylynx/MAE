package view;

import java.awt.BorderLayout;
import java.io.IOException;
import java.io.StringReader;

import javax.swing.JPanel;

import maejava.LabanSequence;

import org.apache.batik.bridge.ViewBox;
import org.apache.batik.dom.svg.SAXSVGDocumentFactory;
import org.apache.batik.swing.JSVGCanvas;
import org.apache.batik.swing.JSVGScrollPane;
import org.apache.batik.util.XMLResourceDescriptor;
import org.w3c.dom.svg.SVGDocument;
import org.w3c.dom.svg.SVGSVGElement;

public class SequencePanel extends JPanel {
	
	private JSVGCanvas svgCanvas;
	

	public SequencePanel() {
		svgCanvas = new JSVGCanvas();
		svgCanvas.setDoubleBuffered(true);

		setLayout(new BorderLayout());
		add(svgCanvas, BorderLayout.CENTER);
	}

	private void updateSVG(SVGDocument doc) {
		svgCanvas.setSVGDocument(doc);
		
		svgCanvas.revalidate();
		svgCanvas.repaint();
	}
	
	public void update(LabanSequence sequence)
	{
		String svgString = sequence.svg(1920, 1080);
		
        StringReader reader = new StringReader(svgString);
        String uri = "nothing";
        
        String parser = XMLResourceDescriptor.getXMLParserClassName();
        SAXSVGDocumentFactory f = new SAXSVGDocumentFactory(parser);
        
		SVGDocument svgDoc = null;
		
		try {
			svgDoc = f.createSVGDocument(uri, reader);
		} catch (IOException ex) {
			ex.printStackTrace();
		}

		if (svgDoc != null) {
			SVGSVGElement svgRoot=(SVGSVGElement)svgDoc.getRootElement();
			svgRoot.setAttribute(ViewBox.SVG_VIEW_BOX_ATTRIBUTE,"0 0 1920 1080");
			
			updateSVG(svgDoc);
		}
	}

}
