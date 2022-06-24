import java.io.*;
import java.util.*;
import java.net.*;
import org.w3c.dom.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import pmodel;

public class A
{
  public static void main(String[] args) throws Exception 
  {
//URL url = new URL("http://rsc202/cgi-bin/qq");
URL url = new URL("http://localhost:8080/soap/servlet/rpcrouter");

    // Build the call.
    Call call = new Call();
    call.setTargetObjectURI("urn:emessenger");
    call.setMethodName("sndModel");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);

    SOAPMappingRegistry smr = new SOAPMappingRegistry();
    BeanSerializer bs=new BeanSerializer();    
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,new QName("urn:xml-soap-emessenger-pmodel", "pmodel"),pmodel.class, bs,bs);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,new QName("urn:xml-soap-emessenger-pproc", "pproc"),pproc.class, bs,bs);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,new QName("urn:xml-soap-emessenger-pdeliv", "pdeliv"),pdeliv.class, bs,bs);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,new QName("urn:xml-soap-emessenger-ppdattr", "ppdattr"),ppdattr.class, bs,bs);

    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    pmodel model=new pmodel();
    model.setModelref("coco");
    model.setModelname("Modele assurance");

    params.addElement(new Parameter("model", pmodel.class, model, null));

    pproc[] proc=new pproc[3];
    proc[0]=new pproc();
    proc[0].setProcid(1);
    proc[0].setWkgid(1);
    proc[0].setProcattribid(1);
    proc[0].setProctype(0);
    proc[0].setDoublesign(0);
    proc[1]=new pproc();
    proc[1].setProcid(2);
    proc[1].setWkgid(1);
    proc[1].setProcattribid(2);
    proc[1].setProctype(1);
    proc[1].setDoublesign(1);
    proc[2]=new pproc();
    proc[2].setProcid(3);
    proc[2].setWkgid(1);
    proc[2].setProcattribid(3);
    proc[2].setProctype(2);
    proc[2].setDoublesign(0);

    Integer nbr3=Integer.valueOf ("3");
    params.addElement(new Parameter("procnbr", Integer.class, nbr3, null));
    params.addElement(new Parameter("proc", pproc[].class, proc, null));

    pdeliv[] deliv=new pdeliv[2]; 
    deliv[0]=new pdeliv(); 
    deliv[0].setDelivid(1);
    deliv[0].setProcidsrc(1);
    deliv[0].setProcidtrg(2);
    deliv[0].setDelivattribid(4);
    deliv[0].setDelivname("L1");
    deliv[0].setLateral(0);
    deliv[1]=new pdeliv(); 
    deliv[1].setDelivid(2);
    deliv[1].setProcidsrc(2);
    deliv[1].setProcidtrg(3);
    deliv[1].setDelivattribid(5);
    deliv[1].setDelivname("L2");
    deliv[1].setLateral(0);

    Integer nbr2=Integer.valueOf ("2");
    params.addElement(new Parameter("delivnbr", Integer.class, nbr2, null));
    params.addElement(new Parameter("deliv", pdeliv[].class, deliv, null));
 
    ppdattr[] pdattr=new ppdattr[3];
    pdattr[0]=new ppdattr();
    pdattr[0].setPdattribid(4);
    pdattr[0].setProw(0);
    pdattr[0].setAttribdefid(0);
    pdattr[0].setMvalue("L1");
    pdattr[1]=new ppdattr();
    pdattr[1].setPdattribid(5);
    pdattr[1].setProw(0);
    pdattr[1].setAttribdefid(0);
    pdattr[1].setMvalue("L2");

    params.addElement(new Parameter("pdattrnbr", Integer.class, nbr2, null));
    params.addElement(new Parameter("pdattr", ppdattr[].class, pdattr, null));

    call.setParams(params);
 

    // Invoke the call.
    Response resp;

    try
    {
      resp = call.invoke(url, "");
    }
    catch (SOAPException e)
    {
      System.err.println("Caught SOAPException (" +
                         e.getFaultCode() + "): " +
                         e.getMessage());
      return;
    }

    // Check the response.
    if (!resp.generatedFault())
    {
      Parameter ret = resp.getReturnValue();
      Object value = ret.getValue();
      System.out.println(value != null ? "\n" + value : "I don't know.");
    }
    else
    {
      Fault fault = resp.getFault();

      System.err.println("Generated fault: ");
      System.out.println ("  Fault Code   = " + fault.getFaultCode());  
      System.out.println ("  Fault String = " + fault.getFaultString());
    }
  }
}