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
import com.ibm.xml.dsig.KeyInfo;
import com.ibm.xml.dsig.XSignatureException;
import com.ibm.xml.dsig.SignatureStructureException;
import com.ibm.xml.xkms.AuthInfo;
import com.ibm.xml.xkms.AuthServerInfo;
import com.ibm.xml.xkms.AuthUserInfo;
import com.ibm.xml.xkms.KeyBinding;
import com.ibm.xml.xkms.XkmsParam;
import com.ibm.xml.xkms.XkmsResult;
import com.ibm.xml.xkms.XkmsService;
import com.ibm.xml.xkms.XkmsRegisterParam;
import com.ibm.xml.xkms.XkmsRegisterResult;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.security.Key;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.Security;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Iterator;
import java.util.List;
import org.w3c.dom.Element;

/**
 * Sample XKMS client for X-KRSS.
 *
 * @version $Id: RegisterXkms.java,v 1.1 2001/11/26 10:24:24 mak0702 Exp $
 * @author TAMURA Kent &lt;kent@trl.ibm.co.jp&gt;
 * @author Satoshi Makino &lt;mak0702@trl.ibm.co.jp&gt;
 */
public class RegisterXkms {

    public static void main(String[] argv)
        throws XSignatureException, IOException, KeyStoreException,
               SignatureStructureException, NoSuchAlgorithmException,
               CertificateException, UnrecoverableKeyException {

        Security.addProvider(new IBMJCE());

        String serviceURIs = null;
        String serviceURIa = null;
        String action = null;
        boolean sendPop = false;
        String keystorePath = null;
        String alias = null;
        char[] storePass = null;
        char[] keyPass = null;
        String dname = null;
        String authPass = null;
        String revokePass = null;
        String recoverPass = null;

        if (argv.length < 5) {
            System.err.println("");
            System.err.println("Usage: RegisterXkms {-soap,-axis} servletURI " +
                               "yourDName [action]");
            System.err.println("Action is as follows:");
            System.err.println("    registerkey authPass revokePass " +
                               "{-withkey,-withoutkey} keystoreFile alias " +
                               "storePass keyPass");
            System.err.println("    revoke {-usepop keystoreFile alias " +
                               "storePass keyPass | -usepass revokePass}");
            System.err.println("    recover recoverPass keystoreFile alias " +
                               "storePass keyPass");
            System.err.println();
            System.exit(1);
        }
        if(argv[0].equals("-soap")) serviceURIs = argv[1];
        if(argv[0].equals("-axis")) serviceURIa = argv[1];
        dname = argv[2];
        action = argv[3];
        if(argv.length == 11 && action.equals("registerkey")) {
            authPass = argv[4];
            revokePass = argv[5];
            if(argv[6].equals("-withkey")) sendPop = true;
            keystorePath = argv[7];
            alias = argv[8];
            storePass = argv[9].toCharArray();
            keyPass = argv[10].toCharArray();
        } else if(action.equals("revoke")) {
            if(argv.length == 9 && argv[4].equals("-usepop")) {
                sendPop = true;
                keystorePath = argv[5];
                alias = argv[6];
                storePass = argv[7].toCharArray();
                keyPass = argv[8].toCharArray();
            } else if(argv.length == 6 && argv[4].equals("-usepass")) {
                revokePass = argv[5];
            }
        } else if(argv.length == 9 && action.equals("recover")) {
            recoverPass = argv[4];
            keystorePath = argv[5];
            alias = argv[6];
            storePass = argv[7].toCharArray();
            keyPass = argv[8].toCharArray();
        } else {
            System.err.println("Unknown action: " + action);
            System.exit(1);
        }

        String protocol = serviceURIa == null ? "SOAP" : "SOAP/AXIS";
        String actionURI = "http://www.xkms.org/schema/xkms-2001-01-20";
        XkmsService xkms = XkmsService.getInstance(protocol);
        XkmsRegisterParam rparam = xkms.createXkmsRegisterParam();
        rparam.addRespond(XkmsParam.RESPOND_KEYNAME);
        rparam.addRespond(XkmsParam.RESPOND_KEYVALUE);
        rparam.addRespond(XkmsParam.RESPOND_X509CERT);
        rparam.setProperty(XkmsParam.PROP_SOAP_SERVICE,
                           serviceURIa == null ? serviceURIs : serviceURIa);
        rparam.setProperty(XkmsParam.PROP_SOAP_ACTION, actionURI);
        if(authPass != null) rparam.setAuthPassPhrase(authPass);
        if(revokePass != null) rparam.setRevocationPassPhrase(revokePass);
        if(recoverPass != null) rparam.setRecoveryPassPhrase(recoverPass);
        KeyBinding prototype = new KeyBinding();
        prototype.setKeyUsage(KeyBinding.USAGE_SIGNATURE);
        KeyInfo kinfo = new KeyInfo();
        kinfo.setKeyNames(new String[] { dname });

        if(action.equals("registerkey"))
            prototype.setStatus(KeyBinding.ASSERTION_VALID);
        else if(action.equals("revoke"))
            prototype.setStatus(KeyBinding.ASSERTION_INVALID);
        else if(action.equals("recover"))
            prototype.setStatus(KeyBinding.ASSERTION_INDETERMINATE);
        rparam.setPrototype(prototype);
        AuthInfo ainfo = null;
        if(action.equals("registerkey") && alias == null)
            ainfo = new AuthServerInfo();
        else ainfo = new AuthUserInfo();
        rparam.setAuthInfo(ainfo);
        if(sendPop == true) {
            //
            // Setup a certificate and a private key.
            //
            KeyStore keystore = KeyStore.getInstance("JKS");
            keystore.load(new FileInputStream(keystorePath), storePass);
            X509Certificate cert =
                (X509Certificate)keystore.getCertificate(alias);
            Key key = keystore.getKey(alias, keyPass); // a private key
            if (key == null) {
                System.err.println("Could not get a key: "+alias);
                System.exit(1);
            }
            rparam.setPrivateKey((PrivateKey)key);
            rparam.setCertificate(cert);
            kinfo.setKeyValue(cert.getPublicKey());
        }
        prototype.setKeyInfo(kinfo);

        XkmsRegisterResult rresult = xkms.register(rparam);
        if(rresult.getException() != null) {
            System.out.println("Register: Failed due to an exception in " +
                               "XKMS message processing");
            System.out.println("Register: Exception is:");
            System.out.println(rresult.getException().getMessage());
        } else if(rresult.getResult() == XkmsResult.RESULT_SUCCESS
                  || rresult.getResult() == XkmsResult.RESULT_INCOMPLETE) {
            System.err.println("Register: Succeeded");
            List answers = rresult.getAnswers();
            if(answers != null) {
                Iterator ansIter = answers.iterator();
                while(ansIter.hasNext()) {
                    KeyBinding keyBind = (KeyBinding)ansIter.next();
                    System.out.println("Register: Key status is " +
                                       keyBind.getStatusName());
                    Element keyInfoElem = keyBind.getKeyInfo();
                    if(keyInfoElem != null) {
                        KeyInfo keyInfo = new KeyInfo(keyInfoElem);
                        KeyInfo.X509Data[] x5DataArray = keyInfo.getX509Data();
                        for(int i = 0; x5DataArray != null &&
                            i < x5DataArray.length; i ++) {
                            KeyInfo.X509Data x5Data = x5DataArray[i];
                            X509Certificate[] certs = x5Data.getCertificates();
                            if(!action.equals("revoke")) {
                                KeyStore keystore = KeyStore.getInstance("JKS");
                                try {
                                    FileInputStream fis = new
                                        FileInputStream(keystorePath);
                                    keystore.load(fis, storePass);
                                    fis.close();
                                } catch(FileNotFoundException fnfe) {
                                    keystore.load(null, storePass);
                                }
                                Key key = null;
                                if(sendPop == true) key =
                                    keystore.getKey(alias, keyPass);
                                else key = rresult.getPrivateKey();
                                if (key != null) {
                                    keystore.setKeyEntry
                                        (dname, key, keyPass, certs);
                                    FileOutputStream fos =
                                        new FileOutputStream(keystorePath);
                                    keystore.store(fos, storePass);
                                    fos.close();
                                    System.out.println
                                        ("Register: Your keys and " +
                                         "certificate are stored in: " +
                                         keystorePath);
                                    System.out.println
                                        ("Register: Keystore password is: " +
                                         new String(storePass));
                                    System.out.println
                                        ("Register: Alias is: \"" + dname + "\"");
                                    System.out.println
                                        ("Register: Key password is: " +
                                         new String(keyPass));
                                }
                            }
                        }
                    }
                }
            }
        } else if (rresult.getResult() == XkmsResult.RESULT_NOMATCH) {
            System.out.println("Register: No corresponding entry was found");
        } else {
            System.err.println("Register: Failed");
        }
    }
}