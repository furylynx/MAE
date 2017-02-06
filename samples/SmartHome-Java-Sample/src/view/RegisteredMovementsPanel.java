package view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.StringReader;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.DefaultListCellRenderer;
import javax.swing.JComboBox;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import org.apache.batik.bridge.ViewBox;
import org.apache.batik.dom.svg.SAXSVGDocumentFactory;
import org.apache.batik.swing.JSVGCanvas;
import org.apache.batik.util.XMLResourceDescriptor;
import org.w3c.dom.svg.SVGDocument;
import org.w3c.dom.svg.SVGSVGElement;

import maejava.LabanSequence;

public class RegisteredMovementsPanel extends JPanel {

	List<LabanSequence> registeredSequences;
	JList<LabanSequence> sequencesJList;

	JSVGCanvas activePane;

	public RegisteredMovementsPanel(List<LabanSequence> registeredSequences) {
		this.registeredSequences = registeredSequences;

		setLayout(new BorderLayout());

		sequencesJList = new JList<LabanSequence>(
				registeredSequences.toArray(new LabanSequence[0]));

		sequencesJList.setCellRenderer(new DefaultListCellRenderer() {
			/**
			 * Serial version ID.
			 */
			private static final long serialVersionUID = 1L;

			@Override
			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				if (value != null) {
					LabanSequence sequence = (LabanSequence) value;
					value = sequence.getTitle();
				}

				return super.getListCellRendererComponent(list, value, index,
						isSelected, cellHasFocus);
			}
		});

		sequencesJList.addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				@SuppressWarnings("unchecked")
				JList<LabanSequence> combo = (JList<LabanSequence>) e
						.getSource();
				LabanSequence selectedSequence = (LabanSequence) combo
						.getSelectedValue();
				
				if (activePane != null) {
					remove(activePane);
				}
				
				JSVGCanvas canvas = new JSVGCanvas();
				canvas.setDisableInteractions(true);

				StringReader reader = new StringReader(selectedSequence.svg(1920, 1080));
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

					canvas.setSVGDocument(svgDoc);
				}

				activePane = canvas;


				if (activePane != null) {
					add(activePane, BorderLayout.CENTER);
					activePane.revalidate();
					activePane.repaint();
				}
				
				revalidate();
				repaint();

			}
		});

		add(sequencesJList, BorderLayout.WEST);
		
		for (int i = 0; i < registeredSequences.size(); i++)
		{
			sequencesJList.setSelectedIndex(i);
		}

	}

}
