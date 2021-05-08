import java.util.*;
import java.io.*;

class Main {
    public static void main(String[] args) throws Exception {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         int size = Integer.parseInt(br.readLine());
         StringBuilder sb = new StringBuilder();
         for (int i = 0; i < size; i++) {
            sb.insert(0, "\n");
            sb.insert(0, br.readLine());
         }
         System.out.print(sb.toString());
    }
}