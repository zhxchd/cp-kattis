#include <iostream>
#include <cmath>
using namespace std;

int x, l, r;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> x >> l >> r;

    int k = 0, found = 0;
    double prev = (double) x;

    while (!found) {
        if (ceil(prev) >= l && ceil(prev) <= r) {
            found = !found;
            cout << k << ' ';
        } else if (ceil(prev) > r) {
            cout << "impossible" << endl;
            return 0;
        }
        prev = 10 * sqrt(prev);
        k++;
    }

    if (r == 100) {
        cout << "inf" << endl;
        return 0;
    }

    while (true) {
        if (ceil(prev) > r) {
            cout << k - 1 << endl;
            return 0;
        } else {
            prev = 10 * sqrt(prev);
            k++;
        }
    }

    return 0;
}