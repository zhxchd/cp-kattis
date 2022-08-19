import java.util.*;
import java.io.*;
import java.math.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer st;
    static BigDecimal a, b, c, ans;
    static MathContext mc = new MathContext(100);

    public static void main(String[] args) throws Exception {
        st = new StringTokenizer(br.readLine());
        a = new BigDecimal(st.nextToken());
        b = new BigDecimal(st.nextToken());
        c = new BigDecimal(st.nextToken());

        ans = a.multiply(b).divide(c, mc);
        bw.write(ans.toString());
        bw.write("\n");
        bw.close();
    }
}