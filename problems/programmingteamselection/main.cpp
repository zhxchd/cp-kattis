/*
 * https://open.kattis.com/problems/programmingteamselection
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

int m, n; // n is the number of nodes, m is the number of edges
string s1, s2;
unordered_map<string, int> hmap;
int dp[1 << 15 + 1];
int neighbors[16];

void init() {
    n = 0;
    hmap.clear();
    for (int i = 0; i < 20; i++) {
        neighbors[i] = 0;
    }
    for (int i = 0; i < (1 << 15 + 1); ++i) {
        dp[i] = -1;
    }
}

bool sol(int mask, int rnum) {
    if (rnum % 3 != 0) {
        return false;
    }
    if (rnum == 0) {
        return true;
    }
    if (dp[mask] != -1) {
        return dp[mask];
    }
    bool res = false;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            for (int k = j+1; k < n; ++k) {
                if (
                    (mask & (1 << i)) == 0
                    && (mask & (1 << j)) == 0
                    && (mask & (1 << k)) == 0
                    && (neighbors[i] & (1 << j))
                    && (neighbors[j] & (1 << k))
                    && (neighbors[k] & (1 << i))
                    ) {
                        // i, j, k are not used and can form a triangle, let's try that!
                        // set mask i, j, and k-th bits to 1
                        res = res || sol(mask | (1 << i) | (1 << j) | (1 << k), rnum - 3);
                    }
            }
        }
    }
    dp[mask] = res;
    return res;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (true) {
        cin >> m;
        if (m == 0) {
            return 0;
        }

        init();

        for (int i = 0; i < m; i++) {
            cin >> s1 >> s2;
            if (hmap.find(s1) == hmap.end()) {
                hmap[s1] = n;
                n += 1;
            }
            if (hmap.find(s2) == hmap.end()) {
                hmap[s2] = n;
                n += 1;
            }
            neighbors[hmap[s1]] |= 1 << hmap[s2];
            neighbors[hmap[s2]] |= 1 << hmap[s1];
        }

        if (sol(0, n)) {
            cout << "possible" << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return 0;
}