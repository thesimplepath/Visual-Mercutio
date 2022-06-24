package samples.messaging;

import java.io.*;
import org.apache.soap.*;
import org.apache.soap.rpc.SOAPContext;
import javax.mail.MessagingException;

/**
 * This class receives the PO via a "purchaseOrder" method and does
 * something with it.
 *
 * @author Sanjiva Weerawarana <sanjiva@watson.ibm.com>
 */
public class POProcessor {
  public void purchaseOrder (Envelope env, SOAPContext reqCtx, 
                                           SOAPContext resCtx)
    throws MessagingException, IOException {
    resCtx.setRootPart("OK thanks, got the PO; we'll contact you when ready.",
        "text/xml");
  }

  public void bustedRequest (Envelope env, SOAPContext reqCtx, 
                                           SOAPContext resCtx)
    throws Exception {
    throw new IllegalArgumentException ("Huh?");
  }
}
