/*
 * https://open.kattis.com/problems/shopping
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, x, y, s, shops[11];
long long d, dist[11][100001];
vector<pair<int, long long>> neighbors[100001];

void sssp(int source_id) {
    int source = shops[source_id];

    for (int i = 0; i < n; i++) {
        dist[source_id][i] = LONG_LONG_MAX;
    }

    // pq stores <dist, node> pairs
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    bool popped[100001] = {0};
    dist[source_id][source] = 0ll;
    pq.push(make_pair(0ll, source));

    while(!pq.empty()) {
        auto curr = pq.top();
        long long curr_d = curr.first;
        int curr_node = curr.second;
        pq.pop();

        if (popped[curr_node]) {
            continue;
        } else {
            popped[curr_node] = true;
        }

        for (auto nd : neighbors[curr_node]) {
            int n = nd.first;
            long long d = nd.second; // distance from curr_node to n
            long long alt_d = curr_d + d;
            if (dist[source_id][n] > alt_d) {
                dist[source_id][n] = alt_d;
                pq.push(make_pair(alt_d, n));
            }
        }
    }
}

long long get_cost(int perm[]) {
    long long res = 0ll;
    for (int i = 0; i < s+1; i++) {
        res += dist[perm[i]][shops[perm[i+1]]];
    }
    return res;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> d;
        neighbors[x].push_back(make_pair(y, d));
        neighbors[y].push_back(make_pair(x, d));
    }

    cin >> s;
    
    shops[0] = 0;
    for (int i = 0; i < s; i++) {
        cin >> shops[i+1];
    }

    // first, we need to find the distance among 0 and all shops, so that we have a TSP
    for (int i = 0; i < s+1; i++) {
        sssp(i);
    }

    // now, we have all the distances among all shops, it becomes a TSP.
    long long cost = LONG_LONG_MAX;

    int perm[15];
    perm[0] = 0;
    perm[s+1] = 0;
    for (int i = 1; i < s+1; i++) {
        perm[i] = i;
    }

    do {
        long long alt_cost = get_cost(perm);
        if (alt_cost < cost) {
            cost = alt_cost;
        }
    } while (next_permutation(perm+1, perm+s+1));

    cout << cost << endl;

    return 0;
}