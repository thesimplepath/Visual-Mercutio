import com.ibm.wstk.xml.XMLReader;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import java.net.URL;
import java.net.URLConnection;
import java.io.StringReader;
import java.io.InputStream;

public class NasdaqQuotes { 
    
    static final String surl = "http://quotes.nasdaq.com/quote.dll?page=xml&mode=stock";
    
    public NasdaqQuote getQuote(String symbol) throws Exception {
        String nurl = this.surl + "&symbol=" + symbol;
        URL url = new URL(nurl);
        String res = doGet(url);
        StringReader sr = new StringReader(res);
        XMLReader xmlReader = new XMLReader(sr);
        Document d = xmlReader.read();
        NodeList nl = d.getDocumentElement().getChildNodes();
        for (int n = 0; n < nl.getLength(); n++) {
            if (nl.item(n).getNodeType() == Element.ELEMENT_NODE)
                return new NasdaqQuote((Element)nl.item(n));
        }
        return null;
    }
    
    private String doGet(URL url) throws Exception {
        URLConnection conn = null;
        InputStream in = null;
        String results = null;
        conn = url.openConnection();        
        byte[] buffer = new byte[0];
        byte[] chunk = new byte[4096];
        int count;
        in = conn.getInputStream();
        while ((count = in.read(chunk)) > 0) {
            byte[] t = new byte[buffer.length + count];
            System.arraycopy(buffer, 0, t, 0, buffer.length);
            System.arraycopy(chunk, 0, t, buffer.length, count);
            buffer = t;
        }
        results = new String(buffer);        
        return results;
    }
}
