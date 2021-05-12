#include <iostream>
#include <iomanip>

using namespace std;

// d = h - a
int n, p, t, d = 0, h, a, t0 = 0;

int readsec() {
    int a, b;
    cin >> a;
    cin.ignore(1);
    cin >> b;
    return a * 60 + b;
}

void output() {
    int h1 = h / 60, h2 = h - h1 * 60;
    int a1 = a / 60, a2 = a - a1 * 60;
    if (d > 0) cout << 'H' << ' ';
    else cout << 'A' << ' ';
    cout << h1 << ':' << std::setfill('0') << std::setw(2) << h2 << ' ';
    cout << a1 << ':' << std::setfill('0') << std::setw(2) << a2 << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        char T;
        cin >> T;
        cin >> p;
        t = readsec();

        if (d > 0) {
            h += t - t0;
        } else if (d < 0) {
            a += t - t0;
        }
        if (T == 'H') d = p + d;
        else d = d - p;
        t0 = t;
    }

    if (d > 0) {
        h += 32 * 60 - t0;
    } else if (d < 0) {
        a += 32 * 60 - t0;
    }

    output();

    return 0;

}