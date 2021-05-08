import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws Exception {
         int size = Integer.parseInt(br.readLine());
         print(size);
         bw.flush();
    }

    static void print(int size) throws Exception {
        if (size == 0) return;
        else {
            String temp = br.readLine();
            print(size - 1);
            bw.write(temp);
            bw.write("\n");
        }
    }
}