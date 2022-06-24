package samples.bidbuy.server.bid;

import samples.bidbuy.shared.*;

/**
 * Big/PurchaseOrder Service
 */
public class BidService {

    static int nextReceiptNumber = 9000;

    /**
     * Request a quote for a given quantity of a specified product
     * @param productName name of product
     * @param quantity number desired
     * @return Total amount in US$ for complete purchase
     */
    public double RequestForQuote(String productName, int quantity) {
        if (quantity < 100) {
           return 1.0 * quantity;
        } if (quantity < 1000) {
           return 0.8 * quantity;
        } else {
           return 0.7 * quantity;
        } 
 
    }

    /**
     * Purchase a given quantity of a specified product
     * @param productName name of product
     * @param quantity number desired
     * @param price desired price (!!!)
     * @param customerId who you are
     * @param shipTo where you want the goods to go
     * @param date where you want the goods to go
     * @return Receipt
     */
    public String SimpleBuy(String address, String productName, int quantity) {
      return "Receipt #" + (nextReceiptNumber++) + '\n' +
             "==============\n" +
             "Quantity=" + quantity + '\n' +
             "Product Name=" + productName + '\n' +
             "Address=" + address + '\n' +
             "Price=$" + RequestForQuote(productName, quantity) + "\n\n" +
             "Courtesy of Apache SOAP";
    }

    /**
     * Process a purchase order.
     * @return Receipt
     */
    public String Buy(PurchaseOrder po) {
      return "Receipt #" + (nextReceiptNumber++) + '\n' +
             "==============\n" + po + "\n\n" +
             "Courtesy of Apache SOAP";
    }

    /**
     * Let the world know that we are still alive...
     */
    public void Ping() {
    }

}
