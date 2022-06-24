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

import org.w3c.dom.*;

import javax.activation.*;
import java.io.*;
import java.util.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import javax.activation.DataHandler;

import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.attachments.Attachments;
import org.apache.axis.attachments.AttachmentUtils;
import org.apache.axis.attachments.ManagedMemoryDataSource;
import org.apache.axis.AxisFault;
import org.apache.axis.Part;

/**
 * This class contains an example of a SOAP service that can process attachments.
 */
public class AttachmentService
{
  /**
   * Create the attachment service.
   */
  public AttachmentService()
  {
  }


  /**
   * List all attachments and return the information as string.
   * This is the RPC interface for this service.
   *
   * The format for the output message is:
   * <parameters>
   *   <listTitle>[title text]</listtitle>
   *   <fileList>
   *     <file>[filename]</file>
   *   </fileList>
   * </parameters>
   * <attachments>
   *   <content ...>
   *     [Content of attachment]
   *   </content>
   * </attachments>
   */
  public String listAttachmentsRPC( String listTitle, String[] fileList,
    DataHandler classFile, DataHandler imageFile, DataHandler htmlFile)
    throws  IOException, ClassNotFoundException,
     java.awt.datatransfer.UnsupportedFlavorException
  {
    // System.out.println("Entering RPC interface for listAttachments service...");
    // List attachments
    DataHandler[] dhs= {classFile, imageFile, htmlFile};
    String ret=listAttachments( listTitle,  fileList, dhs , false );
    for(int i=0; i < dhs.length; ++i)
    {
        DataSource ds= dhs[i].getDataSource();
        if(ds instanceof ManagedMemoryDataSource ){
          ((ManagedMemoryDataSource )ds).delete(); //Delete the resources associated with this attachment.
        }
    }
    return ret;
  }

  public Document listAttachmentsMessage(org.apache.axis.MessageContext msgContext, Document xml)
    throws org.apache.axis.AxisFault,java.io.IOException, org.xml.sax.SAXException,
    java.awt.datatransfer.UnsupportedFlavorException,javax.xml.parsers.ParserConfigurationException,
    java.lang.ClassNotFoundException
  {
    String listTitle = "Attachment List";
    Vector files = new Vector();

    NodeList titleChildren = xml.getElementsByTagName("listTitle");
    for (int i = 0; i < titleChildren.getLength(); i++)
    {
      Element child = (Element)titleChildren.item(i);
      listTitle = getChildCharacterData(child);
    }

    // Pull out the names of the files that were specified as part of the message
    NodeList fileChildren = xml.getElementsByTagName("file");
    for (int i = 0; i < fileChildren.getLength(); i++)
    {
      Element child = (Element)fileChildren.item(i);
      files.add(getChildCharacterData(child));
    }

    // Get file list as an array
    String[] fileList = (String[]) files.toArray(new String[files.size()]);

    //Get the attachments directly from the request message since in this message they are not
    //  referenced by the xml..
    Message reqMsg= msgContext.getRequestMessage();

    Attachments attachments=reqMsg.getAttachments();  

    if(null == attachments){
       throw new org.apache.axis.AxisFault("No support for attachments" );
    }

    java.util.Collection parts= attachments.getAttachments();
    Part[] partsArray= (Part[]) parts.toArray( new Part[parts.size()]);

    String rpcResponse= listAttachments(listTitle, fileList, partsArray, true);

    Message respMsg= msgContext.getResponseMessage();

    // Split the RPC results into the 2 message strings we need
    int parmIndex = rpcResponse.indexOf("<parameters>");
    int attachIndex = rpcResponse.indexOf("<attachments>");
    String parmPart = rpcResponse.substring(parmIndex,attachIndex-1);
    String attachPart = rpcResponse.substring(attachIndex);

    // System.out.println("...building the messages to return.");
    // Convert the 2 strings into the messages we will return to the client
    DocumentBuilderFactory  dbf = DocumentBuilderFactory.newInstance();
    dbf.setNamespaceAware(true);
    dbf.setValidating(false);
    DocumentBuilder db = dbf.newDocumentBuilder();

    Document  tmp1 = db.parse(new InputSource(new StringReader(parmPart)));

    Document  tmp2 = db.parse(new InputSource(new StringReader(attachPart)));
    
    //Smash the two seperate docs into a single reply.
    Document respDoc= db.newDocument();
    Element respRoot= respDoc.createElementNS("http://www.attachment.com/AttachmentService", "listAttachmentsMessageResponse"); 
    respDoc.appendChild(respRoot);

    Node imp= respDoc.importNode(tmp1.getDocumentElement(),true);
    respRoot.appendChild(imp);
    imp= respDoc.importNode(tmp2.getDocumentElement(),true);
    respRoot.appendChild(imp);


    //Now copy the attachments that were received and send them back.
    attachments=respMsg.getAttachments();  

    for(int i=0; i< partsArray.length ;  ++i)
    {
      Part newPart= attachments.createAttachmentPart(
          AttachmentUtils.getActiviationDataHandler(partsArray[i]));
          
      newPart.setContentLocation(partsArray[i].getContentLocation()); //Make sure content location is the same.
                                                          //All other headers are already handled.
    }

    // System.out.println("Leaving MSG interface for listAttachments service...");
    return( respDoc);
  }

