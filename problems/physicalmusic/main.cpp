#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n, *d, c, best;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    while (t > 0) {
        vector<int> l;
        c = 0;
        cin >> n;
        d = new int[n + 1];
        best = n + 1;
        for (int i = 0; i < n; i++) {
            cin >> d[i + 1];
        }
        for (int i = n; i > 0; i--) {
            if (d[i] > i || best < d[i]) {
                c++;
                l.push_back(d[i]);
            }

            if (d[i] < best) {
                best = d[i];
            }
        }
        cout << c << endl;
        std::sort (l.begin(), l.end());
        for (auto i = l.begin(); i != l.end(); ++i) {
            cout << *i << endl;
        }
        t--;
    }

    return 0;
}