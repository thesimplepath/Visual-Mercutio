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

import java.io.*;
import java.util.*;

import com.ibm.services.*;
import com.ibm.services.data.*;
import com.ibm.services.data.util.XMLUtil;
import com.ibm.services.BaseService;
import com.ibm.services.util.InvokeService;

import com.ibm.wstk.*;
import com.ibm.wstk.util.*;

import org.w3c.dom.*;

/**
 * The <code>AddressBookService</code> class, implements address book 
 * functions.
 *
 * @author Alfredo da Silva
 */
public class AddressBookService
{
  /**
   * DataService WSDL file.
   */
  protected static final String WSDL_FILENAME = 
    DSConstants.DS_URL + DSConstants.DATA_PREFIX 
    + "/" + DSConstants.DS_XPATH_WSDL_DOC;

  /**
   * datastoreFilename
   *
   */
  protected String datastoreFilename;


  /**
   * Property name for the datastore filename 
   *
   */
  public static final String PROP_ADDRESSBOOK_SERVICE_DATASTORE_FILENAME = 
    ServiceConstants.ADDRESSBOOK + ".datastore.filename";


  /**
   * ServiceProperties object.
   *
   */
  protected ServiceProperties serviceProps;


  public AddressBookService() throws IOException
  {
    // DEBUG:
    // System.out.println("----------\nAddressBookService.<init>: before create serviceProps");
    
    // Create serviceProperties object
    serviceProps = new ServiceProperties();

    // DEBUG:
    // System.out.println("----------\nAddressBookService.<init>: after create serviceProps");

    // Get datastore filename
    datastoreFilename = WSTKConstants.WSTK_HOME + "/" +
      serviceProps.getProperty(PROP_ADDRESSBOOK_SERVICE_DATASTORE_FILENAME);
    
    // DEBUG:
    // System.out.println("----------\nAddressBookService.<init> datastoreFilename: " + datastoreFilename);

    // ADS    WSDL_FILENAME = 
    //      serviceProps.getProperty(ServiceConstants.IDENTITY + "." + 
    //                                      ServiceConstants.PROP_WSDL_URL);
  }


  /**
   * Adds a new address entry.
   *
   * @param name a <code>String</code> value
   * @param address an <code>Address</code> value
   * @return a <code>String</code> value
   * @exception DSException if an error occurs
   */
  public String addEntry(String name, Address address) throws DSException
  {
    String insertMsg = "<ds:insert xmlns:xp=\"http://tempuri.org/xsd/2001/10/Data/XPath\" xmlns:ds=\"http://tempuri.org/xsd/2001/10/Data\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://tempuri.org/xsd/2001/10/Data/XPath DataXPath.xsd\"> <xp:documentTarget ";

    StringReader reader;


    try 
    {
      String xmlName = "<Name>" + name + "</Name>";
      String streetNum = "<StreetNum>" + String.valueOf(address.getStreetNum()) + "</StreetNum>";
      String streetName = "<StreetName>" + address.getStreetName() + 
        "</StreetName>";
      String city = "<City>" + address.getCity() + "</City>";
      String state = "<State>" + address.getState() + "</State>";
      String zip = "<Zip>" + String.valueOf(address.getZip()) + "</Zip>";
      String areaCode = "<AreaCode>" + String.valueOf(address.getPhoneNumber().getAreaCode()) + "</AreaCode>";
      String exchange = "<Exchange>" + address.getPhoneNumber().getExchange() + "</Exchange>";
      String number = "<Number>" + address.getPhoneNumber().getNumber() + 
        "</Number>";
      
      // Create new DS operation instance
      DSOperation dsOperation = 
        DSOperation.newInstance(DSConstants.INSERT_OPER);

      // Set input file location
      insertMsg += "location=\"" + datastoreFilename + "\" /> <xp:into>/m:AddressBook</xp:into><xp:with>";

      // Create insert message
      insertMsg += "<Listing>" + xmlName + "<Address>" + streetNum + 
        streetName + city + state + zip + "<PhoneNumber>" + areaCode + 
        exchange + number + "</PhoneNumber>" + "</Address>" + "</Listing>" + 
        "</xp:with></ds:insert>";

      // DEBUG
      // System.out.println("*** insertMsg: " + insertMsg);

      reader = new StringReader(insertMsg);

      // Populate operation data
      dsOperation.read(reader);

      // Invoke operation
      Response response = dsOperation.invoke(WSDL_FILENAME, null);

      // Debugging
      // System.out.println(response.toXMLString());

      return response.getStatus().getType();
    }
    catch (Exception e) 
    {
      throw new DSException("Problems adding new entry", e);
    }
  }


