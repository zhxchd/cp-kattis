#include <iostream>
#include <queue>
using namespace std;

int n, k, *t, *d, nd;

bool verify(int tlimit) {
    int num = 0;
    for (int i = 0; i < nd; ++i) {
        int r = tlimit / d[i];
        if (r > 0) {
            num += 1 + (r + 1) / 2 * 4;
        }
    }
    return num >= n;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    nd = min(n, k);
    t = new int[n];
    d = new int[nd];

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        q.push(t[i]);
    }

    for (int i = 0; i < nd; ++i) {
        d[i] = q.top();
        q.pop();
    }

    int r = (2 * ((n - 1) / 4 + 1) - 1) * d[0], l = 0;

    // at any time: v(r) = true but v(l) = false
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (verify(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r << endl;

    return 0;
}