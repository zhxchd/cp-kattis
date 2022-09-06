/*
 * https://open.kattis.com/problems/icecream2
 * Author: Xiaochen Zhu, xczhu@proton.me
 * 
 * Disclaimer: max flow algorithms are copied from
 * https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
 */

#include <bits/stdc++.h>
using namespace std;

typedef double ll;
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
                // stored in EL[idx]
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

int n, m, f, c, v, in, out, t1, t2;
ll lt;
map<pair<int, int>, ll> edges;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    in = 0;

    max_flow mf(n+1);

    cin >> f >> c >> v;
    out = f;
    mf.add_edge(in, c, INF);
    mf.add_edge(in, v, INF);
    for (int i = 0; i < m; i++) {
        cin >> t1 >> t2 >> lt;
        // edge t1 to t2 (undirected) with weight t3
        if (t1 > t2) {
            swap(t1, t2);
        }
        if (edges.find({t1, t2}) == edges.end()) {
            edges[{t1, t2}] = lt;
        } else {
            edges[{t1, t2}] += lt;
        }
    }

    for (auto x : edges) {
        mf.add_edge(x.first.first, x.first.second, x.second, false);
    }

    // we binary search the final answer
    int l = 0;
    ll r = mf.dinic(in, out);
    ll mid, max_m = 0;

    // final answer in [l, r]
    while (r >= l) {
        mid = (long long)((l + r) / 2); // mid keeps to be an integer
        // now test whether or not mid can work
        max_flow mf(n+1);
        mf.add_edge(in, c, mid/2.0);
        mf.add_edge(in, v, mid/2.0);
        for (auto x : edges) {
            mf.add_edge(x.first.first, x.first.second, x.second, false);
        }
        if (mf.dinic(in, out) == mid) {
            // then we can (possibly) go higher
            l = mid + 1;
            r = r;
            if (mid > max_m) {
                max_m = mid;
            }
        } else {
            // then we search in [l, mid-1];
            l = l;
            r = mid-1;
        }
    }

    cout << max_m << endl;

    return 0;
}