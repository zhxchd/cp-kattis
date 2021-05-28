#include <iostream>
#include <vector>
#include <array>
using namespace std;

int t;
char c;
vector<pair<int, int>> whites;

int dfs(pair<int, int> s, array<array<int, 10>, 10> b) {
    array<array<int, 10>, 10> copy = b;
    int x = s.first, y = s.second;
    int m = 0;
    if (x + 2 <= 9 && y + 2 <= 9 && b[x + 2][y + 2] == 0 && b[x + 1][y + 1] == -1) {
        copy[x + 2][y + 2] = -1, copy[x][y] = 0, copy[x + 1][y + 1] = 0;
        m = max(m, 1 + dfs(make_pair(x + 2, y + 2), copy));
        copy = b;
    }
    if (x + 2 <= 9 && y - 2 >= 0 && b[x + 2][y - 2] == 0 && b[x + 1][y - 1] == -1) {
        copy[x + 2][y - 2] = -1, copy[x][y] = 0, copy[x + 1][y - 1] = 0;
        m = max(m, 1 + dfs(make_pair(x + 2, y - 2), copy));
        copy = b;
    }
    if (x - 2 >= 0 && y - 2 >= 0 && b[x - 2][y - 2] == 0 && b[x - 1][y - 1] == -1) {
        copy[x - 2][y - 2] = -1, copy[x][y] = 0, copy[x - 1][y - 1] = 0;
        m = max(m, 1 + dfs(make_pair(x - 2, y - 2), copy));
        copy = b;
    }
    if (x - 2 >= 0 && y + 2 <= 9 && b[x - 2][y + 2] == 0 && b[x - 1][y + 1] == -1) {
        copy[x - 2][y + 2] = -1, copy[x][y] = 0, copy[x - 1][y + 1] = 0;
        m = max(m, 1 + dfs(make_pair(x - 2, y + 2), copy));
        copy = b;
    }
    return m;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;

    for (int i = 0; i < t; ++i) {
        array<array<int, 10>, 10> b = {};
        whites = {};
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                cin >> c;
                if (c == 'B') {
                    b[j][k] = -1;
                } else if (c == 'W') {
                    b[j][k] = 1;
                    whites.push_back(make_pair(j, k));
                } else {
                    b[j][k] = 0;
                }
            }
        }
        int m = 0;
        for (auto w : whites) {
            m = max(dfs(w, b), m);
        }
        cout << m << endl;
    }

    return 0;
}