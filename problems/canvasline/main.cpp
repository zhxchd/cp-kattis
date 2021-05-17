#include <iostream>
#include <set>
using namespace std;

int n, *l, *r, p, x, *m;
bool *f, *f1;
set<int> pegs = {};

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    l = new int[n];
    r = new int[n];
    m = new int[n];
    f = new bool[n];
    f1 = new bool[n];

    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        m[i] = 2;
        f[i] = false;
        f1[i] = false;
    }

    cin >> p;

    int curr = 0;
    for (int i = 0; i < p && curr < n; i++) {
        cin >> x;
        if (l[curr] <= x && x <= r[curr]) {
            m[curr]--;
            if (m[curr] < 0) {
                cout << "impossible" << endl;
                return 0;
            }
            if (x == r[curr] - 1) {
                f1[curr] = true;
            }
            if (x == r[curr]) {
                f[curr] = true;
                if (curr + 1 < n && x == l[curr + 1]) {
                    m[curr + 1]--;
                    if (m[curr + 1] < 0) {
                        cout << "impossible" << endl;
                        return 0;
                    }
                }
                curr++;
            }
        } else if (x > r[curr]) {
            while (true) {
                curr++;
                if (curr >= n || (x <= r[curr])) break;
            }
            if (curr < n && l[curr] <= x && x <= r[curr]) {
                m[curr]--;
                if (x == r[curr] - 1) {
                    f1[curr] = true;
                }
                if (x == r[curr]) {
                    f[curr] = true;
                    if (curr + 1 < n && x == l[curr + 1]) {
                        m[curr + 1]--;
                    }
                    curr++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (m[i] == 1) {
            int d = 0;
            if (!f[i]) {
                if (i + 1 < n && r[i] == l[i + 1]) {
                    if (m[i + 1] > 0) {
                        m[i + 1]--;
                    } else if (!f1[i]) {
                        d = -1;
                    } else {
                        d = -2;
                    }
                }
            } else {
                d = -1;
            }
            pegs.insert(r[i] + d);
        } else if (m[i] == 2) {
            pegs.insert(r[i] - 1);
            if (i + 1 < n && r[i] == l[i + 1]) {
                if (m[i + 1] > 0) {
                    m[i + 1]--;
                    pegs.insert(r[i]);
                } else {
                    pegs.insert(r[i] - 2);
                }
            } else {
                pegs.insert(r[i]);
            }
        } else if (m[i] < 0) {
            cout << "impossible" << endl;
            return 0;
        }
    }

    cout << pegs.size() << endl;

    for (int it : pegs) {
        if (it == *(pegs.rbegin())) {
            cout << it << endl;
        } else {
            cout << it << ' ';
        }
    }

    return 0;
}