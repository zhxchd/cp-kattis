/*
 * https://open.kattis.com/problems/copsandrobbers
 * Author: Xiaochen Zhu, xczhu@proton.me
 * 
 * Disclaimer: max flow algorithms are copied from
 * https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;  // large enough

class max_flow
{
private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t)
    { // find augmenting path
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1}); // record BFS sp tree
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == t)
                break; // stop as sink t reached
            for (auto &idx : AL[u])
            { // explore neighbors of u
                // auto [v, cap, flow] = EL[idx];          // stored in EL[idx]
                auto &v = get<0>(EL[idx]);
                auto &cap = get<1>(EL[idx]);
                auto &flow = get<2>(EL[idx]);
                if ((cap - flow > 0) && (d[v] == -1))            // positive residual edge
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
            }
        }
        return d[t] != -1; // has an augmenting path
    }

    ll send_one_flow(int s, int t, ll f = INF)
    { // send one flow from s->t
        if (s == t)
            return f; // bottleneck edge f found
        // auto &[u, idx] = p[t];
        auto &u = p[t].first;
        auto &idx = p[t].second;
        auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
        ll pushed = send_one_flow(s, u, min(f, cap - flow));
        flow += pushed;
        auto &rflow = get<2>(EL[idx ^ 1]); // back edge
        rflow -= pushed;                   // back flow
        return pushed;
    }

    ll DFS(int u, int t, ll f = INF)
    { // traverse from s->t
        if ((u == t) || (f == 0))
            return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i)
        { // from last edge
            //   auto &[v, cap, flow] = EL[AL[u][i]];
            auto &v = get<0>(EL[AL[u][i]]);
            auto &cap = get<1>(EL[AL[u][i]]);
            auto &flow = get<2>(EL[AL[u][i]]);
            if (d[v] != d[u] + 1)
                continue; // not part of layer graph
            if (ll pushed = DFS(v, t, min(f, cap - flow)))
            {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]); // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    max_flow(int initialV) : V(initialV)
    {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v)
            return;                              // safeguard: no self loop
        EL.emplace_back(v, w, 0);                // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);          // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0); // back edge
        AL[v].push_back(EL.size() - 1);          // remember this index
    }

    ll edmonds_karp(int s, int t)
    {
        ll mf = 0; // mf stands for max_flow
        while (BFS(s, t))
        {                               // an O(V*E^2) algorithm
            ll f = send_one_flow(s, t); // find and send 1 flow f
            if (f == 0)
                break; // if f == 0, stop
            mf += f;   // if f > 0, add to mf
        }
        return mf;
    }

    ll dinic(int s, int t)
    {
        ll mf = 0; // mf stands for max_flow
        while (BFS(s, t))
        {                            // an O(V^2*E) algorithm
            last.assign(V, 0);       // important speedup
            while (ll f = DFS(s, t)) // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int m, n, c, in, out, n_in[30][30], n_out[30][30];
ll cost[30][30], costs[27];
char terrain[30][30];

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> c;  // m lines of n nodes

    int id = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> terrain[i][j];
            n_in[i][j] = id++;
            n_out[i][j] = id++;
            if (terrain[i][j] == 'B') {
                in = n_in[i][j];
            }
        }
    }

    out = id++;
    max_flow mf(id);

    for (int i = 0; i < c; i++) {
        cin >> costs[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (terrain[i][j] != '.' && terrain[i][j] != 'B') {
                cost[i][j] = costs[terrain[i][j] - 'a'];
            } else {
                cost[i][j] = INF;
            }
            mf.add_edge(n_in[i][j], n_out[i][j], cost[i][j]);
        }
    }

    // add edges for neighbors
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // [i][j] to four neighbors
            if (i == 0) {
                mf.add_edge(n_out[i][j], out, INF);
            } else {
                // i, j to neighbor
                mf.add_edge(n_out[i][j], n_in[i-1][j], INF);
            }
            if (j == 0) {
                mf.add_edge(n_out[i][j], out, INF);
            } else {
                mf.add_edge(n_out[i][j], n_in[i][j-1], INF);
            }
            if (i == m-1) {
                mf.add_edge(n_out[i][j], out, INF);
            } else {
                mf.add_edge(n_out[i][j], n_in[i+1][j], INF);
            }
            if (j == n-1) {
                mf.add_edge(n_out[i][j], out, INF);
            } else {
                mf.add_edge(n_out[i][j], n_in[i][j+1], INF);
            }
        }
    }

    auto maxflow = mf.dinic(in, out);
    if (maxflow == INF || maxflow == 0) {
        cout << -1 << endl;
    } else {
        cout << maxflow << endl;
    }

    return 0;
}