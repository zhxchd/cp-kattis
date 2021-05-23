#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;

int t, n, m, i, j, k, a, ttime, itime;
unordered_map<int, int> last_write;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    for (i = 0; i < t; ++i) {
        last_write = {};
        ttime = 0;

        cout << i + 1 << ' ';
        cin >> n;
        for (j = 0; j < n; ++j) {
            itime = 0;
            cin >> m;
            for (k = 0; k < m - 1; ++k) {
                cin >> a;
                itime = max(itime, last_write[a]);
            }
            cin >> a;
            itime++;
            last_write[a] = itime;
            ttime = max(itime, ttime);
        }

        cout << ttime << endl;
    }

    return 0;
}