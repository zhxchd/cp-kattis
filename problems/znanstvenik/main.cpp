#include <iostream>
#include <set>
using namespace std;

int r, c;
char m[1000][1000];
set<string> s;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> c;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> m[j][r - i - 1];
        }
    }

    // now the matrix has c rows and r columns,
    // delete the rightmost columns
    // find the maximum number of columns to delete

    for (int x = 1; x <= r; ++x) {
        // remain leftmost x rows
        s = {};
        bool dup = false;
        for (int i = 0; i < c; ++i) {
            if (!s.insert(string(m[i], x)).second) {
                dup = true;
                break;
            }
        }
        if (!dup) {
            cout << r - x << endl;
            return 0;
        }
    }

    return 0;
}