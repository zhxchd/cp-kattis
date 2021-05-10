import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer st;

    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws Exception {
        st = new StringTokenizer(br.readLine());
        int v = Integer.parseInt(st.nextToken());
        int e = Integer.parseInt(st.nextToken());
        Map<Integer, Integer> c = new HashMap<>();
        int[] d = new int[v];
        boolean[] visit = new boolean[v];
        boolean[] inq = new boolean[v];
        List<Integer>[] adj = new List[v];
        for (int i = 0; i < v; i++) {
            adj[i] = new LinkedList<>();
            d[i] = Integer.MAX_VALUE;
        }
        for (int i = 0; i < e; i++) {
            st = new StringTokenizer(br.readLine());
            int v1 = Integer.parseInt(st.nextToken()) - 1;
            int v2 = Integer.parseInt(st.nextToken()) - 1;
            int a = Integer.parseInt(st.nextToken());
            adj[v1].add(v2);
            adj[v2].add(v1);
            c.put((v1 + v2) * (v1 + v2 + 1) / 2 + v2, a);
            c.put((v1 + v2) * (v1 + v2 + 1) / 2 + v1, a);
        }
        PriorityQueue<Integer> q = new PriorityQueue<>((v1, v2) -> Integer.compare(d[v1], d[v2]));
        q.offer(0);
        d[0] = 0;
        inq[0] = true;
        while (!q.isEmpty()) {
            int x = q.poll();
            visit[x] = true;
            if (x == v - 1) break;
            for (int y : adj[x]) {
                if (!visit[y]) {
                    int temp = c.get((x + y + 1) * (x + y) / 2 + y) + d[x];
                    if (temp < d[y]) {
                        d[y] = temp;
                        if (inq[y]) q.remove(y);
                    }
                    q.offer(y);
                    inq[y] = true;
                }
            }
        }
        bw.write(String.valueOf(d[v - 1]));
        bw.write("\n");
        bw.close();
    }
}