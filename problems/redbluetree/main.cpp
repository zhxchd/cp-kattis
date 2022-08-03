#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;


int v, e, k;
vector<tuple<int, int, int>> edges;

// for ufds
vector<int> id, sz;

int root(int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

int unite(int p, int q) {
    int i = root(p);
    int j = root(q);
    if (i == j) {
        return sz[i];
    } else if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
        return sz[j];
    } else {
        id[j] = i;
        sz[i] += sz[j];
        return sz[i];
    }
}

int kruskal() {
    int num = 0;
    id.clear();
    sz.clear();
    for (int i = 0; i < v; i++) {
        id.push_back(i);
        sz.push_back(1);
    }
    for (auto edge : edges) {
        int is_blue = get<0>(edge);
        int v1 = get<1>(edge);
        int v2 = get<2>(edge);
        // cout << "visited :";
        // for (auto node : visited) {
        //     cout << node << " ";
        // }
        // cout << endl;
        if (root(v1) != root(v2)) {
            unite(v1, v2);
            // cout << "Add edge " << v1 << ", " << v2 << endl;
            if (is_blue) {
                num++;
            }
            if (sz[root(v1)] == v) {
                break;
            }
        }
    }
    return num;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> e >> k;

    char temp;
    int a, b;

    for (int i = 0; i < e; i++) {
        cin >> temp >> a >> b;
        edges.push_back(make_tuple(temp == 'B', a-1, b-1));
    }

    sort(edges.begin(), edges.end()); //red (0) -> blue (1)
    // cout << get<0>(edges[0]) << get<0>(edges[1]) << get<0>(edges[2]);
    int min_blue = kruskal(); // min number of blue edges

    // cout << min_blue << endl;
    if (k < min_blue) {
        cout << 0 << endl;
        return 0;
    }

    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end()); // blue (1) -> red (0)
    int max_blue = kruskal(); // max number of blue edges, starting from the blue edges in the first run
    cout << (k <= max_blue) << endl;

    return 0;
}