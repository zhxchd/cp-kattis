/*
 * https://open.kattis.com/problems/airports
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;  // large enough

class max_flow {
   private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {  // find augmenting path
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});  // record BFS sp tree
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t)
                break;                 // stop as sink t reached
            for (auto &idx : AL[u]) {  // explore neighbors of u
                // auto [v, cap, flow] = EL[idx];          // stored in EL[idx]
                auto &v = get<0>(EL[idx]);
                auto &cap = get<1>(EL[idx]);
                auto &flow = get<2>(EL[idx]);
                if ((cap - flow > 0) && (d[v] == -1))             // positive residual edge
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};  // 3 lines in one!
            }
        }
        return d[t] != -1;  // has an augmenting path
    }

    ll send_one_flow(int s, int t, ll f = INF) {  // send one flow from s->t
        if (s == t)
            return f;  // bottleneck edge f found
        // auto &[u, idx] = p[t];
        auto &u = p[t].first;
        auto &idx = p[t].second;
        auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
        ll pushed = send_one_flow(s, u, min(f, cap - flow));
        flow += pushed;
        auto &rflow = get<2>(EL[idx ^ 1]);  // back edge
        rflow -= pushed;                    // back flow
        return pushed;
    }

    ll DFS(int u, int t, ll f = INF) {  // traverse from s->t
        if ((u == t) || (f == 0))
            return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {  // from last edge
            //   auto &[v, cap, flow] = EL[AL[u][i]];
            auto &v = get<0>(EL[AL[u][i]]);
            auto &cap = get<1>(EL[AL[u][i]]);
            auto &flow = get<2>(EL[AL[u][i]]);
            if (d[v] != d[u] + 1)
                continue;  // not part of layer graph
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);  // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

   public:
    max_flow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v)
            return;                               // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index
    }

    ll edmonds_karp(int s, int t) {
        ll mf = 0;                       // mf stands for max_flow
        while (BFS(s, t)) {              // an O(V*E^2) algorithm
            ll f = send_one_flow(s, t);  // find and send 1 flow f
            if (f == 0)
                break;  // if f == 0, stop
            mf += f;    // if f > 0, add to mf
        }
        return mf;
    }

    ll dinic(int s, int t) {
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int n, m; // n is the number of airports; m is the number of flights
vector<ll> t; // t = ll[n]
vector<vector<ll>> d, sp; // d = ll[n][n], sp = ll[n][n]
vector<int> from, to;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    // resize stuff
    t.resize(n);
    from.resize(m);
    to.resize(m);
    d.resize(n);
    sp.resize(n);
    for (int i = 0; i < n; i++) {
        d[i].resize(n);
        sp[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            if (i != j) {
                d[i][j] += t[j];
            }
        }
    }
    // let's reuse the vector t
    t.clear();
    t.resize(m);

    // now we can use FW for APSP
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sp[i][j] = d[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (sp[i][j] > (sp[i][k] + sp[k][j])) {
                    sp[i][j] = sp[i][k] + sp[k][j];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        // m flights
        cin >> from[i] >> to[i] >> t[i];
        from[i] -= 1;
        to[i] -= 1;
    }

    max_flow mf = max_flow(2+2*m);

    // each flight i has: start i (2i+1) and end i (2i+2)
    for (int i = 0; i < m; i++) {
        mf.add_edge(0, 2*i+1, 1);
        mf.add_edge(2*i+2, 2*m+1, 1);
    }

    // if flight i can be done right after flight j: connect end j (2j+2) with start i (2i+1) (from 2i+1 to 2j+2)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j) {
                // let's check whether i can be done right after j
                // start time of j + time from j.from to j.to + shortest time from j.to to i.from <= start time of i
                if (t[j] + d[from[j]][to[j]] + sp[to[j]][from[i]] <= t[i]) {
                    mf.add_edge(2*i+1, 2*j+2, 1);
                }
            }
        }
    }

    cout << m - mf.dinic(0, 2*m+1) << endl;

    return 0;
}