  /**
   * Describe <code>listAll</code> method here.
   *
   * @return a <code>Listing[]</code> value
   * @exception DSException if an error occurs
   */
  public Listing[] listAll() throws DSException
  {
    String queryAllMsg = "<ds:query xmlns:xp=\"http://tempuri.org/xsd/2001/10/Data/XPath\" xmlns:ds=\"http://tempuri.org/xsd/2001/10/Data\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://tempuri.org/xsd/2001/10/Data/XPath DataXPath.xsd\"> <xp:documentTarget ";

    StringReader reader;
    Vector listingVector = new Vector();
    Listing[] listingArray = null;


    try 
    {
      // Create new DS operation instance
      DSOperation dsOperation = 
        DSOperation.newInstance(DSConstants.QUERY_OPER);

      // Set input file location
      queryAllMsg += "location=\"" + datastoreFilename + "\" />  <xp:what>/</xp:what></ds:query>";

      // DEBUG
      // System.out.println("*** queryAllMsg: " + queryAllMsg);

      reader = new StringReader(queryAllMsg);

      // Populate operation data
      dsOperation.read(reader);

      // Invoke operation
      Response response = dsOperation.invoke(WSDL_FILENAME, null);

      // Debugging
      // System.out.println(response.toXMLString());

      if (response.getStatus().getType().equals(StatusCodeType.SUCCESS))
      {
        Vector extensionElementVector = 
          ((SuccessResponseType)response).getResult().getExtensionElement();

        for (int i = 0; i < extensionElementVector.size(); i++) 
        {
          String extensionElement = 
            (String)extensionElementVector.elementAt(i);

          if (extensionElement != null) 
          {
            reader = new StringReader(extensionElement);
            
            Element elem = XMLUtil.parseXML(reader).getDocumentElement();
            
            // Debugging
            // System.out.println("*** elemList:\n " + XMLUtil.XML2String(elem));

            if (isListEmpty(elem) == true) 
            {
              // ADS listingArray = new Listing[1];
              // ADS listingArray[0] = null;

              return listingArray;
            }

            // Get listing element
            NodeList listingElementList = elem.getElementsByTagName("Listing");

            for (int j = 0; j < listingElementList.getLength(); j++) 
            {
              // Debugging
              // System.out.println("*** elem:\n " + XMLUtil.XML2String((Element)listingElementList.item(j)));

              // Add element to the listingVector
              listingVector.add(createListing((Element)listingElementList.item(j)));
            }
          }
        }

        // Create array of Listings
        if (listingVector.size() != 0)
        {
          listingArray = new Listing[listingVector.size()];

          listingVector.copyInto(listingArray);
        }
      }

      return listingArray;
    }
    catch (Exception e) 
    {
      throw new DSException("Problems listing all entries", e);
    }
  }


