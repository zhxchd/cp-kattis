#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int r, c, *p, s, e, sz, result;

vector<int> nsquare(int pos) {
    // (c-1,r-1)
    vector<int> n = {};
    int x = pos % c, y = (pos - x) / c;
    if (x + 1 <= c - 1) {
        n.push_back(pos + 1);
    }
    if (x - 1 >= 0) {
        n.push_back(pos - 1);
    }
    if (y + 1 <= r - 1) {
        n.push_back(pos + c);
    }
    if (y - 1 >= 0) {
        n.push_back(pos - c);
    }
    return n;
}

vector<int> nempty(int pos) {
    // (c-1,r-1)
    vector<int> n = {};
    int x = pos % c, y = (pos - x) / c;
    if (x + 1 <= c - 1) {
        n.push_back(pos + 1);
        if (y + 1 <= r - 1) {
            n.push_back(pos + 1 + c);
        }
        if (y - 1 >= 0) {
            n.push_back(pos + 1 - c);
        }
    }
    if (x - 1 >= 0) {
        n.push_back(pos - 1);
        if (y + 1 <= r - 1) {
            n.push_back(pos - 1 + c);
        }
        if (y - 1 >= 0) {
            n.push_back(pos - 1 - c);
        }
    }
    if (y + 1 <= r - 1) {
        n.push_back(pos + c);
    }
    if (y - 1 >= 0) {
        n.push_back(pos - c);
    }
    return n;
}

bool connected() {
    int rm = sz;
    bool *v = new bool[r * c];
    memset(v, 0, r * c);
    queue<int> q = {};
    v[s] = true;
    rm--;
    q.push(s);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int i : nsquare(curr)) {
            if (p[i] && !v[i]) {
                v[i] = true;
                q.push(i);
                rm--;
            }
        }
    }
    return rm == 0;
}

bool no_holes() {
    if (sz == r * c) {
        return true;
    }

    int rm = r * c - sz;
    bool *v = new bool[r * c];
    memset(v, 0, r * c);

    for (int i = 0; i < r * c; ++i) {
        if (!p[i] && !v[i]) {
            bool open = false;
            queue<int> q = {};
            v[i] = true;
            rm--;
            q.push(i);
            while (!q.empty()) {
                int curr = q.front();
                if (!open && nempty(curr).size() < 8) {
                    open = true;
                }
                q.pop();
                for (int i : nempty(curr)) {
                    if (!p[i] && !v[i]) {
                        v[i] = true;
                        q.push(i);
                        rm--;
                    }
                }
            }
            if (!open) return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> r >> c;

    result = 0;

    // r*c squares -> 2^(rc) possibilities -> rc bit binary

    for (int i = 1; i < 1 << (r * c); ++i) {
        p = new int[r * c], s = -1, e = -1, sz = 0;
        // cout << "bitmask " << i << ": ";
        for (int j = 0; j < r * c; ++j) {
            p[j] = (i >> j) % 2;
            if (p[j] == 1) {
                sz++;
                if (s == -1) {
                    s = j;
                }
            } else if (e == -1) {
                e = j;
            }
            // cout << p[j] << " ";
        }
        // cout << "verified: " << (connected()) << endl;
        if (connected() && no_holes()) {
            result++;
        }
    }

    cout << result << endl;
    return 0;
}