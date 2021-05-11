import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer st;

    static int n, m, k;
    static List<Integer>[] adj;
    static int[] color;

    static long[][] d;
    static boolean[][] done;

    // at this dfs, [i]
    private static long dfs(int i, int colors) {
        if (done[i][colors]) return d[i][colors];
        d[i][colors] = 1l;
        for (int x : adj[i]) {
            int c = color[x];
            if (colors / (int) Math.pow(2, c) % 2 == 0) {
                d[i][colors] += dfs(x, colors + (int) Math.pow(2, c));
            }
        }
        done[i][colors] = true;
        return d[i][colors];
    }

    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws Exception {
        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        color = new int[n];
        d = new long[n][(int) Math.pow(2, k)];
        done = new boolean[n][(int) Math.pow(2, k)];

        adj = new List[n];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            color[i] = Integer.parseInt(st.nextToken()) - 1;
            adj[i] = new LinkedList<Integer>();
        }

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int v1 = Integer.parseInt(st.nextToken()) - 1;
            int v2 = Integer.parseInt(st.nextToken()) - 1;
            adj[v1].add(v2);
            adj[v2].add(v1);
        }

        long ans = 0l;
        for (int i = 0; i < n; i++) {
            ans += dfs(i, (int) Math.pow(2, color[i]));
        }

        bw.write(String.valueOf(ans - n));
        bw.write("\n");
        bw.close();
    }
}