  /**
   * Describe <code>listEntry</code> method here.
   *
   * @param name a <code>String</code> value
   * @return a <code>Address</code> value
   * @exception DSException if an error occurs
   */
  public Address listEntry(String name) throws DSException
  {
    String listEntryMsg = "<ds:query xmlns:xp=\"http://tempuri.org/xsd/2001/10/Data/XPath\" xmlns:ds=\"http://tempuri.org/xsd/2001/10/Data\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://tempuri.org/xsd/2001/10/Data/XPath DataXPath.xsd\"> <xp:documentTarget ";


    StringReader reader;
    Address address = null;


    try 
    {
      // Create new DS operation instance
      DSOperation dsOperation = 
        DSOperation.newInstance(DSConstants.QUERY_OPER);

      // Set input file location
      listEntryMsg += "location=\"" + datastoreFilename + "\" /> <xp:what>//Listing[Name[text()=";

      // Create insert message
      listEntryMsg += "'" + name + "']]" + "</xp:what></ds:query>";

      // DEBUG
      // System.out.println("*** listEntryMsg: " + listEntryMsg);

      reader = new StringReader(listEntryMsg);

      // Populate operation data
      dsOperation.read(reader);

      // Invoke operation
      Response response = dsOperation.invoke(WSDL_FILENAME, null);

      // Debugging
      // System.out.println(response.toXMLString());

      if (response.getStatus().getType().equals(StatusCodeType.SUCCESS))
      {
        String extensionElement = 
          (String)((SuccessResponseType)response).getResult().getExtensionElement().elementAt(0);

        if (extensionElement != null) 
        {
          reader = new StringReader(extensionElement);

          Element elem = XMLUtil.parseXML(reader).getDocumentElement();

          // Get address element
          Element addressElement = 
            (Element)elem.getElementsByTagName("Address").item(0);

          address = createAddress(addressElement);
        }
      }

      return address;
    }
    catch (Exception e) 
    {
      throw new DSException("Problems listing entry", e);
    }
  }


  /**
   * Describe <code>removeAll</code> method here.
   *
   * @return a <code>String</code> value
   * @exception DSException if an error occurs
   */
  public String removeAll() throws DSException
  {
    String removeAllMsg = "<ds:remove xmlns:xp=\"http://tempuri.org/xsd/2001/10/Data/XPath\" xmlns:ds=\"http://tempuri.org/xsd/2001/10/Data\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://tempuri.org/xsd/2001/10/Data/XPath DataXPath.xsd\"> <xp:documentTarget ";

    StringReader reader;


    try 
    {
      // Create new DS operation instance
      DSOperation dsOperation = 
        DSOperation.newInstance(DSConstants.REMOVE_OPER);

      // Set input file location
      removeAllMsg += "location=\"" + datastoreFilename + "\" /> <xp:what maxOccurs=\"unbounded\">/m:AddressBook//*</xp:what></ds:remove>";

      // DEBUG
      // System.out.println("*** removeAllMsg: " + removeAllMsg);

      reader = new StringReader(removeAllMsg);

      // Populate operation data
      dsOperation.read(reader);

      // Invoke operation
      Response response = dsOperation.invoke(WSDL_FILENAME, null);

      // Debugging
      // System.out.println(response.toXMLString());

      return response.getStatus().getType();
    }
    catch (Exception e) 
    {
      throw new DSException("Problems removing all entries", e);
    }
  }


  /**
   * Describe <code>removeEntry</code> method here.
   *
   * @param name a <code>String</code> value
   * @return a <code>String</code> value
   * @exception DSException if an error occurs
   */
  public String removeEntry(String name) throws DSException
  {
    String removeEntryMsg = "<ds:remove xmlns:xp=\"http://tempuri.org/xsd/2001/10/Data/XPath\" xmlns:ds=\"http://tempuri.org/xsd/2001/10/Data\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://tempuri.org/xsd/2001/10/Data/XPath DataXPath.xsd\">	<xp:documentTarget ";


    StringReader reader;


    try 
    {
      // Create new DS operation instance
      DSOperation dsOperation = 
        DSOperation.newInstance(DSConstants.REMOVE_OPER);

      // Set input file location
      removeEntryMsg += "location=\"" + datastoreFilename + "\" /> <xp:what>//Listing[Name[text()=";

      // Create insert message
      removeEntryMsg += "'" + name + "']]" + "</xp:what></ds:remove>";

      // DEBUG
      // System.out.println("*** removeEntryMsg: " + removeEntryMsg);

      reader = new StringReader(removeEntryMsg);

      // Populate operation data
      dsOperation.read(reader);

      // Invoke operation
      Response response = dsOperation.invoke(WSDL_FILENAME, null);

      // Debugging
      // System.out.println(response.toXMLString());

      return response.getStatus().getType();
    }
    catch (Exception e) 
    {
      throw new DSException("Problems removing entry", e);
    }
  }

