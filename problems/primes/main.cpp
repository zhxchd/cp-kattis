#include <iostream>
#include <set>
using namespace std;

long long n, *p, l, r;

set<long long> powerset(set<long long> a, set<long long> b) {
    set<long long> to_return = b;
    auto b_end = b.end();
    for (long long ai : a) {
        if (ai != 1) {
            for (auto it = b.begin(); it != b.end(); ++it) {
                if (ai * (*it) <= r) {
                    to_return.insert(ai * *(it));
                } else {
                    b_end = it;
                    break;
                }
            }
        }
    }
    return to_return;
}

set<long long> get_powers(long long x) {
    set<long long> to_return;
    long long prev = 1;
    while (true) {
        if (prev <= r) {
            to_return.insert(prev);
            prev = x * prev;
        } else {
            return to_return;
        }
    }
    return to_return;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (cin >> n) {
        if (n == 0) return 0;
        bool first = 1;
        p = new long long[n];
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        cin >> l >> r;
        set<long long> pows;
        set<long long> result = {1};
        for (int i = 0; i < n; ++i) {
            pows = get_powers(p[i]);
            result = powerset(result, pows);
        }
        for (auto it = result.lower_bound(l); it != result.end(); ++it) {
            if (first) {
                cout << *it;
                first = 0;
            } else {
                cout << ',' << *it;
            }
        }
        if (first) {
            cout << "none";
        }
        cout << endl;
    }

    return 0;
}
