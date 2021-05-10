import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws Exception {
        System.out.println((int) Math.floor(Math.random() * 2 + 1));
        while (true) {
            int x = Integer.parseInt(br.readLine());
            if (x == 99) {
                return;
            } else if (x % 3 == 0) {
                System.out.println(x + (int) Math.floor(Math.random() * 2 + 1));
            } else {
                System.out.println((x / 3 + 1) * 3);
                if ((x / 3 + 1) * 3 == 99) return;
            }
        }
    }
}