#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int l, a, lcount, rcount, ltime, rtime, x;
char c;
vector<int> p;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (cin >> l >> a) {
        p = {};
        lcount = 0, rcount = 0, ltime = -1, rtime = -1;
        for (int i = 0; i < a; i++) {
            cin >> x >> c;
            if (c == 'L') {
                lcount++;
                if (x > ltime) {
                    ltime = x;
                }
            } else {
                rcount++;
                if (l - x > rtime) {
                    rtime = l - x;
                }
            }
            p.push_back(x);
        }
        sort(p.begin(), p.end());
        if (ltime > rtime) {
            cout << "The last ant will fall down in " << ltime << " seconds - started at " << p[lcount - 1] << '.' << endl;
        } else if (ltime < rtime) {
            cout << "The last ant will fall down in " << rtime << " seconds - started at " << p[a - rcount] << '.' << endl;
        } else {
            cout << "The last ant will fall down in " << rtime << " seconds - started at " << p[lcount - 1] << " and " << p[a - rcount] << '.' << endl;
        }
    }

    return 0;
}