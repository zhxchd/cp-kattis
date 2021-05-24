#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, lc, curr;
bool st = true, *lv;
vector<int> *adj;
vector<int> id = {}, sz = {};
vector<pair<int, int>> r;
vector<pair<int, int>> l;

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

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    if (n % 2 == 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    adj = new vector<int>[n];
    int e[n - 1][2];
    bool m[n][n];
    memset(m, 0 , sizeof(m));
    lv = new bool[n];

    for (int i = 0; i < n - 1; ++i) {
        cin >> e[i][0] >> e[i][1];
        e[i][0]--;
        e[i][1]--;
        adj[e[i][0]].push_back(e[i][1]);
        adj[e[i][1]].push_back(e[i][0]);
    }

    lv = new bool[n];
    lv[0] = true;
    queue<int> q = {};
    q.push(0);
    lc = 1;
    while (lc <= (n - 1) / 2) {
        curr = q.front();
        q.pop();
        for (auto it = adj[curr].begin(); lc <= (n - 1) / 2 && it != adj[curr].end(); ++it) {
            if (!lv[*it]) {
                lv[*it] = true;
                lc++;
                q.push(*it);
                m[curr][*it] = true;
                m[*it][curr] = true;
                l.push_back(make_pair(curr, *it));
            }
        }
    }

    // initialize UFDS for RHS
    for (int i = 0; i < n; ++i) {
        id.push_back(i);
        sz.push_back(1);
    }

    for (int j = 0; j < n - 1; ++j) {
        // edge e[j]
        if (!m[e[j][0]][e[j][1]]) {
            unite(e[j][0], e[j][1]);
            r.push_back(make_pair(e[j][0], e[j][1]));
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!lv[i]) {
            for (int j = 0; j < n; ++j) {
                if (lv[j] && root(i) != root(j)) {
                    l.push_back(make_pair(i, j));
                    unite(i, j);
                    r.push_back(make_pair(i, j));
                    lv[i] = true;
                    break;
                }
            }
        }
    }

    if (l.size() != n - 1 || r.size() != n - 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (auto it : l) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
    }

    for (auto it : r) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
    }

    return 0;
}