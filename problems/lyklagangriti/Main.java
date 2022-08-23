import java.io.*;

// This one TLE on the last two test groups

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws Exception {
        StringBuilder sb = new StringBuilder();
        int offset = 0;
        while (true) {
            int nextInt = br.read();
            if (nextInt == 10) break;
            char next = (char) nextInt;
            if (next == 'L') {
                offset--;
            } else if (next == 'R') {
                offset++;
            } else if (next == 'B') {
                offset--;
                sb.deleteCharAt(offset);
            } else {
                sb.insert(offset, next);
                offset++;
            }
        }
        bw.write(sb.toString());
        bw.write("\n");
        bw.flush();
    }
}