  /**
   * Create Address object
   *
   * @param el an <code>Element</code> value
   * @return an <code>Address</code> value
   */
  private Address createAddress(Element addressElement)
  {
    Address address = null;
    int    streetNum = 0;
    String streetName = "";
    String city = "";
    String state = "";
    int    zip = 0;
    int    areaCode = 0;
    String exchange = "";
    String number = "";



    // Get streetNum element
    Element streetNumElement = 
      (Element)addressElement.getElementsByTagName("StreetNum").item(0);

    streetNum = Integer.parseInt(XMLUtil.getText(streetNumElement).trim());

    // Get streetName element
    Element streetNameElement = 
      (Element)addressElement.getElementsByTagName("StreetName").item(0);

    streetName = XMLUtil.getText(streetNameElement).trim();

    // Get city element
    Element cityElement = 
      (Element)addressElement.getElementsByTagName("City").item(0);

    city = XMLUtil.getText(cityElement).trim();

    // Get state element
    Element stateElement = 
      (Element)addressElement.getElementsByTagName("State").item(0);

    state = XMLUtil.getText(stateElement).trim();

    // Get zip element
    Element zipElement = 
      (Element)addressElement.getElementsByTagName("Zip").item(0);

    zip = Integer.parseInt(XMLUtil.getText(zipElement).trim());

    // Get phone element
    Element phoneElement = 
      (Element)addressElement.getElementsByTagName("PhoneNumber").item(0);

    // Get areaCode element
    Element areaCodeElement = 
      (Element)phoneElement.getElementsByTagName("AreaCode").item(0);

    areaCode = Integer.parseInt(XMLUtil.getText(areaCodeElement).trim());

    // Get exchange element
    Element exchangeElement = 
      (Element)phoneElement.getElementsByTagName("Exchange").item(0);

    exchange = XMLUtil.getText(exchangeElement).trim();

    // Get number element
    Element numberElement = 
      (Element)phoneElement.getElementsByTagName("Number").item(0);

    number = XMLUtil.getText(numberElement).trim();

    address = new Address(streetNum, streetName, city, state,
                          zip, new PhoneNumber(areaCode, exchange, number));

    return address;
  }

  /**
   * Create Listing object
   *
   * @param el an <code>Element</code> value
   * @return an <code>Listing</code> value
   */
  private Listing createListing(Element el)
  {
    Listing listing = null;
    String name = null;
    Address address = null;


    // Get name element
    Element nameElement = (Element)el.getElementsByTagName("Name").item(0);

    name = XMLUtil.getText(nameElement).trim();

    // Get address element
    Element addressElement = 
      (Element)el.getElementsByTagName("Address").item(0);

    address = createAddress(addressElement);

    if (name != null && address != null)
    {
      listing = new Listing(name, address);
    }

    return listing;
  }

  
  /**
   * Check whether a list is empty.
   *
   * @param elem an <code>Element</code> value
   * @return a <code>boolean</code> value
   */
  private boolean isListEmpty(Element elem)
  {
    boolean isEmpty = false;


    NodeList childrenList = elem.getChildNodes();
    
    // Address book is empty
    if (childrenList.getLength() == 1)
    {
      if (childrenList.item(0).getNodeType() == Node.TEXT_NODE)
        isEmpty = true;
    }
    else
      if (childrenList.getLength() == 0)
        isEmpty = true;

    return isEmpty;
  }
}
