#include <iostream>
using namespace std;

int x1, x2, n1, n2, *t1, *t2, tmax, i, i1, i2, m1, m2, d;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> x1 >> x2;

    cin >> n1;
    t1 = new int[n1 + 1];
    t1[0] = 0;
    for (i = 1; i < n1 + 1; i++) {
        cin >> t1[i];
    }

    cin >> n2;
    t2 = new int[n2 + 1];
    t2[0] = 0;
    for (i = 1; i < n2 + 1; i++) {
        cin >> t2[i];
    }

    if (x1 > x2) {
        swap(n1, n2);
        swap(x1, x2);
        swap(t1, t2);
    }

    // 1 chases 2:
    i1 = 1, i2 = 1, m1 = 0, m2 = 0, d = x2 - x1, tmax = max(t1[n1], t2[n2]);
    // cout << "Time 0: x1 = " << x1 << ", x2 = " << x2 << endl;
    for (i = 1; i <= tmax; ++i) {
        if (m1 && !m2) {
            d--;
        } else if (!m1 && m2) {
            d++;
        }
        // cout << "Time " << i << ": x1 = " << x1 << ", x2 = " << x2 << endl;
        if (d == 4) {
            cout << "bumper tap at time " << i << endl;
            return 0;
        }
        if (i1 < n1 + 1 && i == t1[i1]) {
            m1 = 1 - m1;
            i1++;
        }
        if (i2 < n2 + 1 && i == t2[i2]) {
            m2 = 1 - m2;
            i2++;
        }
    }

    if (m1 && !m2) {
        cout << "bumper tap at time " << tmax + d - 4 << endl;
        return 0;
    } else {
        cout << "safe and sound" << endl;
        return 0;
    }

}
