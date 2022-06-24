package samples.bidbuy.shared;

import java.util.Date;

public class PurchaseOrder {

    // constructors

    public PurchaseOrder() {};

    public PurchaseOrder(String id, Date createDate, Address shipTo,
                         Address billTo, LineItem[] items)
    {
         this.poID=id;
         this.createDate=createDate;
         this.shipTo=shipTo;
         this.billTo=billTo;
         this.items=items;
    }
    
    // properties

    private String poID;
    public String getPoID() { return poID; }
    public void setPoID(String value) { poID=value; }

    private Date createDate;
    public Date getCreateDate() { return createDate; }
    public void setCreateDate(Date value) { createDate=value; }

    private Address shipTo;
    public Address getShipTo() { return shipTo; }
    public void setShipTo(Address value) { shipTo=value; }

    private Address billTo;
    public Address getBillTo() { return billTo; }
    public void setBillTo(Address value) { billTo=value; }

    private LineItem[] items;
    public LineItem[] getItems() { return items; }
    public void setItems(LineItem[] value) { items=value; }

    public String toString()
    {
      StringBuffer strBuf = new StringBuffer();

      strBuf.append("Purchase Order ID: " + poID + '\n');
      strBuf.append("Creation Date: " + createDate + "\n\n");
      strBuf.append("Ship To\n=======\n" + shipTo + '\n');
      strBuf.append("Bill To\n=======\n" + billTo + '\n');
      strBuf.append("Items\n=====\n");

      if (items != null)
      {
        for (int i = 0; i < items.length; i++)
        {
          strBuf.append("Item #" + (i+1) + ": " + items[i] + '\n');
        }
      }

      return strBuf.toString();
    }
}
  