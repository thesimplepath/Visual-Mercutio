package xkms;
import java.io.File;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class ModifySlapd {
    public static void main(String[] argv) throws Exception {
        String domain = argv[0]; // "o=TRL,c=JP"

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter wr = new PrintWriter(System.out);
        String line;
        while ((line = br.readLine()) != null) {
            wr.println(line);
            if (line.equalsIgnoreCase("ibm-slapdSuffix: cn=localhost"))
                wr.println("ibm-slapdSuffix: "+domain);
        }
        wr.close();
        br.close();
    }
}
