#include <iostream>
#include <map>
using namespace std;

int n, m, c, *x, ma, mi;
bool found = false;
map<int, int> counts;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> c;

    x = new int[n];

    // length of m: [i-m+1...i]
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        counts[x[i]]++;
        if (i - m >= 0) {
            counts[x[i - m]]--;
            if (counts[x[i - m]] == 0) {
                counts.erase(x[i - m]);
            }
        }
        if (i - m + 1 >= 0 && counts.rbegin()->first - counts.begin()->first <= c) {
            cout << i - m + 2 << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "NONE" << endl;
    }

    return 0;
}