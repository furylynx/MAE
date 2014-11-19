package View;

import java.awt.BorderLayout;
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

import org.apache.batik.dom.svg.SAXSVGDocumentFactory;
import org.apache.batik.swing.JSVGCanvas;
import org.apache.batik.swing.JSVGScrollPane;
import org.apache.batik.util.XMLResourceDescriptor;

import maejava.LabanSequence;

public class RegisteredMovementsPanel extends JPanel {

	List<LabanSequence> registeredSequences;
	JList<LabanSequence> comboBox;
	Map<LabanSequence, JSVGScrollPane> svgPanels;

	JSVGScrollPane activePane;

	public RegisteredMovementsPanel(List<LabanSequence> registeredSequences) {
		this.registeredSequences = registeredSequences;
		svgPanels = new HashMap<LabanSequence, JSVGScrollPane>();
		setLayout(new BorderLayout());

		comboBox = new JList<LabanSequence>(registeredSequences.toArray(new LabanSequence[0]));
		
		for (LabanSequence sequence : registeredSequences) {
			JSVGCanvas canvas = new JSVGCanvas();

			StringReader reader = new StringReader(sequence.svg(1920, 1080));
			String uri = "nothing";

			String parser = XMLResourceDescriptor.getXMLParserClassName();
			SAXSVGDocumentFactory f = new SAXSVGDocumentFactory(parser);

			try {
				canvas.setSVGDocument(f.createSVGDocument(uri, reader));
			} catch (IOException e) {
				e.printStackTrace();
			}

			svgPanels.put(sequence, new JSVGScrollPane(canvas));
		} 
		
		comboBox.setCellRenderer(new DefaultListCellRenderer() {
			/**
			 * Serial version ID.
			 */
			private static final long serialVersionUID = 1L;

			@Override
			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				if (value != null)
				{
					LabanSequence sequence = (LabanSequence) value;
					value = sequence.getTitle();
				}
				
				return super.getListCellRendererComponent(list, value, index,
						isSelected, cellHasFocus);
			}
		});

		comboBox.addListSelectionListener(new ListSelectionListener() {
			
			@Override
			public void valueChanged(ListSelectionEvent e) {
				JList<LabanSequence> combo = (JList<LabanSequence>) e
						.getSource();
				LabanSequence selectedSequence = (LabanSequence) combo
						.getSelectedValue();

				if (activePane != null) {
					remove(activePane);
				}

				activePane = svgPanels.get(selectedSequence);

				if (activePane != null) {
					add(activePane, BorderLayout.CENTER);
				}
				
			}
		}
		);


		add(comboBox, BorderLayout.WEST);

	}

}
