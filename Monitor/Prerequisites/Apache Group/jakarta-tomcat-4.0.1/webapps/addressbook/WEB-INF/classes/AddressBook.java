/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 2000, International
 * Business Machines, Inc., http://www.apache.org.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

import java.util.*;
import org.w3c.dom.*;
import org.apache.axis.utils.XMLUtils;
import org.xml.sax.* ;
import javax.xml.parsers.* ;

/**
 *
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 */
public class AddressBook
{
  private Hashtable name2AddressTable = new Hashtable();

  public static Element getFirstChildElement (Element elem) {
    for (Node n = elem.getFirstChild (); n != null; n = n.getNextSibling ()) {
      if (n.getNodeType () == Node.ELEMENT_NODE) {
        return (Element) n;
      }
    }
    return null;
  }

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

  public static Element getNextSiblingElement (Element elem) {
    for (Node n = elem.getNextSibling (); n != null; n = n.getNextSibling ()) {
      if (n.getNodeType () == Node.ELEMENT_NODE) {
        return (Element) n;
      }
    }
    return null;
  }

  /**
   * Creates a new <code>AddressBook</code> instance.
   *
   */
  public AddressBook()
  {
    addEntry("John B. Good",
             new Address(123, "Main Street", "Anytown", "NY", 12345,
                         new PhoneNumber(123, "456", "7890")));
    addEntry("Bob Q. Public",
             new Address(456, "North Whatever", "Notown", "ME", 12424,
                         new PhoneNumber(987, "444", "5566")));
  }

  /**
   * Describe <code>addEntry</code> method here.
   *
   * @param name a <code>String</code> value
   * @param address an <code>Address</code> value
   */
  public void addEntry(String name, Address address)
  {
    name2AddressTable.put(name, address);
  }

  /**
   * Describe <code>getAddressFromName</code> method here.
   *
   * @param name a <code>String</code> value
   * @return an <code>Address</code> value
   * @exception IllegalArgumentException if an error occurs
   */
  public Address getAddressFromName(String name)
    throws IllegalArgumentException
  {
    if (name == null)
    {
      throw new IllegalArgumentException("The name argument must not be " +
                                         "null.");
    }

    return (Address)name2AddressTable.get(name);
  }

  /**
   * Describe <code>getAllListings</code> method here.
   *
   * @return an <code>Element</code> value
   */
  public Element getAllListings()
  {
    Document doc = XMLUtils.newDocument();
    Element bookEl = doc.createElement("AddressBook");

    bookEl.appendChild(doc.createTextNode("\n"));

    for (Enumeration keys = name2AddressTable.keys();
         keys.hasMoreElements();)
    {
      String name = (String)keys.nextElement();
      Address address = (Address)name2AddressTable.get(name);
      Element listingEl = doc.createElement("Listing");
      Element nameEl = doc.createElement("Name");
      nameEl.appendChild(doc.createTextNode(name));
      listingEl.appendChild(doc.createTextNode("\n    "));
      listingEl.appendChild(nameEl);
      listingEl.appendChild(doc.createTextNode("\n    "));
      Element addressEl = doc.createElement("Address");
      Element streetNumEl = doc.createElement("StreetNum");
      streetNumEl.appendChild(doc.createTextNode(address.getStreetNum() + ""));
      addressEl.appendChild(doc.createTextNode("\n      "));
      addressEl.appendChild(streetNumEl);
      addressEl.appendChild(doc.createTextNode("\n      "));
      Element streetNameEl = doc.createElement("StreetName");
      streetNameEl.appendChild(doc.createTextNode(address.getStreetName()));
      addressEl.appendChild(streetNameEl);
      addressEl.appendChild(doc.createTextNode("\n      "));
      Element cityEl = doc.createElement("City");
      cityEl.appendChild(doc.createTextNode(address.getCity()));
      addressEl.appendChild(cityEl);
      addressEl.appendChild(doc.createTextNode("\n      "));
      Element stateEl = doc.createElement("State");
      stateEl.appendChild(doc.createTextNode(address.getState()));
      addressEl.appendChild(stateEl);
      addressEl.appendChild(doc.createTextNode("\n      "));
      Element zipEl = doc.createElement("Zip");
      zipEl.appendChild(doc.createTextNode(address.getZip() + ""));
      addressEl.appendChild(zipEl);
      addressEl.appendChild(doc.createTextNode("\n      "));
      PhoneNumber phone = address.getPhoneNumber();
      Element phoneEl = doc.createElement("PhoneNumber");
      phoneEl.appendChild(doc.createTextNode("\n        "));
      Element areaCodeEl = doc.createElement("AreaCode");
      areaCodeEl.appendChild(doc.createTextNode(phone.getAreaCode() + ""));
      phoneEl.appendChild(areaCodeEl);
      phoneEl.appendChild(doc.createTextNode("\n        "));
      Element exchangeEl = doc.createElement("Exchange");
      exchangeEl.appendChild(doc.createTextNode(phone.getExchange()));
      phoneEl.appendChild(exchangeEl);
      phoneEl.appendChild(doc.createTextNode("\n        "));
      Element numberEl = doc.createElement("Number");
      numberEl.appendChild(doc.createTextNode(phone.getNumber()));
      phoneEl.appendChild(numberEl);
      phoneEl.appendChild(doc.createTextNode("\n      "));
      addressEl.appendChild(phoneEl);
      addressEl.appendChild(doc.createTextNode("\n    "));
      listingEl.appendChild(addressEl);
      listingEl.appendChild(doc.createTextNode("\n  "));
      bookEl.appendChild(doc.createTextNode("  "));
      bookEl.appendChild(listingEl);
      bookEl.appendChild(doc.createTextNode("\n"));
    }

    return bookEl;
  }

