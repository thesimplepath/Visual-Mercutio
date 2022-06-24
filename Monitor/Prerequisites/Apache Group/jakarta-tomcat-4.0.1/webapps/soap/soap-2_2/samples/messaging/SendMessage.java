package samples.messaging;

import java.io.*;
import java.net.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.*;
import org.apache.soap.*;
import org.apache.soap.messaging.*;
import org.apache.soap.transport.*;
import org.apache.soap.util.xml.*;

/**
 * This class sends a message by taking in an XML file that has a full
 * SOAP envelope in it and dumping it to the given message router URL.
 * Any content from the response is dumped to stdout.
 *
 * @author Sanjiva Weerawarana <sanjiva@watson.ibm.com>
 */
public class SendMessage {
  public static void main (String[] args) throws Exception {
    if (args.length != 2) {
      System.err.println ("Usage: java " + SendMessage.class.getName () +
                          " SOAP-router-URL envelope-file");
      System.exit (1);
    }

    // get the envelope to send
    FileReader fr = new FileReader (args[1]);
    DocumentBuilder xdb = XMLParserUtils.getXMLDocBuilder();
    Document doc = xdb.parse (new InputSource (fr));
    if (doc == null) {
      throw new SOAPException (Constants.FAULT_CODE_CLIENT, "parsing error");
    }
    Envelope msgEnv = Envelope.unmarshall (doc.getDocumentElement ());

    // send the message
    Message msg = new Message ();
    msg.send (new URL (args[0]), "urn:this-is-the-action-uri", msgEnv);

    // receive whatever from the transport and dump it to the screen
    System.out.println ("RESPONSE:");
    System.out.println ("--------");
    SOAPTransport st = msg.getSOAPTransport ();
    BufferedReader br = st.receive ();
    String line;
    while ((line = br.readLine ()) != null) {
      System.out.println (line);
    }
  }
}
