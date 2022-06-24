/*
 * (C) Copyright IBM Corp. 2000,2001  All rights reserved.
 *
 * US Government Users Restricted Rights Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * The program is provided "as is" without any warranty express or
 * implied, including the warranty of non-infringement and the implied
 * warranties of merchantibility and fitness for a particular purpose.
 * IBM will not be liable for any damages suffered by you as a result
 * of using the Program. In no event will IBM be liable for any
 * special, indirect or consequential damages or lost profits even if
 * IBM has been advised of the possibility of their occurrence. IBM
 * will not be liable for any third party claims against you.
 */

package xkms;

import com.ibm.crypto.provider.IBMJCE;
import com.ibm.xml.dsig.KeyInfo;
import com.ibm.xml.dsig.ResourceShower;
import com.ibm.xml.dsig.SignatureContext;
import com.ibm.xml.dsig.Validity;
import com.ibm.xml.dsig.XSignature;
import com.ibm.xml.dsig.util.AdHocIDResolver;
import com.ibm.xml.dsig.util.SimpleKey;
import com.ibm.xml.sax.StandardErrorHandler;
import com.ibm.xml.xkms.XkmsService;
import com.ibm.xml.xkms.XkmsLocateParam;
import com.ibm.xml.xkms.XkmsLocateResult;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringWriter;
import java.io.Writer;
import java.security.Key;
import java.security.Security;
import java.security.cert.CertificateException;
import java.security.cert.X509CRL;
import java.security.cert.X509Certificate;
import java.util.Set;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import org.apache.xerces.parsers.DOMParser;
import org.apache.xml.serialize.DOMSerializer;
import org.apache.xml.serialize.OutputFormat;
import org.apache.xml.serialize.Serializer;
import org.apache.xml.serialize.XMLSerializer;
import org.w3c.dom.Document;                    // DOM Level 2!
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

/**
 *
 * @version $Id: VerifyXkms.java,v 1.3 2001/11/26 10:24:24 mak0702 Exp $
 * @author TAMURA Kent &lt;kent@trl.ibm.co.jp&gt;
 * @author Satoshi Makino &lt;mak0702@trl.ibm.co.jp&gt;
 */
public class VerifyXkms {

    static class TableModelImpl extends AbstractTableModel {
        static final String[] ids = {"Location", "Status"};
        Validity validity;

        TableModelImpl(Validity v) {
            this.validity = v;
        }

        public int getRowCount() {
            return this.validity.getNumberOfReferences();
        }
        public int getColumnCount() {
            return 2;
        }
        public String getColumnName(int column) {
            return ids[column];
        }
        public Object getValueAt(int row, int column) {
            switch (column) {
              case 0:
                return this.validity.getReferenceURI(row);
              case 1:
                boolean validp = this.validity.getReferenceValidity(row);
                return validp ? "OK" : "NG: " +
                    this.validity.getReferenceMessage(row);
            }
            return null;
        }
    }

    private static final String WINDOW_TITLE =
        "XML-Siganture Verifier with XKMS";

