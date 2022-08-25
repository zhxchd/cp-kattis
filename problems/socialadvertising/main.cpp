/*
 * https://open.kattis.com/problems/socialadvertising
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <iostream>
using namespace std;

int t;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;

    while (t > 0) {

        int n, d, u, adj[20] = { 0 };

        cin >> n;

        for (int i = 0; i < n; i++) {
            cin >> d;
            for (int j = 0; j < d; j++) {
                cin >> u;
                adj[i] = adj[i] | (1 << (u-1));
                adj[u-1] = adj[u-1] | (1 << i);
            }
        }

        int min_count = n+1;

        for (int i = 1; i < (1 << n); i++) {
            bool valid = true;
            int count = 0;
            // each i is a vertex set choice
            for (int j = 0; j < n; j++) {
                if (i & (1<<j)) {
                    count++;
                } else if (!(adj[j] & i)) {
                    valid = false;
                    break;
                }
            }
            if (valid && count < min_count) {
                min_count = count;
            }
        }

        cout << min_count << endl;

        t--;
    }

    return 0;
}