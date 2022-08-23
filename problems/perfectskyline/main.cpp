/*
 * https://open.kattis.com/problems/perfectskyline
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <iostream>
#include <vector>
using namespace std;

int n, s, temp; // n is the number of blocks, s is the number of buildings
int blocks[15], buildings[15];

vector<int> ways_to_build[15]; // ways_to_build[i] stores bitmasks of how to build building[i]
int solution[15]; // solution[i] is the final solution for building[i], as a bitmask
bool visited[15][32768] = {0}; // memorization to avoid duplicates, max 32768 bitmasks

void print_sol() {
    for (int i = 0; i < s; i++) {
        int mask = solution[i];
        vector<int> sol;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                sol.push_back(j+1);
            }
        }
        cout << sol.size();
        for (auto j : sol) {
            cout << " " << j;
        }
        cout << endl;
    }
    exit(0); // when print_sol is called, the problem is solved.
}

// i is the building index to build, used_bits is a bit map that represents how the blocks are utilized right now
void sol(int i, int used_bits) {
    if (i >= s) {
        // all buildings have been built, currently solution is a solution
        print_sol();
    }
    if (visited[i][used_bits]) {
        return;
    }
    
    // now to build building[i]
    for (auto way_to_build : ways_to_build[i]) {
        if ((way_to_build & used_bits) == 0) {
            // no block is to be used twice, can proceed
            solution[i] = way_to_build;
            sol(i+1, way_to_build | used_bits);
        }
    }

    visited[i][used_bits] = true;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> s;

    for (int i = 0; i < n; ++i) {
        cin >> blocks[i];
    }

    for (int i = 0; i < s; ++i) {
        cin >> buildings[i];
    }

    // for all buildings, we store all ways to build them in bit masks
    // we can do this because N and S are very small (i.e. <= 15)
    for (int i = 0; i < (1 << n); i++) {
        long long sum = 0ll;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {// bit indexed j is 1
                sum += blocks[j];
            }
        }
        for (int j = 0; j < s; j++) {
            if (sum == buildings[j]) {
                ways_to_build[j].push_back(i);
            }
        }
    }

    sol(0, 0);

    cout << "-1" << endl;

    return 0;
}