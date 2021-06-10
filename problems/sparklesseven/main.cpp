#include <iostream>
using namespace std;

int x[7][7];
bool p[7] = {0};

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            cin >> x[i][j];
            if (!p[j] && x[i][j]) {
                p[j] = true;
            }
        }
    }

    for (int i = 0; i < 7; ++i) {
        if (!p[i]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    cout << "POSSIBLE" << endl;

    return 0;
}