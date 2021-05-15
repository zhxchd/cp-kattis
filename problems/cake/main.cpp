#include <iostream>
#include <set>
using namespace std;

int p, q, n;
set<int> *r;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> q >> n;

    r = new set<int>[p];

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        r[x - 1].insert(y - 1);
    }

    int l = 0, area = 0;
    for (int i = 0; i < p; i++) {
        if (!r[i].empty()) {
            int rhs = 0, low;
            n -= r[i].size();
            if (n == 0) low = p;
            else low = i + 1;
            for (const int &j : r[i]) {
                cout << l + 1 << ' ' << rhs + 1 << ' ' << low << ' ';
                if (j == *(r[i].rbegin())) {
                    area += (low - l) * (q - rhs);
                    rhs = q;
                } else {
                    area += (low - l) * (j - rhs + 1);
                    rhs = j + 1;
                }
                cout << rhs << endl;
            }
            l = low;
        }
    }

    cout << p * q - area << endl;

    return 0;
}