#include <iostream>
#include <vector>
using namespace std;

// Enumerate all possibility (with DP)
// p[tb, i] = optimal reward for [i...n] if one is to buy stock on i
// p[true,i] = max of (if buy stock on i) p[false,i+1] - price[i] vs (if don't buy stock on i) p[true, i+1]
// p[false,i] = max of (if sell stock on i) p[true,i+2] + price[i] vs (don't sell stock on i) p[false, i+1]

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    int temp;
    vector<int> p; // price
    
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> temp;
        p.push_back(temp);
    }

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    int t[2][n+1];
    t[0][n-1] = p[n-1]; // 0 means not open to buy
    t[1][n-1] = 0;      // 1 means open to buy
    t[0][n-2] = max(p[n-2], p[n-1]);
    t[1][n-2] = max(p[n-1]-p[n-2], 0);

    for (int i = n - 3; i >= 0; --i) {
        t[0][i] = max(t[1][i+2]+p[i], t[0][i+1]);
        t[1][i] = max(t[0][i+1]-p[i], t[1][i+1]);
    }

    cout << t[1][0] << endl;

    return 0;
}