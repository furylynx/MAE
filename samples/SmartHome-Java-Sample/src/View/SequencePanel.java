package View;

import java.awt.BorderLayout;
import java.io.IOException;
import java.io.StringReader;

import javax.swing.JPanel;

import org.apache.batik.dom.svg.SAXSVGDocumentFactory;
import org.apache.batik.swing.JSVGCanvas;
import org.apache.batik.swing.JSVGScrollPane;
import org.apache.batik.util.XMLResourceDescriptor;
import org.w3c.dom.svg.SVGDocument;

public class SequencePanel extends JPanel {

	/**
	 * Serial version ID.
	 */
	private static final long serialVersionUID = -2062414238196829924L;
	
	private JSVGScrollPane svgPane;
	private JSVGCanvas svgCanvas;

	public SequencePanel() {
		svgCanvas = new JSVGCanvas();
		svgPane = new JSVGScrollPane(svgCanvas);

		add(svgPane, BorderLayout.CENTER);
	}

	public void updateSVG(SVGDocument doc) {
		svgCanvas.setSVGDocument(doc);
		svgCanvas.repaint();
	}

	public void updateSVG(String svgString) {
        StringReader reader = new StringReader(svgString);
        String uri = "nothing";
        
        String parser = XMLResourceDescriptor.getXMLParserClassName();
        SAXSVGDocumentFactory f = new SAXSVGDocumentFactory(parser);
        
        try {
			updateSVG(f.createSVGDocument(uri, reader));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
