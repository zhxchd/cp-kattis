/*
 * https://open.kattis.com/problems/cordonbleu
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

// https://github.com/jaehyunp/stanfordacm/blob/master/code/MinCostMaxFlow.cc

//////////////////////////////////////////////////////////////////////
// Min cost bipartite matching via shortest augmenting paths
//
// This is an O(n^3) implementation of a shortest augmenting path
// algorithm for finding min cost perfect matchings in dense
// graphs.  In practice, it solves 1000x1000 problems in around 1
// second.
//
//   cost[i][j] = cost for pairing left node i with right node j
//   Lmate[i] = index of right node that left node i pairs with
//   Rmate[j] = index of left node that right node j pairs with
//
// The values in cost[i][j] may be positive or negative.  To perform
// maximization, simply negate the cost[][] matrix.
//////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;


// to improve time complexity, I modify the stanfordacm code to allow unbalanced matrix
double MinCostMatching(const VVD &cost, VI &Lmate, VI &Rmate) {
    
    // n > m
    int n = int(cost.size());
    int m = int(cost[0].size());
    // cout << n << m << endl;

    // construct dual feasible solution
    VD u(n);
    VD v(m);
    for (int i = 0; i < n; i++) {
        u[i] = cost[i][0];
        for (int j = 1; j < m; j++) u[i] = min(u[i], cost[i][j]);
    }
    for (int j = 0; j < m; j++) {
        v[j] = cost[0][j] - u[0];
        for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
    }

    // construct primal solution satisfying complementary slackness
    Lmate = VI(n, -1);
    Rmate = VI(m, -1);
    int mated = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (Rmate[j] != -1) continue;
            if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
                Lmate[i] = j;
                Rmate[j] = i;
                mated++;
                break;
            }
        }
    }

    VD dist(m);
    VI dad(m);
    VI seen(m);

    // repeat until primal solution is feasible
    while (mated < n) {
        // find an unmatched left node
        int s = 0;
        while (Lmate[s] != -1) s++;

        // initialize Dijkstra
        fill(dad.begin(), dad.end(), -1);
        fill(seen.begin(), seen.end(), 0);
        for (int k = 0; k < m; k++)
            dist[k] = cost[s][k] - u[s] - v[k];

        int j = 0;
        while (true) {
            // find closest
            j = -1;
            for (int k = 0; k < m; k++) {
                if (seen[k]) continue;
                if (j == -1 || dist[k] < dist[j]) j = k;
            }
            seen[j] = 1;

            // termination condition
            if (Rmate[j] == -1) break;

            // relax neighbors
            const int i = Rmate[j];
            for (int k = 0; k < m; k++) {
                if (seen[k]) continue;
                const double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (dist[k] > new_dist) {
                    dist[k] = new_dist;
                    dad[k] = j;
                }
            }
        }

        // update dual variables
        for (int k = 0; k < m; k++) {
            if (k == j || !seen[k]) continue;
            const int i = Rmate[k];
            v[k] += dist[k] - dist[j];
            u[i] -= dist[k] - dist[j];
        }
        u[s] += dist[j];

        // augment along path
        while (dad[j] >= 0) {
            const int d = dad[j];
            Rmate[j] = Rmate[d];
            Lmate[Rmate[j]] = j;
            j = d;
        }
        Rmate[j] = s;
        Lmate[s] = j;

        mated++;
    }

    double value = 0;
    for (int i = 0; i < n; i++)
        value += cost[i][Lmate[i]];

    return value;
}

int n, m, a, b;  // n is num of bottles, m is num of couriers
vector<pair<int, int>> bottles, couriers;
pair<int, int> r;

int mdistance(pair<int, int> l1, pair<int, int> l2) {
    return abs(l1.first - l2.first) + abs(l1.second - l2.second);
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    bottles.resize(n);
    couriers.resize(m + n - 1);

    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        bottles[i] = make_pair(a, b);
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        couriers[i] = make_pair(a, b);
    }

    cin >> a >> b;
    r = make_pair(a, b);

    // Add additional couriers at restaurant
    for (int i = 0; i < n - 1; i++) {
        couriers[i + m] = make_pair(a, b);
    }

    // left is bottles, right is couriers
    vector<vector<double>> cost;  // n * n+m-1
    vector<int> lm, rm;           // n+m-1; n
    // cost[couriers][bottles]
    cost.resize(n+m-1);

    for (int i = 0; i < n+m-1; i++) {
        // cost[i].resize(n + m - 1);
        cost[i] = vector<double>(n+m-1, 0);
    }

    for (int i = 0; i < n + m - 1; i++) {
        for (int j = 0; j < n; j++) {
            double c = mdistance(couriers[i], bottles[j]) + mdistance(bottles[j], r);
            cost[i][j] = c;
        }
    }

    cout << (int)MinCostMatching(cost, lm, rm) << endl;

    return 0;
}