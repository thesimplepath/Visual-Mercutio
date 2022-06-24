/*
 * (C) Copyright IBM Corp. 2000  All rights reserved.
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


/**
 * This class is a simple example of a Web Service Provider.  This service 
 * will receive a message and echo it back to the Service Requestor.
 */
public class WebServiceExample {
  /**
   * Create the example service.
   */
  public WebServiceExample() { }

  /**
   * Receive a message and echo it to the Service Requestor.
   *
   * @param inMessage The message string that will be received from the 
   *                  Service Requestor
   * @return Returns a string which will contain the input message string.
   */
  public String echoMessage(String inMessage) {
    // Create new message 
    String outMessage="Message Received By WebServiceExample: ["+inMessage+"]";

    // Return the string to Service Requestor
    return outMessage;
  }

}
