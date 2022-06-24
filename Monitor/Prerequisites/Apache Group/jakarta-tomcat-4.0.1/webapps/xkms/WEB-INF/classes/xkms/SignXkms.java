/*
 * (C) Copyright IBM Corp. 1999,2000,2001  All rights reserved.
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
import com.ibm.xml.dsig.AlgorithmFactory;
import com.ibm.xml.dsig.IDResolver;
import com.ibm.xml.dsig.KeyInfo;
import com.ibm.xml.dsig.ResourceShower;
import com.ibm.xml.dsig.SignatureContext;
import com.ibm.xml.dsig.SignatureStructureException;
import com.ibm.xml.dsig.TransformException;
import com.ibm.xml.dsig.XSignature;
import com.ibm.xml.dsig.util.AdHocIDResolver;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.Security;
import java.security.SignatureException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Hashtable;
import javax.xml.parsers.ParserConfigurationException;
import org.apache.xerces.parsers.DOMParser;
import org.apache.xml.serialize.DOMSerializer;
import org.apache.xml.serialize.OutputFormat;
import org.apache.xml.serialize.Serializer;
import org.apache.xml.serialize.XMLSerializer;
import org.w3c.dom.Document;                    // This requires DOM L2!
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 *
 * @version $Id: SignXkms.java,v 1.3 2001/11/26 10:24:24 mak0702 Exp $
 * @author TAMURA Kent &lt;kent@trl.ibm.co.jp&gt;
 * @author Satoshi Makino &lt;mak0702@trl.ibm.co.jp&gt;
 */
public class SignXkms {
    public static void main(String[] argv) throws Exception {
        String keystorepath =
            System.getProperty("user.home")+File.separator+".keystore";
        String keystoretype = "JKS";
        String alias = null;
        char[] storepass = null;
        char[] keypass = null;
        String templateURI = null;

        Security.addProvider(new IBMJCE());
        int i;
        for (i = 0;  i < argv.length;  i++) {
            if (argv[i].equals("-keystore") && i+1 < argv.length) {
                keystorepath = argv[++i];
            } else if (argv[i].equals("-keystoretype") && i+1 < argv.length) {
                keystoretype = argv[++i];
            } else if (alias == null) {
                alias = argv[i];
            } else if (storepass == null) {
                storepass = argv[i].toCharArray();
            } else if (keypass == null) {
                keypass = argv[i].toCharArray();
            } else if (templateURI == null) {
                templateURI = argv[i];
            }
        }
        if (templateURI == null || i < argv.length) {
            System.err.println("");
            System.err.println("Usage: TemplateSign [-keystore " +
                               "<path-to-keystore-file>] [-keystoretype " +
                               "<type>] <key-alias> <store-passwd> " +
                               "<key-passwd> <template-uri>");
            System.err.println("Options:");
            System.err.println("\t-keystoretype <type>\tThe type of " +
                               "keystore like 'JKS' 'JCEKS'. The default " +
                               "is 'JKS'");
            System.exit(1);
        }
        //System.err.println("Key store: "+keystorepath);

        //initTimes();
        sign(keystorepath, keystoretype, alias, storepass, keypass, templateURI);
        //printTimes();

        if (false) {
            initTimes();
            for (int j = 0;  j < 100;  j++) {
                sign(keystorepath, keystoretype, alias, storepass, keypass,
                     templateURI);
            }
            printTimes();
        }
    }

    static long parseTime;
    static long xsignTime;
    static long outputTime;
    static long totalTime;
    static void initTimes() {
        parseTime = 0;  xsignTime = 0;  outputTime = 0;  totalTime = 0;
        XSignature.signTime = 0;
        XSignature.canonicalizeTime = 0;
        XSignature.resetDigestTime();
    }
    static void printTimes() {
        System.err.println("Total:             "+ totalTime + "ms");
        System.err.println("  XML Parsing:       "+ parseTime + "ms");
        System.err.println("  XSignature.sign(): "+ xsignTime + "ms");
        System.err.println("    Digest for Ref:   " +
                           XSignature.getDigestTime() + "ms");
        System.err.println("    Canonicalize:     " +
                           XSignature.canonicalizeTime + "ms");
        System.err.println("    Sign with JCA/JCE:" + XSignature.signTime + "ms");
        System.err.println("  Serializing DOM:   " + outputTime + "ms");
    }

