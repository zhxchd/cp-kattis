#include <iostream>
#include <vector>
using namespace std;

int s, n, m, *incr, *decr, p = 0, v = 0, last;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> n >> m;

    incr = new int[s];
    decr = new int[s];

    cin >> last;

    incr[0] = 1, decr[0] = 1;

    for (int i = 1; i < s; ++i) {
        int curr;
        cin >> curr;
        if (curr > last) {
            incr[i] = incr[i - 1] + 1;
            decr[i] = 1;
        } else {
            decr[i] = decr[i - 1] + 1;
            incr[i] = 1;
        }
        last = curr;
    }

    for (int i = 1; i + 1 < s; ++i) {
        if (i + n - 1 < s && incr[i] >= n && incr[i + 1] == 1 && decr[i + n - 1] == n) {
            p++;
        }
        if (i + m - 1 < s && decr[i] >= m && decr[i + 1] == 1 && incr[i + m - 1] == m) {
            v++;
        }
    }

    cout << p << ' ' << v << endl;

    return 0;
}