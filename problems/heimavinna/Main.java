import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws Exception {
        int count = 0;
        int temp = 0;
        boolean isInterval = false;
        while (true) {
            int next = br.read();
            if (next == 10) {
                if (isInterval) {
                    count = count + temp;
                } else {
                    count = count + 1;
                }
                System.out.println(count);
                return;
            }
            if (next == (int) '-') {
                count = count - temp + 1;
                isInterval = true;
                temp = 0;
            } else if (next == (int) ';') {
                if (isInterval) {
                    count = count + temp;
                } else {
                    count = count + 1;
                }
                isInterval = false;
                temp = 0;
            } else {
                temp = temp * 10 + next - 48;
            }
        }
    }
}