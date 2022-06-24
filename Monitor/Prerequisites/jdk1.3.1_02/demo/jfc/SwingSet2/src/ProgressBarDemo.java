/*
 * @(#)ProgressBarDemo.java	1.2 99/10/12
 *
 * Copyright (c) 1997-1999 by Sun Microsystems, Inc. All Rights Reserved.
 * 
 * Sun grants you ("Licensee") a non-exclusive, royalty free, license to use,
 * modify and redistribute this software in source and binary code form,
 * provided that i) this copyright notice and license appear on all copies of
 * the software; and ii) Licensee does not utilize the software in a manner
 * which is disparaging to Sun.
 * 
 * This software is provided "AS IS," without a warranty of any kind. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
 * IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN AND ITS LICENSORS SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING
 * OR DISTRIBUTING THE SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN OR ITS
 * LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR DIRECT,
 * INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES, HOWEVER
 * CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING OUT OF THE USE OF
 * OR INABILITY TO USE SOFTWARE, EVEN IF SUN HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 * This software is not designed or intended for use in on-line control of
 * aircraft, air traffic, aircraft navigation or aircraft communications; or in
 * the design, construction, operation or maintenance of any nuclear
 * facility. Licensee represents and warrants that it will not use or
 * redistribute the Software for such purposes.
 */


import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.border.*;
import javax.swing.colorchooser.*;
import javax.swing.filechooser.*;
import javax.accessibility.*;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import java.io.*;
import java.applet.*;
import java.net.*;

/**
 * JProgressBar Demo
 *
 * @version 1.2 10/12/99
 * @author Jeff Dinkins
 # @author Peter Korn (accessibility support)
 */
public class ProgressBarDemo extends DemoModule {

    /**
     * main method allows us to run as a standalone demo.
     */
    public static void main(String[] args) {
	ProgressBarDemo demo = new ProgressBarDemo(null);
	demo.mainImpl();
    }

    /**
     * ProgressBarDemo Constructor
     */
    public ProgressBarDemo(SwingSet2 swingset) {
	// Set the title for this demo, and an icon used to represent this
	// demo inside the SwingSet2 app.
	super(swingset, "ProgressBarDemo", "toolbar/JProgressBar.gif");

	createProgressPanel();
    }

    javax.swing.Timer timer;
    Action loadAction;
    Action stopAction;
    JProgressBar progressBar;
    JTextArea progressTextArea;
    
    public void createProgressPanel() {
	getDemoPanel().setLayout(new BorderLayout());

	JPanel textWrapper = new JPanel(new BorderLayout());
	textWrapper.setBorder(new SoftBevelBorder(BevelBorder.LOWERED));
	textWrapper.setAlignmentX(LEFT_ALIGNMENT);
	progressTextArea = new MyTextArea();
	progressTextArea.getAccessibleContext().setAccessibleName(getString("ProgressBarDemo.accessible_text_area_name"));
	progressTextArea.getAccessibleContext().setAccessibleName(getString("ProgressBarDemo.accessible_text_area_description"));
	textWrapper.add(progressTextArea, BorderLayout.CENTER);

	getDemoPanel().add(textWrapper, BorderLayout.CENTER);

	JPanel progressPanel = new JPanel();
	getDemoPanel().add(progressPanel, BorderLayout.SOUTH);

	progressBar = new JProgressBar(JProgressBar.HORIZONTAL, 0, text.length()) {
	    public Dimension getPreferredSize() {
		return new Dimension(300, super.getPreferredSize().height);
	    }
	};
	progressBar.getAccessibleContext().setAccessibleName(getString("ProgressBarDemo.accessible_text_loading_progress"));

	progressPanel.add(progressBar);
	progressPanel.add(createLoadButton());
	progressPanel.add(createStopButton());
    }

    public JButton createLoadButton() {
	loadAction = new AbstractAction(getString("ProgressBarDemo.start_button")) {
	    public void actionPerformed(ActionEvent e) {
		if(timer == null) {
		    loadAction.setEnabled(false);
		    stopAction.setEnabled(true);
		    timer = new javax.swing.Timer(18, createTextLoadAction());
		    timer.start();
		}
	    }
	};
	return createButton(loadAction);
    }

    public JButton createStopButton() {
	stopAction = new AbstractAction(getString("ProgressBarDemo.stop_button")) {
	    public void actionPerformed(ActionEvent e) {
		if(timer != null) {
		    timer.stop();
		    timer = null;
		}
		loadAction.setEnabled(true);
		stopAction.setEnabled(false);
	    }
	};
	return createButton(stopAction);
    }

    public JButton createButton(Action a) {
	JButton b = new JButton();
	// setting the following client property informs the button to show
	// the action text as it's name. The default is to not show the
	// action text.
	b.putClientProperty("displayActionText", Boolean.TRUE);
	b.setAction(a);
	return b;
    }


    int textLocation = 0;

    String text = getString("ProgressBarDemo.text");

    public Action createTextLoadAction() {
	return new AbstractAction("text load action") {
	    public void actionPerformed (ActionEvent e) {
		if(progressBar.getValue() < progressBar.getMaximum()) {
		    progressBar.setValue(progressBar.getValue() + 1);
		    progressTextArea.append(text.substring(textLocation, textLocation+1));
		    textLocation++;
		} else {
		    if(timer != null) {
			timer.stop();
			timer = null;
			loadAction.setEnabled(true);
			stopAction.setEnabled(false);
		    }
		}
	    }
	};
    }


    class MyTextArea extends JTextArea {
        public MyTextArea() {
            super(null, 0, 0);
	    setEditable(false);
	    setText("");
        }

        public float getAlignmentX () {
            return LEFT_ALIGNMENT;
        }
 
        public float getAlignmentY () {
            return TOP_ALIGNMENT;
        }
    }
}


