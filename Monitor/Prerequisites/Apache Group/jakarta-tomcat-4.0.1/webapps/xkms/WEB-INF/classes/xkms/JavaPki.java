/*
 * (C) Copyright IBM Corp. 2001  All rights reserved.
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
import com.ibm.jsse.JSSEProvider;
import java.security.Security;
/**
 *
 * @version $Id: JavaPki.java,v 1.3 2001/11/26 10:24:24 mak0702 Exp $
 * @author TAMURA Kent &lt;kent@trl.ibm.co.jp&gt;
 */
public class JavaPki {
    public static void main(String[] argv) {
        Security.addProvider(new IBMJCE());
        Security.addProvider(new JSSEProvider());
        com.tivoli.pki.main.JavaPki.main(argv);
    }
}