    static void sign(String keystorepath, String keystoretype, String alias,
                     char[] storepass, char[] keypass, String templateURI)
        throws IOException, KeyStoreException, CertificateException,
               NoSuchAlgorithmException, InvalidKeyException, SignatureException,
               UnrecoverableKeyException, TransformException,
               SignatureStructureException, SAXException,
               NoSuchProviderException, ParserConfigurationException {

        long start = System.currentTimeMillis();
        //
        // Initialize: Reading a template signature.
        //
        DOMParser parser = new DOMParser();
        parser.parse(templateURI);
        Document doc = parser.getDocument();
        long parseEnd = System.currentTimeMillis();
        parseTime += parseEnd-start;

        //
        // Setup a certificate and a private key.
        //
        KeyStore keystore = KeyStore.getInstance(keystoretype);
        keystore.load(new FileInputStream(keystorepath), storepass);
        X509Certificate cert = (X509Certificate)keystore.getCertificate(alias);
        Key key = keystore.getKey(alias, keypass); // a private key
        if (key == null) {
            System.err.println("Could not get a key: "+alias);
            System.exit(1);
        }

        //
        // Sign
        //
        NodeList list =
            doc.getElementsByTagNameNS(XSignature.XMLDSIG_NAMESPACE, "Signature");
        if (list.getLength() == 0) {
            System.err.println("No Signature element.");
        }
        long endSign = System.currentTimeMillis();
        SignatureContext sigContext = new SignatureContext();
        sigContext.setIDResolver(new AdHocIDResolver(doc));
        //sigContext.setResourceShower(new StderrResourceShower());
        //sigContext.setAlgorithmFactory(new AlgorithmFactory("IBMJCE"));
        KeyInfo keyInfo = new KeyInfo();
        //KeyInfo.X509Data x5data = new KeyInfo.X509Data();
        //x5data.setCertificate(cert);
        //x5data.setParameters(cert, true, true, true);
        //keyInfo.setX509Data(new KeyInfo.X509Data[] { x5data });
        //keyInfo.setKeyValue(cert.getPublicKey());
        keyInfo.setKeyNames(new String[] { cert.getSubjectDN().getName() });
        for (int i = 0;  i < list.getLength();  i ++) {
            long startSign = System.currentTimeMillis();
            Element signatureElement = (Element)list.item(i);
            try {
                keyInfo.insertTo(signatureElement);
                sigContext.sign(signatureElement, key);
            } catch(Exception e) { e.printStackTrace(); }
            endSign = System.currentTimeMillis();
            xsignTime += endSign-startSign;
        }

        //
        // Output
        //
        Writer wr = new OutputStreamWriter(System.out, "UTF-8");
        OutputFormat format = new OutputFormat(doc, "UTF-8", false);
        format.setPreserveSpace(true);
        Serializer ser = new XMLSerializer(format);
        ser.setOutputCharStream(wr);
        DOMSerializer domser = ser.asDOMSerializer();
        domser.serialize(doc);
        long endTime = System.currentTimeMillis();
        outputTime += endTime-endSign;
        totalTime += endTime-start;
    }

    static class StderrResourceShower implements ResourceShower {
        public StderrResourceShower() {
        }
        public void showSignedResource(Element owner, int count, String uri,
                                       String type, byte[] content,
                                       String encoding) {
            System.err.print("******** "+uri+" ********");
            try {
                if (encoding != null) {
                    System.err.print(new String(content, encoding));
                } else {
                    System.err.write(content);
                }
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
            System.err.println("****************");
        }
    }
}
