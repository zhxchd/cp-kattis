import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws Exception {
        int n = Integer.parseInt(br.readLine());

        Map<String, Integer> map = new TreeMap<>();

        String[] names = new String[n];
        int[] c = new int[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            names[i] = st.nextToken();
            c[i] = Integer.parseInt(st.nextToken());
            String date = st.nextToken();
            if (map.containsKey(date)) {
                if (c[map.get(date)] < c[i]) {
                    map.put(date, i);
                }
            } else {
                map.put(date, i);
            }
        }
        System.out.println(map.size());
        map.values().stream().map(i -> names[i]).sorted().forEach(s -> System.out.println(s));
    }
}
