/*
This solution does not pass the OJ.
Time Limit Exceeded.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int l, a, lf = -1, rf = -1;

struct ant_t {
    int p0;
    float p;
    int d;
};

bool operator<(const ant_t& x, const ant_t& y) {
    return x.p < y.p;
}

float t, t0;
vector<ant_t> ants;
set<float> pq;

void update() {
    for (vector<ant_t>::iterator it = ants.begin(); it != ants.end(); ++it) {
        it->p += it->d * (t - t0);
        if (it != ants.begin() && it->p == (it - 1)->p) {
            (it - 1)->d = 0 - (it - 1)->d;
            it->d = 0 - it->d;
        }
        if (it != ants.begin() && it->d == -1 && (it - 1)->d == 1) {
            pq.insert(t + (it->p - (it - 1)->p) / 2.0);
        }
    }

    if (ants.begin()->p == 0 && ants.begin()->d == -1) {
        lf = ants.begin()->p0;
        ants.erase(ants.begin());
    } else {
        lf = -1;
    }

    if ((ants.end() - 1)->p == l && (ants.end() - 1)->d == 1) {
        rf = (ants.end() - 1)->p0;
        ants.erase(ants.end() - 1);
    } else {
        rf = -1;
    }

    if (ants.begin()->d == -1) {
        pq.insert(t + ants.begin()->p);
    }
    if ((ants.end() - 1)->d == 1) {
        pq.insert(t + l - (ants.end() - 1)->p);
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> l >> a) {
        t0 = 0.0;
        ants = {};
        pq = {};
        pq.insert(0);
        for (int i = 0; i < a; i++) {
            ant_t x;
            char c;
            cin >> x.p >> c;
            if (c == 'L') {
                x.d = -1;
            } else {
                x.d = 1;
            }
            x.p0 = x.p;
            ants.push_back(x);
        }

        sort(ants.begin(), ants.end());

        while (!ants.empty()) {
            t = *pq.begin();
            pq.erase(t);
            update();
            t0 = t;
        }

        cout << "The last ant will fall down in " << t << " seconds - started at ";
        if (lf >= 0 && rf >= 0) {
            cout << lf << " and " << rf << "." << endl;
        } else if (lf >= 0) {
            cout << lf << "." << endl;
        } else {
            cout << rf << "." << endl;
        }
    }

    return 0;
}