  protected String listAttachments( String listTitle, String[] fileList,
     Object[] parts, //In the RPC demo, attachchments have already been deserialized to JAF DataHandlers.
                    //In the Messaging demo the attachments have been directly obtained.
                    //Hence, the differnce in the treatment of attachment between the two.
      boolean msg  //Only needed for a bug in AXIS.            
    )
    throws  IOException, 
     java.awt.datatransfer.UnsupportedFlavorException, 
     java.lang.ClassNotFoundException
  {

    // List attachments
    StringBuffer response = new StringBuffer("<parameters>\n  <listTitle>" + listTitle + "</listTitle>\n");

    // Add file list
    response.append( "  <fileList>\n");
    for (int i = 0; i < fileList.length; i++)
    {
      response.append("    <file>" + fileList[i] + "</file>\n");
    }
    response.append( "  </fileList>\n</parameters>\n\n");

    response.append( "<attachments>\n");

    for(int i=0; i< parts.length; ++i)
    {
        DataHandler datahandler= null;
        Part part= null;
        if( parts[i] instanceof Part){
          part= (Part) parts[i];
          datahandler= AttachmentUtils.getActiviationDataHandler(part); 
        }
        else datahandler= (DataHandler) parts[i]; 

        if (datahandler.getContentType().startsWith("text/"))
        {
          response.append( "  <content part=\"" + fileList[i] + "\"\n");
          response.append( "           type=\"" + datahandler.getContentType() + "\"");
          if(null != part)
          {
             response.append( "           id=\"" + part.getContentId() + "\"");
             response.append( "           location=\"" + part.getContentLocation()+ "\"");
          }
          response.append( ">\n");

          if(!msg)
          {  //Message does not handle CDATA sections correctly.
            response.append( "    <![CDATA[");
            response.append( datahandler.getTransferData(
                 new java.awt.datatransfer.DataFlavor(datahandler.getContentType() +
                   "; class=java.lang.String")));

            response.append( "]]>\n");
          }
          response.append( ">\n");
          response.append( "  </content>\n");
        }
        else
        {
          response.append( "  <content part=\"" + fileList[i] + "\"  ");
          response.append( " type=\"" + datahandler.getContentType() + "\"");
          if(null != part)
          {
             response.append( "           id=\"" + part.getContentId() + "\"");
             response.append( "           location=\"" + part.getContentLocation()+ "\"");
          }
          response.append( "/>\n");
          response.append( " <!--Attachment received that is not \"text/*\", content is not being returned!-->\n");
        }
    }

    // End tag
    response.append( "</attachments>");

    return response.toString();
  }


    /*  Copied from SOAP 2x DOMUtils.java*/
  
    static public String getChildCharacterData (Element parentEl) {
        if (parentEl == null) {
            return null;
        }
        Node          tempNode = parentEl.getFirstChild();
        StringBuffer  strBuf   = new StringBuffer();
        CharacterData charData;
        
        while (tempNode != null) {
            switch (tempNode.getNodeType()) {
                case Node.TEXT_NODE :
                case Node.CDATA_SECTION_NODE : charData = (CharacterData)tempNode;
                    strBuf.append(charData.getData());
                    break;
            }
            tempNode = tempNode.getNextSibling();
        }
        return strBuf.toString();
    }

}

