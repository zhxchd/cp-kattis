/*
 * https://open.kattis.com/problems/jupiter
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

const ll INF = 1e18; // large enough

// n is the number of downlinks, q is the number of queues and s is the number of sensors
int n, q, s;
ll ltemp;
int n_nodes, in, out, ss[35][105], q_in[35][35], q_out[35][35], d[35], temp;

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

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> q >> s;

    // create all node ids:
    int id = 0;
    in = id++;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < s; j++)
        {
            ss[i][j] = id++;
        }
        for (int j = 0; j < q; j++)
        {
            q_in[i][j] = id++;
        }
        for (int j = 0; j < q; j++)
        {
            q_out[i][j] = id++;
        }
        d[i] = id++;
    }
    out = id++;
    n_nodes = id;

    max_flow mf(n_nodes);

    for (int i = 0; i < s; i++)
    {
        cin >> temp; // ss[.][i] to q_in[.][t] with inf
        for (int j = 0; j < n; j++)
        {
            mf.add_edge(ss[j][i], q_in[j][temp - 1], INF);
        }
    }

    // now we connect q_in to q_out
    for (int i = 0; i < q; i++)
    {
        // collect capacity
        cin >> ltemp; // q_in[.][i] to q_out[.][i] with ltemp
        for (int j = 0; j < n; j++)
        {
            mf.add_edge(q_in[j][i], q_out[j][i], ltemp);
        }
    }

    // now we connect q_out to d
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < q; j++)
        {
            // q_out[.][j] to d_i
            mf.add_edge(q_out[i][j], d[i], INF);
        }
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < q; j++)
        {
            // q_out[i][j] to q_in[i+1][j] with inf
            mf.add_edge(q_out[i][j], q_in[i + 1][j], INF);
        }
    }

    // finally, we connect s to ss_i and d_i to t
    ll input = 0ll;
    for (int i = 0; i < n; i++)
    {
        cin >> ltemp; // d[i] to out with temp
        mf.add_edge(d[i], out, ltemp);
        for (int j = 0; j < s; j++)
        {
            cin >> ltemp; // in to ss[i][j] with ltemp
            input += ltemp;
            mf.add_edge(in, ss[i][j], ltemp);
        }
    }

    // Now we have everything in the graph, we just need to do a max flow
    // EK, probably slow, let's try

    if (mf.dinic(in, out) == input)
    {
        cout << "possible" << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }

    return 0;
}