    public static void main(String[] argv) {
        InputStream is = null;
        int saveno = -1;
        String savename = null;
        Key key = null;
        String serviceURIa = null;
        String serviceURIs = null;

        Security.addProvider(new IBMJCE());
        //
        // Analyze the command line
        //
        for (int i = 0;  i < argv.length;  i ++) {
            if (argv[i].equals("-s")) {
                saveno = Integer.parseInt(argv[i+1]);
                savename = argv[i+2];
                i += 2;
            } else if (argv[i].equals("-soap")) { // SOAP server
                serviceURIs = argv[++i];
            } else if (argv[i].equals("-axis")) { // SOAP server - Axis
                serviceURIa = argv[++i];
            } else if (argv[i].equals("-keyfile")) {
                File keyfile = new File(argv[i+1]);
                int length = (int)keyfile.length();
                System.err.print("Reading a key file ...");
                byte[] rawkey = new byte[length];
                try {
                    FileInputStream fis = new FileInputStream(keyfile);
                    fis.read(rawkey);
                    fis.close();
                    System.err.println(" done: "+(length*8)+" bit");
                    key = new SimpleKey(rawkey);
                } catch (IOException ioe) {
                    System.err.println(ioe);
                }
                i++;
            } else {
                try {
                    is = new FileInputStream(argv[i]);
                    break;
                } catch (IOException ioe) {
                    System.err.println(ioe);
                }
            }
        }
        if (is == null)  is = System.in;

        JFrame frame = new JFrame
            ("Verifier for W3C/IETF XML-Signature with XKMS");
        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) { System.exit(0); }
        });
        JMenuBar menu = new JMenuBar();
        frame.setJMenuBar(menu);
        JMenu file = new JMenu("File");
        menu.add(file);
        file.add(new AbstractAction("Exit") {
            public void actionPerformed(ActionEvent ae) { System.exit(0); }
        });
        final int FRAMEWIDTH = 480, FRAMEHEIGHT = 320;
        Dimension screen = frame.getToolkit().getScreenSize();
        frame.setBounds
            ((screen.width-FRAMEWIDTH)/2, (screen.height-FRAMEHEIGHT)/2,
             FRAMEWIDTH, FRAMEHEIGHT);
        Container cont = frame.getContentPane();
        frame.show();

        try {
            //
            // Parses a signature document.
            //
            DOMParser parser = new DOMParser();
            InputSource isrc = new InputSource(is);
            parser.parse(isrc);
            Document doc = parser.getDocument();
            //
            // Searches for a Signature element
            //
            NodeList nodeList = doc.getElementsByTagNameNS
                (XSignature.XMLDSIG_NAMESPACE, "Signature");
            if (nodeList.getLength() == 0) {
                JOptionPane.showMessageDialog
                    (null, "The specified document has no Siganture element.",
                     WINDOW_TITLE, JOptionPane.ERROR_MESSAGE);
                System.exit(1);
            }
            Element signature = (Element)nodeList.item(0);

            SignatureContext sigContext = new SignatureContext();
            sigContext.setIDResolver(new AdHocIDResolver(doc));
            sigContext.setResourceShower(saveno < 0 ? null :
                                         new ShowerImpl(saveno, savename));

            //
            // Search for a KeyInfo element
            //
            Validity validity = null;
            Element keyInfoElement = KeyInfo.searchForKeyInfo(signature);
            if (keyInfoElement == null) {
                JOptionPane.showMessageDialog
                    (null, "This verifier does not support a signature " +
                     "without KeyInfo", WINDOW_TITLE, JOptionPane.ERROR_MESSAGE);
                System.exit(1);
            }

            //
            // Show the keyInfo
            //
            JOptionPane.showMessageDialog
                (null, "We have the following KeyInfo in the signed " +
                 "document:\n  " + summarize(keyInfoElement) +
                 "\n\nTrying to get a more detailed KeyInfo.",
                 WINDOW_TITLE, JOptionPane.INFORMATION_MESSAGE);
            /*
             * ================================================================
             * Get new KeyInfos via XKMS.
             * ================================================================
             */
            String protocol = serviceURIa == null ? "SOAP" : "SOAP/AXIS";
            String actionURI = "http://www.xkms.org/schema/xkms-2001-01-20";

            XkmsService xkms = XkmsService.getInstance(protocol);
            XkmsLocateParam lparam = xkms.createXkmsLocateParam();
            lparam.setKeyInfo(keyInfoElement);
            lparam.addRespond(XkmsLocateParam.RESPOND_KEYVALUE);
            lparam.addRespond(XkmsLocateParam.RESPOND_X509CERT);
            lparam.addRespond(XkmsLocateParam.RESPOND_X509CRL);
            lparam.setProperty(XkmsLocateParam.PROP_SOAP_SERVICE,
                               serviceURIa == null ? serviceURIs : serviceURIa);
            lparam.setProperty(XkmsLocateParam.PROP_SOAP_ACTION, actionURI);

            XkmsLocateResult lresult = xkms.locate(lparam);
            if (lresult.getResult() == XkmsLocateResult.RESULT_SUCCESS
                || lresult.getResult() == XkmsLocateResult.RESULT_INCOMPLETE) {
                System.err.println("Locate: Succeeded");
                java.util.Iterator iter =
                    lresult.getKeyInfoElements().iterator();
                while (iter.hasNext()) {
                    Element ki = (Element)iter.next();
                    JOptionPane.showMessageDialog
                        (null, "We got a KeyInfo from an XKMS service:\n  " + 
                         summarize(ki) + "\n\nVerifying the signature with " +
                         "this KeyInfo", WINDOW_TITLE,
                         JOptionPane.INFORMATION_MESSAGE);
                    validity = verify(sigContext, signature, ki);
                    if (validity != null && validity.getCoreValidity())
                        break;
                    JOptionPane.showMessageDialog
                        (null, "Failed to verify the signature with the " +
                         "KeyInfo.\n", WINDOW_TITLE,
                         JOptionPane.INFORMATION_MESSAGE);
                }
                if (validity == null)
                    System.exit(1);
            } else if (lresult.getResult() == XkmsLocateResult.RESULT_NOMATCH) {
                JOptionPane.showMessageDialog
                    (null, "No corresponding entry was found.", WINDOW_TITLE,
                     JOptionPane.ERROR_MESSAGE);
                System.exit(1);
            } else {
                JOptionPane.showMessageDialog
                    (null, "XKMS Locate has failed.", WINDOW_TITLE,
                     JOptionPane.ERROR_MESSAGE);
                System.exit(1);
            }
            /*
             * ================================================================
             */

            //
            // Creates result view
            //
            JPanel panel = new JPanel();
            panel.setLayout(new GridLayout(2, 1));
            JLabel lab = new JLabel(validity.getCoreValidity() ?
                                    "Core Validity: OK" : "Core Validity: NG");
            lab.setFont(new Font("Serif", Font.PLAIN, 30));
            panel.add(lab);
            String signedInfoMes = validity.getSignedInfoValidity()
                ? "Signature Validity: OK" : "Signature Validity: NG (" +
                    validity.getSignedInfoMessage()+")";
            lab = new JLabel(signedInfoMes);
            lab.setFont(new Font("Serif", Font.PLAIN, 25));
            panel.add(lab);
            cont.add(panel, "North");
            TableModelImpl impl = new TableModelImpl(validity);
            JTable table = new JTable(impl);
            table.setFont(new Font("Serif", Font.PLAIN, 20));

            cont.add(new JScrollPane(table));
            JButton button = new JButton(new AbstractAction("Exit") {
                public void actionPerformed(ActionEvent ae) { System.exit(0); }
            });
            cont.add(button, "South");
            button.requestFocus();
            cont.validate();
            cont.repaint();

        } catch (SAXException saxe) {
            Exception ex = saxe.getException();
            if (ex == null)  ex = saxe;
            JOptionPane.showMessageDialog
                (null, ex, WINDOW_TITLE, JOptionPane.ERROR_MESSAGE);
            ex.printStackTrace();
            System.exit(1);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog
                (null, ex, WINDOW_TITLE, JOptionPane.ERROR_MESSAGE);
            ex.printStackTrace();
            System.exit(1);
        }
    }

    static Validity verify(SignatureContext sigContext, Element signature,
                           Element keyInfoElement) {

        Key key = null;
        KeyInfo keyInfo;
        try {
            keyInfo = new KeyInfo(keyInfoElement);
        } catch (Exception ex) {
            return null;
        }

        Key keyInKeyValue = keyInfo.getKeyValue();
        if (keyInKeyValue != null) {
            //System.err.println("The signature has a KeyValue element.");
            //if (key == null)
            //key = keyInKeyValue;
        }

        KeyInfo.X509Data[] x5data = keyInfo.getX509Data();
        if (x5data != null && x5data.length > 0) {
            //System.err.println("The signature has one or more " +
            //                   "X509Data elements.");
            for (int i = 0;  i < x5data.length;  i++) {
                Key xkey = printX509DataInfo(x5data[i]);
                if (key == null) key = xkey;
            }
        }

        Element[] retrievals = keyInfo.getRetrievalMethods();
        if (retrievals != null && retrievals.length > 0) {
            //System.err.println
            //    ("The signature has one or more RetrievalMethod elements.");
            for (int i = 0;  i < retrievals.length;  i++) {
                String type = retrievals[i].getAttribute("Type");
                System.err.println("Type: "+type);
                if (type.equals(KeyInfo.X509DATA)) {
                    try {
                        KeyInfo.X509Data x5d =
                            (KeyInfo.X509Data)sigContext.retrieve(retrievals[i]);
                        Key xkey = printX509DataInfo(x5d);
                        if (key == null) {
                            //System.err.println
                            //    ("Uses a key from a RetrievalMethod.");
                            key = xkey;
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
            }
        }
        if (key == null) {
            System.err.println
                ("Locate: No valid key information in specified KeyInfo");
            return null;
        }

        //
        // Checks validity of the Signature element
        //
        long startTime = System.currentTimeMillis();
        Validity validity = sigContext.verify(signature, key);
        long elapsedTime = System.currentTimeMillis()-startTime;
        //System.err.println("Locate: Time to verify: "+elapsedTime+" [msec]");
        return validity;
    }

    /**
     * Print information in an X509Data and get a key.
     */
    static Key printX509DataInfo(KeyInfo.X509Data x5data) {
        //System.err.println("Checks an X509Data:");
        Key key = null;
        X509CRL crl = x5data.getCRL();
        if (crl != null) {
            System.err.println("Locate: CRL Information:");
            //System.err.println("\tVersion: "+crl.getVersion());
            System.err.println("\tIssuer: "+crl.getIssuerDN());
            //System.err.println("\tUpdated: "+crl.getThisUpdate());
            //System.err.println("\tNext update: "+crl.getNextUpdate());
            //Set certs = crl.getRevokedCertificates();
            //System.err.println("\tNumber of revoked certs: " +
            //                   (certs != null ? certs.size() : 0));
        }
        X509Certificate[] certs = x5data.getCertificates();
        if (certs == null || certs.length <= 0) {
            System.err.println("Locate: No certificates");
            return null;
        }
        //System.err.println("Locate: " + certs.length+" certificate(s).");
        for (int j = 0;  j < certs.length;  j++) {
            boolean revoked = false;
            X509Certificate cert = certs[j];
            System.err.println("Locate: Certificate Information:");
            //System.err.println("\tVersion: "+cert.getVersion());
            //String validity = "OK";
            //try {
            //    cert.checkValidity();
            //} catch (CertificateException certex) {
            //    validity = certex.getMessage();
            //}
            //System.err.println("\tValidity: "+validity);
            System.err.println("\tSubject: "+cert.getSubjectDN());
            System.err.println("\tIssuer: "+cert.getIssuerDN());
            System.err.println("\tSerial#: 0x" +
                               cert.getSerialNumber().toString(16));

            if (crl != null && crl.getIssuerDN().equals(cert.getIssuerDN())) {
                if (crl.getRevokedCertificate(cert.getSerialNumber()) != null) {
                    System.err.println("\tThis certificate was revoked!!!");
                    JOptionPane.showMessageDialog
                        (null, "The certificate was revoked.", WINDOW_TITLE,
                         JOptionPane.INFORMATION_MESSAGE);
                    revoked = true;
                }
            }
            /* XXX: This is not correct if we have a chain. */
            if (!revoked && key == null)
                key = cert.getPublicKey();
        }
        return key;
    }

    static class ShowerImpl implements ResourceShower {
        int number;
        String name;
        ShowerImpl(int no, String name) {
            this.number = no;
            this.name = name;
        }
        public void showSignedResource(Element owner, int count, String uri,
                                       String type, byte[] content,
                                       String encoding) {
            if (this.number == count) {
                try {
                    OutputStream os = new FileOutputStream(this.name);
                    os.write(content);
                    os.close();
                } catch (IOException ioe) {
                    ioe.printStackTrace();
                }
            }
        }
    }

    static String toString(Element node) throws IOException {
        StringWriter wr = new StringWriter();
        OutputFormat format =
            new OutputFormat(node.getOwnerDocument(), "UTF-8", false);
        format.setOmitXMLDeclaration(true);
        format.setPreserveSpace(true);
        Serializer ser = new XMLSerializer(format);
        ser.setOutputCharStream(wr);
        DOMSerializer domser = ser.asDOMSerializer();
        domser.serialize(node);
        wr.close();
        return wr.toString();
    }

    static String summarize(Element el) throws IOException {
        el.normalize();
        StringWriter wr = new StringWriter();
        summarize(wr, el);
        wr.close();
        return wr.toString();
    }
    private static void summarize(Writer wr, Node node) throws IOException {
        switch (node.getNodeType()) {
          case Node.ELEMENT_NODE:
            wr.write("<"+node.getNodeName());
            // attributes
            NamedNodeMap attrs = node.getAttributes();
            for (int i = 0;  i < attrs.getLength();  i++) {
                Node attr = attrs.item(i);
                // Incomplete
                wr.write(" "+attr.getNodeName()+"='"+attr.getNodeValue()+"'");
            }
            wr.write(">");
            for (Node ch = node.getFirstChild(); ch != null;
                 ch = ch.getNextSibling())
                summarize(wr, ch);
            wr.write("</"+node.getNodeName()+">");
            break;
          case Node.ENTITY_REFERENCE_NODE:
            for (Node ch = node.getFirstChild(); ch != null;
                 ch = ch.getNextSibling())
                summarize(wr, ch);
            break;
          case Node.TEXT_NODE:
            String t = node.getNodeValue();
            int lf0 = t.indexOf("\n\n");
            if(lf0 >= 0) t = t.substring(0, lf0) + t.substring(lf0 + 1);
            int lf = t.indexOf('\n');
            if (lf >= 0 && t.length() > 80) {
                char[] before = t.toCharArray();
                char[] after = new char[before.length];
                int ptr = 0;
                for(int i = 0; i < before.length; i ++) {
                    if(!Character.isWhitespace(before[i]) &&
                       !Character.isISOControl(before[i])) {
                        after[ptr] = before[i];
                        ptr ++;
                    }
                }
                t = String.valueOf(after, 0, ptr);
                t = t.substring(0, 10) + "...(snip)..." +
                    t.substring(t.length() - 10);
            }
            wr.write(t);
            break;
          case Node.COMMENT_NODE: // Ignore
          case Node.PROCESSING_INSTRUCTION_NODE: // Ignore
          default:              // Ignore
            break;
        }
    }
}
