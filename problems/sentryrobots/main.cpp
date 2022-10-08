/*
 * https://open.kattis.com/problems/sentryrobots
 * Author: Xiaochen Zhu, xczhu@proton.me
 * 
 * Disclaimer: max flow is from https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
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

int c, y, x, p, o, t1, t2;
set<pair<int, int>> pts, pts1, pts2, obs, obs1;

// transform the map such that the obstacle no longer matters
// if there's an obstacle on row r, column c,
// insert one row above (with the points left than c) and one row below r (with points right than c)
// add 2*o rows and 2*o columns

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c > 0) {
        c--;
        cin >> y >> x >> p;
        pts.clear();
        pts1.clear();
        pts2.clear();
        obs.clear();
        obs1.clear();
        for (int i = 0; i < p; i++) {
            cin >> t1 >> t2;
            pts.insert(make_pair(t1-1, t2-1));
        }
        cin >> o;
        for (int i = 0; i < o; i++) {
            cin >> t1 >> t2;
            obs.insert(make_pair(t1-1, t2-1));
        }
        // now for each row partitioned by ob points, we copy each partition to a new row
        int dx = 0, dy = 0;
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                auto it = pts.find(make_pair(i, j));
                if (it != pts.end()) {
                    // pts.erase(it);
                    pts1.insert(make_pair(dy, j));
                    // dy += 1;
                } else {
                    it = obs.find(make_pair(i, j));
                    if (it != obs.end()) {
                        dy += 1;
                        obs1.insert(make_pair(dy, j));
                        dy += 1;
                    }
                }
            }
            dy += 1;
        }
        // y becomes y + dy + 1, x is x
        
        y += y + dy + 1;

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                auto it = pts1.find(make_pair(j, i));
                if (it != pts1.end()) {
                    // pts.erase(it);
                    pts2.insert(make_pair(j, i+dx));
                } else {
                    it = obs1.find(make_pair(j, i));
                    if (it != obs1.end()) {
                        dx += 1;
                    }
                }
            }
            dx += 1;
        }
        
        x = x + dx + 1;
        y = y + dy + 1;

        // now we have a good pts set
        // build bipartite graph: L with y rows, R with x columns
        max_flow mf(x+y+2);
        // 0 is source, 1,...,y are left, y+1,y+2,...,y+x are right, y+x+1 is end
        for (int i = 1; i <= y; i++) {
            mf.add_edge(0, i, 1);
        }
        for (int i = y+1; i <= y+x; i++) {
            mf.add_edge(i, x+y+1, 1);
        }
        for (pair<int, int> pt : pts2) {
            mf.add_edge(pt.first + 1, pt.second + y + 1, 1);
        }
        cout << mf.dinic(0, x+y+1) << endl;
    }

    return 0;
}