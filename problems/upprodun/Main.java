import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws Exception {
        int rooms = Integer.parseInt(br.readLine());
        int teams = Integer.parseInt(br.readLine());
        int q = teams / rooms;
        int r = teams - rooms * q;
        char[] chars = new char[q];
        for (int i = 0; i < q; i++) {
            chars[i] = '*';
        }
        String str = new String(chars);
        for (int i = 0; i < r; i++) {
            bw.write(str);
            bw.write("*\n");
        }
        for (int i = r; i < rooms; i++) {
            bw.write(str);
            bw.write("\n");
        }
        bw.close();
    }
}