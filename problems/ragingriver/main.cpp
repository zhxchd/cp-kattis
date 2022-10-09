/*
 * https://open.kattis.com/problems/ragingriver
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

// mcmf is from https://github.com/jaehyunp/stanfordacm/blob/master/code/MinCostMaxFlow.cc

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost;
  VI found;
  VL dist, pi, width;
  VPII dad;

  MinCostMaxFlow(int N) : 
    N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)), 
    found(N), dist(N), pi(N), width(N), dad(N) {}
  
  void AddEdge(int from, int to, L cap, L cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }
  
  void Relax(int s, int k, L cap, L cost, int dir) {
    L val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  L Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;
    
    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  pair<L, L> GetMaxFlow(int s, int t) {
    L totflow = 0, totcost = 0;
    while (L amt = Dijkstra(s, t)) {
      totflow += amt;
      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }
    }
    return make_pair(totflow, totcost);
  }
};

int p, r, l, a, b; // p is num peopler, r is num of points, l is number of edges

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> p >> r >> l;
    // 0 is left bank, 1 is right bank, 2, 3, ..., r+1 are r points, r+2 is the super source, r+3 is super t
    MinCostMaxFlow mcmf = MinCostMaxFlow(r+4);
    mcmf.AddEdge(r+2, 0, p, 0);
    mcmf.AddEdge(1, r+3, p, 0);

    for (int i = 0; i < l; i++) {
        cin >> a >> b;
        mcmf.AddEdge(a+2, b+2, 1, 1);
        mcmf.AddEdge(b+2, a+2, 1, 1);
    }

    auto res = mcmf.GetMaxFlow(r+2, r+3);

    if (res.first < p) {
        cout << p - res.first << " people left behind" << endl;
    } else {
        cout << res.second << endl;
    }

    return 0;
}