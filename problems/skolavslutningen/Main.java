import java.util.*;
import java.io.*;

class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws Exception {
        StringTokenizer st = new StringTokenizer(br.readLine());
        int r = Integer.parseInt(st.nextToken());
        int c = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());
        UF uf = new UF(n);
        if (r == 1) {
            bw.write(String.valueOf(n));
            bw.write("\n");
            bw.close();
            return;
        }
        int[] firstLine = new int[c];
        for (int i = 0; i < c; i++) {
            firstLine[i] = br.read() - 65;
        }
        br.skip(1);
        for (int i = 1; i < r; i++) {
            for (int j = 0; j < c; j++) {
                uf.union(br.read() - 65, firstLine[j]);
            }
            br.skip(1);
        }
        bw.write(String.valueOf(uf.numOfSets));
        bw.write("\n");
        bw.close();
    }
}

class UF {
    private int[] id;
    public int numOfSets;
    private int[] sz;

    public UF(int N) {
        id = new int[N];
        sz = new int[N];
        numOfSets = N;
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    private int root(int i) {
        while (i != id[i]) {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    public boolean find(int p, int q) {
        return root(p) == root(q);
    }

    public void union(int p, int q) {
        int i = root(p);
        int j = root(q);
        if (i != j) {
            numOfSets--;
        }
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
}