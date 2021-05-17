#include <iostream>
#include <cmath>
using namespace std;

int n, m;
int s[20] = {1, 7, 4, 2, 6, 8, 10, 18, 22, 20, 28, 68, 88, 108, 188, 200, 208, 288, 688, 888};

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> m;
        // cout << m << ": ";
        int d = ceil(m / 7.0);
        if (d <= 3) {
            cout << s[m - 2] << ' ';
        } else {
            cout << s[m - (d - 3) * 7 - 2];
            for (int j = 0; j < d - 3; ++j) {
                cout << 8;
            }
            cout << ' ';
        }

        if (m % 2 == 0) {
            for (int j = 0; j < m / 2; ++j) {
                cout << 1;
            }
        } else {
            cout << 7;
            for (int j = 0; j < (m - 1)/ 2 - 1; ++j) {
                cout << 1;
            }
        }
        cout << endl;
    }

    return 0;
}