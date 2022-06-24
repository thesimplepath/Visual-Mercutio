
import org.w3c.dom.*;

public class NasdaqQuote { 
   
    protected String symbol;
    protected String market;
    protected double todaysHigh;
    protected double todaysLow;
    protected double fiftyTwoHigh;
    protected double fiftyTwoLow;
    protected double lastSalePrice;
    protected double netPriceChange;
    protected String netPercentChange;
    protected long   shareVolume;
    protected double previousClosePrice;
    protected long   totalShares;
    protected String issuerWebSite;
    protected String tradingStatus;

    private String getNodeValue(String name, Element parent) {
        return parent.getElementsByTagName(name).item(0).getChildNodes().item(0).getNodeValue();
    }

    public NasdaqQuote() {}

    public NasdaqQuote(Element e) {
        setSymbol(e.getAttribute("symbol"));
        setMarket(getNodeValue("market-center-code", e));
        setTodaysHigh((new Double(getNodeValue("todays-high-price", e))).doubleValue());
        setTodaysLow((new Double(getNodeValue("todays-low-price", e))).doubleValue());
        setFiftyTwoWeekHigh((new Double(getNodeValue("fifty-two-wk-high-price", e))).doubleValue());
        setFiftyTwoWeekLow((new Double(getNodeValue("fifty-two-wk-low-price", e))).doubleValue());
        setLastSalePrice((new Double(getNodeValue("last-sale-price", e))).doubleValue());
        setNetPriceChange((new Double(getNodeValue("net-change-price", e))).doubleValue());
        setNetPercentChange(getNodeValue("net-change-pct", e));
        setShareVolume((new Long(getNodeValue("share-volume-qty", e))).longValue());
        setPreviousClosePrice((new Double(getNodeValue("previous-close-price", e))).doubleValue());
        setTotalShares((new Long(getNodeValue("total-outstanding-shares-qty", e))).longValue());
        setIssuerWebSite(getNodeValue("issuer-web-site-url", e));
        setTradingStatus(getNodeValue("trading-status",e));
    }
    
    public String toString() {
        String res = "Symbol:                   " + symbol + "\r\n"
                   + "Market:                   " + market + "\r\n"
                   + "Todays High:              " + todaysHigh + "\r\n"
                   + "Todays Low:               " + todaysLow + "\r\n"
                   + "52-Week High:             " + fiftyTwoHigh + "\r\n"
                   + "52-Week Low:              " + fiftyTwoLow + "\r\n"
                   + "Last Sale Price:          " + lastSalePrice + "\r\n"
                   + "Net Price Change:         " + netPriceChange + "\r\n"
                   + "Net Percent Change:       " + netPercentChange + "\r\n"
                   + "Total Share Volume:       " + shareVolume + "\r\n"
                   + "Previous Close Price:     " + previousClosePrice + "\r\n"
                   + "Total Outstanding Shares: " + totalShares + "\r\n"
                   + "Issuer Web Site:          " + issuerWebSite + "\r\n"
                   + "Trading Status:           " + tradingStatus + "\r\n";
        return res;
    }
    
    public String getSymbol() {
        return symbol;
    }
    
    public String getMarket() {
        return market;
    }
    
    public double getTodaysHigh() {
        return todaysHigh;
    }
    
    public double getTodaysLow() {
        return todaysLow;
    }
    
    public double getFiftyTwoWeekHigh() {
        return fiftyTwoHigh;
    }
    
    public double getFiftyTwoWeekLow() {
        return fiftyTwoLow;
    }
    
    public double getLastSalePrice() {
        return lastSalePrice;
    }
    
    public double getNetPriceChange() {
        return netPriceChange;
    }
    
    public String getNetPercentChange() {
        return netPercentChange;
    }
    
    public long getShareVolume() {
        return shareVolume;
    }
    
    public double getPreviousClosePrice() {
        return previousClosePrice;
    }
    
    public long getTotalShares() {
        return totalShares;
    }
    
    public String getIssuerWebSite() {
        return issuerWebSite;
    }
    
    public String getTradingStatus() {
        return tradingStatus;
    }
    
    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }
    
    public void setMarket(String market) {
        this.market = market;
    }
    
    public void setTodaysHigh(double todaysHigh) {
        this.todaysHigh = todaysHigh;
    }
    
    public void setTodaysLow(double todaysLow) {
        this.todaysLow = todaysLow;
    }
    
    public void setFiftyTwoWeekHigh(double fiftyTwoHigh) {
        this.fiftyTwoHigh = fiftyTwoHigh;
    }
    
    public void setFiftyTwoWeekLow(double fiftyTwoLow) {
        this.fiftyTwoLow = fiftyTwoLow;
    }
    
    public void setLastSalePrice(double lastSalePrice) {
        this.lastSalePrice = lastSalePrice;
    }
    
    public void setNetPriceChange(double netPriceChange) {
        this.netPriceChange = netPriceChange;
    }
    
    public void setNetPercentChange(String netPercentChange) {
        this.netPercentChange = netPercentChange;
    }
    
    public void setShareVolume(long shareVolume) {
        this.shareVolume = shareVolume;
    }
    
    public void setPreviousClosePrice(double previousClosePrice) {
        this.previousClosePrice = previousClosePrice;
    }
    
    public void setTotalShares(long totalShares) {
        this.totalShares = totalShares;
    }
    
    public void setIssuerWebSite(String issuerWebSite) {
        this.issuerWebSite = issuerWebSite;
    }
    
    public void setTradingStatus(String tradingStatus) {
        this.tradingStatus = tradingStatus;
    }
}
