#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int n, s, *a, *b;
int ud[10] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};
map<int, set<int>> vtoi;

struct NOT {
    int key;
    NOT(int const &i): key(i) { }

    bool operator()(int const &i) {
        return (i != key);
    }
};

int upside_down(int x) {
    int copy = x;
    int result = 0;
    while (x > 0) {
        if (ud[x % 10] != -1) {
            result = result * 10 + ud[x % 10];
            x = x / 10;
        } else {
            return -1;
        }
    }
    if (result == copy) {
        return -1;
    }
    return result;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;

    a = new int[n];
    b = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = upside_down(a[i]);
        vtoi[a[i]].insert(i);
        if (b[i] != -1) {
            vtoi[b[i]].insert(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!vtoi[s - a[i]].empty() && find_if(vtoi[s - a[i]].begin(), vtoi[s - a[i]].end(), NOT(i)) != vtoi[s - a[i]].end()) {
            cout << "YES" << endl;
            return 0;
        }
        if (b[i] != -1 && !vtoi[s - b[i]].empty() && find_if(vtoi[s - b[i]].begin(), vtoi[s - b[i]].end(), NOT(i)) != vtoi[s - b[i]].end()) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;

    return 0;
}