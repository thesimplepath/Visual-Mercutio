public class buyService {
  // Dummy Web Service - just return a simple receipt
  /////////////////////////////////////////////////////
  public String buy( String symbol, int amount ) {
    return( "Bought " + amount +  " share(s) of " + symbol + " stock\n\n" );
  }
}
