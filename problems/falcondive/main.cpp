#include <iostream>
using namespace std;

int m, n;
char x, z;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> m >> n >> z >> x >> z) {
    char bg[m][n];
    int anchor[2];
    int delta[2];
    bool tl = false;
    bool s[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> bg[i][j];
            if (!tl && bg[i][j] == x) {
                anchor[0] = i;
                anchor[1] = j;
                tl = true;
            }
        }
    }

    tl = false;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> z;
            if (z == x) {
                s[i][j] = true;
                if (!tl) {
                    delta[0] = i - anchor[0];
                    delta[1] = j - anchor[1];
                    tl = true;
                }
            } else {
                s[i][j] = false;
                bg[i][j] = z;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int i1 = i - delta[0];
            int j1 = j - delta[1];
            if (i1 >= 0 && i1 < m && j1 >= 0 && j1 < n && s[i1][j1]) {
                cout << x;
            } else {
                cout << bg[i][j];
            }
        }
        cout << endl;
    }
}

    return 0;
}