  /**
   * Describe <code>putListings</code> method here.
   *
   * @param el an <code>Element</code> value
   * @return an <code>int</code> value
   */
  public int putListings(Element el)
  {
    Element listingEl = getFirstChildElement(el);
    int count = 0;

    while (listingEl != null)
    {
      String name = null;
      int    streetNum = 0;
      String streetName = "";
      String city = "";
      String state = "";
      int    zip = 0;
      int    areaCode = 0;
      String exchange = "";
      String number = "";

      Element tempEl = getFirstChildElement(listingEl);

      while (tempEl != null)
      {
        String tagName = tempEl.getTagName();

        if (tagName.equals("Name"))
        {
          name = getChildCharacterData(tempEl);
        }
        else if (tagName.equals("Address"))
        {
          Element tempEl2 = getFirstChildElement(tempEl);

          while (tempEl2 != null)
          {
            String tagName2 = tempEl2.getTagName();
            String content2 = getChildCharacterData(tempEl2);

            if (tagName2.equals("StreetNum"))
            {
              streetNum = Integer.parseInt(content2);
            }
            else if (tagName2.equals("StreetName"))
            {
              streetName = content2;
            }
            else if (tagName2.equals("City"))
            {
              city = content2;
            }
            else if (tagName2.equals("State"))
            {
              state = content2;
            }
            else if (tagName2.equals("Zip"))
            {
              zip = Integer.parseInt(content2);
            }
            else if (tagName2.equals("City"))
            {
              city = content2;
            }
            else if (tagName2.equals("PhoneNumber"))
            {
              Element tempEl3 = getFirstChildElement(tempEl2);

              while (tempEl3 != null)
              {
                String tagName3 = tempEl3.getTagName();
                String content3 = getChildCharacterData(tempEl3);

                if (tagName3.equals("AreaCode"))
                {
                  areaCode = Integer.parseInt(content3);
                }
                else if (tagName3.equals("Exchange"))
                {
                  exchange = content3;
                }
                else if (tagName3.equals("Number"))
                {
                  number = content3;
                }

                tempEl3 = getNextSiblingElement(tempEl3);
              }
            }

            tempEl2 = getNextSiblingElement(tempEl2);
          }
        }

        tempEl = getNextSiblingElement(tempEl);
      }

      if (name != null)
      {
        Address address = new Address(streetNum, streetName, city, state,
                                      zip, new PhoneNumber(areaCode,
                                                           exchange,
                                                           number));

        addEntry(name, address);
        count++;
      }

      listingEl = getNextSiblingElement(listingEl);
    }

    return count;
  }

  /**
   * Describe <code>removeEntry</code> method here.
   *
   * @param name a <code>String</code> value
   */
  public String removeEntry(String name)
  {
    String ret = null;


    if (name2AddressTable.containsKey(name) == true)
    {
      name2AddressTable.remove(name);
      ret = name;
    }
    
    return ret;
  }

  /**
   * Describe <code>removeAll</code> method here.
   *
   */
  public void removeAll()
  {
    name2AddressTable.clear();
  }
}
