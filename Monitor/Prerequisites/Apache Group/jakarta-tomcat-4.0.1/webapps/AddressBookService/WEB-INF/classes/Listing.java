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

/**
 *
 * @author Alfredo da Silva (afdasilv@us.ibm.com)
 */
public class Listing
{
  private String name;
  private Address address;

  public Listing()
  {
  }

  public Listing(String name, Address address)
  {
    this.name = name;
    this.address = address;
  }

  public void setName(String name)
  {
    this.name = name;
  }

  public String getName()
  {
    return name;
  }

  public void setAddress(Address address)
  {
    this.address = address;
  }

  public Address getAddress()
  {
    return address;
  }

  public String toString()
  {
    return name + "\n" + address;
  }
}
